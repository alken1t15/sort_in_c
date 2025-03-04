#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_MMAP
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#endif

// Компаратор для сортировки по возрастанию (asc)
int compare_asc(const char *a, const char *b) { return strcmp(a, b); }

// Компаратор для сортировки по убыванию (des)
int compare_des(const char *a, const char *b) {
  return strcmp(b, a); // Обычное сравнение, но в обратном порядке
}

// Функция выбора компаратора
int (*get_comparator(const char *name))(const char *, const char *) {
  if (strcmp(name, "asc") == 0)
    return compare_asc;
  if (strcmp(name, "des") == 0)
    return compare_des;
  return NULL;
}

// Функция загрузки строк (автоматический выбор между fopen и mmap)
char **load_strings(const char *filename, size_t count, size_t *actual_count) {
#ifdef USE_MMAP
  return load_strings_mmap(filename, count, actual_count);
#else
  return load_strings_fopen(filename, count, actual_count);
#endif
}
#ifdef USE_MMAP
// Чтение строк через mmap
char **load_strings_mmap(const char *filename, size_t count,
                         size_t *actual_count) {
  // Открываем файл в только режиме чтения (O_RDONLY)
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    return NULL;
  }
  // Перемещает указатель в конец файла и возвращает размер в байтах
  off_t file_size = lseek(fd, 0, SEEK_END);
  if (file_size == -1) {
    perror("Error getting file size");
    close(fd);
    return NULL;
  }
  // Здесь создаем отображение файла в память
  char *data = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);
  if (data == MAP_FAILED) {
    perror("Error mmap");
    return NULL;
  }

  // Подсчет количества строк
  size_t lines_count = 0;
  for (off_t i = 0; i < file_size; i++) {
    if (data[i] == '\n')
      lines_count++;
  }
  lines_count++; // Последняя строка без \n
  // Если в файле меньше строк, чем передали в параметре
  if (lines_count < count + 1) {
    fprintf(stderr, "There are not so many lines in the file\n");
    return NULL;
  }

  if (lines_count > count)
    lines_count = count;

  // Выделение памяти для указателей на строки
  char **lines = malloc(lines_count * sizeof(char *));
  if (!lines) {
    perror("Memory allocation error");
    munmap(data, file_size);
    return NULL;
  }

  // Разбор строк без изменения оригинальных данных
  size_t i = 0;
  // Указатель на начало строки
  const char *start = data;
  // Проходимся по каждому байту
  for (off_t j = 0; j < file_size; j++) {
    // Проверка на конец строки, либо на проверку конца файла
    if (data[j] == '\n' || j == file_size - 1) {
      // Вычисление длины строки
      size_t len = &data[j] - start + 1;
      lines[i] = malloc(len);
      if (!lines[i]) {
        perror("Memory allocation error");
        break;
      }
      // Копируем строку без переноса (для избежания заполнения)
      strncpy(lines[i], start, len - 1);
      // Потом добавляем перенос
      lines[i][len - 1] = '\0';
      i++;
      start = &data[j + 1];

      if (i >= lines_count)
        break;
    }
  }

  *actual_count = i;
  munmap(data, file_size);
  return lines;
}
#else
// Чтение строк через fopen
char **load_strings_fopen(const char *filename, size_t count,
                          size_t *actual_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Error opening file: %s\n", filename);
    return NULL;
  }

  char **lines = malloc(count * sizeof(char *));
  if (!lines) {
    fprintf(stderr, "Memory allocation error\n");
    fclose(file);
    return NULL;
  }

  size_t i = 0;      // Счетчик для строк
  char buffer[1024]; // Массив для хранения одной строки
  // fgets читает строку из файла в buffer
  while (i < count && fgets(buffer, sizeof(buffer), file)) {
    // Удаляем перенос строки
    buffer[strcspn(buffer, "\n")] = 0;
    // Выделяем память и копируем строку
    lines[i] = strdup(buffer);
    if (!lines[i]) {
      fprintf(stderr, "Memory allocation error\n");
      fclose(file);
      return NULL;
    }
    i++;
  }
  // Если в файле меньше строк, чем передали в параметре
  if (i != count) {
    fprintf(stderr, "There are not so many lines in the file\n");
    return NULL;
  }
  fclose(file);
  *actual_count = i; // Реальное количество строк
  return lines;
}

#endif

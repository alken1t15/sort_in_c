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
int compare_asc(const char* a, const char* b) {
    return strcmp(a, b);
}

// Компаратор для сортировки по убыванию (des)
int compare_des(const char* a, const char* b) {
    return strcmp(b, a); // Обычное сравнение, но в обратном порядке
}

// Функция выбора компаратора
int (*get_comparator(const char* name))(const char*, const char*) {
    if (strcmp(name, "asc") == 0) return compare_asc;
    if (strcmp(name, "des") == 0) return compare_des;
    return NULL;
}

// Функция загрузки строк (автоматический выбор между fopen и mmap)
char** load_strings(const char* filename, size_t count, const char* mode, size_t* actual_count) {
    if (strcmp(mode, "fopen") == 0) {
        return load_strings_fopen(filename, count, actual_count);
    }
#ifdef USE_MMAP
    else if (strcmp(mode, "mmap") == 0) {
        return load_strings_mmap(filename, count, actual_count);
    }
#endif
    else {
        fprintf(stderr, "Unknown file reading mode: %s\n", mode);
        return NULL;
    }
}

// Чтение строк через fopen
char** load_strings_fopen(const char* filename, size_t count, size_t* actual_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    char** lines = malloc(count * sizeof(char*));
    if (!lines) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    size_t i = 0;
    char buffer[1024];
    while (i < count && fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        lines[i] = strdup(buffer);
        if (!lines[i]) {
            fprintf(stderr, "Memory allocation error\n");
            fclose(file);
            return NULL;
        }
        i++;
    }
    fclose(file);
    *actual_count = i;
    return lines;
}

#ifdef USE_MMAP
// Чтение строк через mmap
char** load_strings_mmap(const char* filename, size_t count, size_t* actual_count) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        close(fd);
        return NULL;
    }

    char* data = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (data == MAP_FAILED) {
        return NULL;
    }

    char** lines = malloc(count * sizeof(char*));
    size_t i = 0;
    char* token = strtok(data, "\n");
    while (token && i < count) {
        lines[i++] = strdup(token);
        token = strtok(NULL, "\n");
    }

    *actual_count = i;
    munmap(data, file_size);
    return lines;
}
#endif
#include "../include/sortings.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 5) {
    fprintf(stderr, "Usage: %s <num_lines> <file> <algorithm> <comparator>\n",
            argv[0]);
    return -1;
  }

  size_t count = atoi(argv[1]);
  if (count == 0) {
    fprintf(stderr, "Invalid number of lines\n");
    return -1;
  }

  const char *filename = argv[2];
  const char *algorithm = argv[3];
  const char *comparator = argv[4];

  // Выбор компаратора
  int (*cmp)(const char *, const char *) = get_comparator(comparator);
  if (!cmp) {
    fprintf(stderr, "Unknown comparator\nExample: asc, des\n");
    return -1;
  }

  // Выбор сортировки
  void (*sort_func)(char **, size_t, int (*)(const char *, const char *)) =
      NULL;
  if (strcmp(algorithm, "bubble") == 0)
    sort_func = sort_bubble;
  else if (strcmp(algorithm, "insertion") == 0)
    sort_func = sort_insertion;
  else if (strcmp(algorithm, "merge") == 0)
    sort_func = sort_merge;
  else if (strcmp(algorithm, "quick") == 0)
    sort_func = sort_quick;
  else if (strcmp(algorithm, "radix") == 0)
    sort_func = sort_radix;
  else {
    fprintf(stderr, "Unknown sorting algorithm\nExample: 1)bubble 2)insertion "
                    "3)merge 4)quick 5)radix\n");
    return -1;
  }

  // Загрузка строк с правильными аргументами
  size_t actual_count;
  char **lines = load_strings(filename, count, &actual_count);
  if (!lines)
    return -1;

  // Сортировка строк
  sort_func(lines, actual_count, cmp);

  // Вывод отсортированных строк
  for (size_t i = 0; i < actual_count; i++) {
    printf("%s\n", lines[i]);
    free(lines[i]);
  }
  free(lines);

  return 0;
}

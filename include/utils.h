#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

// Функция выбора компаратора
int compare_asc(const char* a, const char* b);
int compare_des(const char* a, const char* b);
int (*get_comparator(const char* name))(const char*, const char*);

char** load_strings(const char* filename, size_t count, const char* mode, size_t* actual_count);
char** load_strings_fopen(const char* filename, size_t count, size_t* actual_count);

#ifdef USE_MMAP
char** load_strings_mmap(const char* filename, size_t count, size_t* actual_count);
#endif

#endif
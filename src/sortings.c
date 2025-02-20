#include "sortings.h"
#include <stdlib.h>
#include <string.h>
#include <utils.h>

// 🔹 Пузырьковая сортировка (Bubble Sort)
void sort_bubble(char** arr, size_t size, int (*comparator)(const char*, const char*)) {
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (comparator(arr[j], arr[j + 1]) > 0) {
                char* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 🔹 Сортировка вставками (Insertion Sort)
void sort_insertion(char** arr, size_t size, int (*comparator)(const char*, const char*)) {
    for (size_t i = 1; i < size; i++) {
        char* key = arr[i];
        size_t j = i;
        while (j > 0 && comparator(arr[j - 1], key) > 0) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

// 🔹 Функция для слияния (Merge Step)
void merge(char** arr, size_t left, size_t mid, size_t right, int (*comparator)(const char*, const char*)) {
    size_t left_size = mid - left + 1;
    size_t right_size = right - mid;

    char** left_array = (char**)malloc(left_size * sizeof(char*));
    char** right_array = (char**)malloc(right_size * sizeof(char*));

    for (size_t i = 0; i < left_size; i++) left_array[i] = arr[left + i];
    for (size_t j = 0; j < right_size; j++) right_array[j] = arr[mid + 1 + j];

    size_t i = 0, j = 0, k = left;
    while (i < left_size && j < right_size) {
        if (comparator(left_array[i], right_array[j]) <= 0) arr[k++] = left_array[i++];
        else arr[k++] = right_array[j++];
    }

    while (i < left_size) arr[k++] = left_array[i++];
    while (j < right_size) arr[k++] = right_array[j++];

    free(left_array);
    free(right_array);
}

// 🔹 Рекурсивная сортировка слиянием (Merge Sort)
void merge_sort(char** arr, size_t left, size_t right, int (*comparator)(const char*, const char*)) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        merge_sort(arr, left, mid, comparator);
        merge_sort(arr, mid + 1, right, comparator);
        merge(arr, left, mid, right, comparator);
    }
}

// 🔹 Обёртка для Merge Sort
void sort_merge(char** arr, size_t size, int (*comparator)(const char*, const char*)) {
    if (size > 1) {
        merge_sort(arr, 0, size - 1, comparator);
    }
}

// 🔹 Быстрая сортировка (Quick Sort)
void quick_sort(char** arr, size_t low, size_t high, int (*comparator)(const char*, const char*)) {
    if (low < high) {
        char* pivot = arr[high];
        size_t i = low - 1;
        for (size_t j = low; j < high; j++) {
            if (comparator(arr[j], pivot) < 0) {
                i++;
                char* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        char* temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        size_t pivot_index = i + 1;

        if (pivot_index > 0) quick_sort(arr, low, pivot_index - 1, comparator);
        quick_sort(arr, pivot_index + 1, high, comparator);
    }
}

// 🔹 Обёртка для Quick Sort
void sort_quick(char** arr, size_t size, int (*comparator)(const char*, const char*)) {
    if (size > 1) {
        quick_sort(arr, 0, size - 1, comparator);
    }
}

// 🔹 Функция для получения максимальной длины строки
size_t get_max_length(char** arr, size_t size) {
    size_t max_len = 0;
    for (size_t i = 0; i < size; i++) {
        size_t len = strlen(arr[i]);
        if (len > max_len) max_len = len;
    }
    return max_len;
}

// 🔹 Поразрядная сортировка (Radix Sort) для строк
void sort_radix(char** arr, size_t size, int (*comparator)(const char*, const char*)) {
    size_t max_len = get_max_length(arr, size);

    for (int pos = max_len - 1; pos >= 0; pos--) {
        size_t count[256] = {0};  // Частотный массив (256 символов ASCII)
        char** output = (char**)malloc(size * sizeof(char*));

        // Подсчёт количества символов в текущей позиции
        for (size_t i = 0; i < size; i++) {
            unsigned char key = (unsigned char)(pos < strlen(arr[i]) ? arr[i][pos] : 0);
            count[key]++;
        }

        // Вычисление позиций элементов
        for (size_t i = 1; i < 256; i++) {
            count[i] += count[i - 1];
        }

        // Размещение элементов в отсортированном порядке
        for (int i = size - 1; i >= 0; i--) {
            unsigned char key = (unsigned char)(pos < strlen(arr[i]) ? arr[i][pos] : 0);
            output[count[key] - 1] = arr[i];
            count[key]--;
        }

        // Копируем отсортированные данные обратно
        for (size_t i = 0; i < size; i++) {
            arr[i] = output[i];
        }

        free(output);
    }

    // Если сортировка по убыванию, реверсируем массив
    if (comparator == compare_des) {
        for (size_t i = 0; i < size / 2; i++) {
            char* temp = arr[i];
            arr[i] = arr[size - 1 - i];
            arr[size - 1 - i] = temp;
        }
    }
}
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../include/sortings.h"
#include "../include/utils.h"

// Тестирование сортировки пузырьком
void test_bubble_sort() {
    char* arr[] = {"Banana", "Apple", "Cherry"};
    char* expected_asc[] = {"Apple", "Banana", "Cherry"};
    char* expected_des[] = {"Cherry", "Banana", "Apple"};

    sort_bubble(arr, 3, compare_asc);
    for (int i = 0; i < 3; i++) {
        assert(strcmp(arr[i], expected_asc[i]) == 0);
    }

    sort_bubble(arr, 3, compare_des);
    for (int i = 0; i < 3; i++) {
        assert(strcmp(arr[i], expected_des[i]) == 0);
    }

    printf("test_bubble_sort passed!\n");
}

// Тестирование сортировки вставками
void test_insertion_sort() {
    char* arr[] = {"dog", "cat", "elephant"};
    char* expected_asc[] = {"cat", "dog", "elephant"};
    char* expected_des[] = {"elephant", "dog", "cat"};

    sort_insertion(arr, 3, compare_asc);
    for (int i = 0; i < 3; i++) {
        assert(strcmp(arr[i], expected_asc[i]) == 0);
    }

    sort_insertion(arr, 3, compare_des);
    for (int i = 0; i < 3; i++) {
        assert(strcmp(arr[i], expected_des[i]) == 0);
    }

    printf("test_insertion_sort passed!\n");
}

// Тестирование сортировки слиянием
void test_merge_sort() {
    char* arr[] = {"zebra", "ant", "monkey"};
    char* expected_asc[] = {"ant", "monkey", "zebra"};
    char* expected_des[] = {"zebra", "monkey", "ant"};

    sort_merge(arr, 3, compare_asc);
    for (int i = 0; i < 3; i++) {
        assert(strcmp(arr[i], expected_asc[i]) == 0);
    }

    sort_merge(arr, 3, compare_des);
    for (int i = 0; i < 3; i++) {
        assert(strcmp(arr[i], expected_des[i]) == 0);
    }

    printf("test_merge_sort passed!\n");
}

// Тестирование быстрой сортировки
void test_quick_sort() {
    char* arr[] = {"grape", "apple", "pear"};
    char* expected_asc[] = {"apple", "grape", "pear"};
    char* expected_des[] = {"pear", "grape", "apple"};

    sort_quick(arr, 3, compare_asc);
    for (int i = 0; i < 3; i++) {
        assert(strcmp(arr[i], expected_asc[i]) == 0);
    }

    sort_quick(arr, 3, compare_des);
    for (int i = 0; i < 3; i++) {
        assert(strcmp(arr[i], expected_des[i]) == 0);
    }

    printf("test_quick_sort passed!\n");
}

// Тестирование поразрядной сортировки
void test_radix_sort() {
    char* arr[] = {"900", "123", "500"};
    char* expected_asc[] = {"123", "500", "900"};
    char* expected_des[] = {"900", "500", "123"};

    sort_radix(arr, 3, compare_asc);
    for (int i = 0; i < 3; i++) {
        assert(strcmp(arr[i], expected_asc[i]) == 0);
    }

    sort_radix(arr, 3, compare_des);
    for (int i = 0; i < 3; i++) {
        assert(strcmp(arr[i], expected_des[i]) == 0);
    }

    printf("test_radix_sort passed!\n");
}

// Запуск всех тестов
int main() {
    test_bubble_sort();
    test_insertion_sort();
    test_merge_sort();
    test_quick_sort();
    test_radix_sort();

    printf("All sorting tests passed!\n");
    return 0;
}
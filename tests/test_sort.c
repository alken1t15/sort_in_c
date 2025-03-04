#include "../include/sortings.h"
#include "../include/utils.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Тестирование сортировки пузырьком
void test_bubble_sort() {
  char *arr[] = {"Banana", "Apple", "Cherry"};
  char *expected_asc[] = {"Apple", "Banana", "Cherry"};
  char *expected_des[] = {"Cherry", "Banana", "Apple"};

  sort_bubble(arr, 3, compare_asc);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_asc[i]) == 0);
  }

  sort_bubble(arr, 3, compare_des);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_des[i]) == 0);
  }

  printf("✅ test_bubble_sort passed!\n");
}

// Тестирование сортировки вставками
void test_insertion_sort() {
  char *arr[] = {"dog", "cat", "elephant"};
  char *expected_asc[] = {"cat", "dog", "elephant"};
  char *expected_des[] = {"elephant", "dog", "cat"};

  sort_insertion(arr, 3, compare_asc);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_asc[i]) == 0);
  }

  sort_insertion(arr, 3, compare_des);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_des[i]) == 0);
  }

  printf("✅ test_insertion_sort passed!\n");
}

// Тестирование сортировки слиянием
void test_merge_sort() {
  char *arr[] = {"zebra", "ant", "monkey"};
  char *expected_asc[] = {"ant", "monkey", "zebra"};
  char *expected_des[] = {"zebra", "monkey", "ant"};

  sort_merge(arr, 3, compare_asc);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_asc[i]) == 0);
  }

  sort_merge(arr, 3, compare_des);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_des[i]) == 0);
  }

  printf("✅ test_merge_sort passed!\n");
}

// Тестирование быстрой сортировки
void test_quick_sort() {
  char *arr[] = {"grape", "apple", "pear"};
  char *expected_asc[] = {"apple", "grape", "pear"};
  char *expected_des[] = {"pear", "grape", "apple"};

  sort_quick(arr, 3, compare_asc);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_asc[i]) == 0);
  }

  sort_quick(arr, 3, compare_des);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_des[i]) == 0);
  }

  printf("✅ test_quick_sort passed!\n");
}

// Тестирование поразрядной сортировки
void test_radix_sort() {
  char *arr[] = {"900", "123", "500"};
  char *expected_asc[] = {"123", "500", "900"};
  char *expected_des[] = {"900", "500", "123"};

  sort_radix(arr, 3, compare_asc);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_asc[i]) == 0);
  }

  sort_radix(arr, 3, compare_des);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_des[i]) == 0);
  }

  printf("✅ test_radix_sort passed!\n");
}

// Тестирование сортировки массива из одного элемента
void test_single_element() {
  char *arr[] = {"single"};
  char *expected[] = {"single"};
  sort_bubble(arr, 1, compare_asc);
  for (int i = 0; i < 1; i++) {
    assert(strcmp(arr[i], expected[i]) == 0);
  }
  printf("✅ test_single_element passed!\n");
}

// Тестирование сортировки уже отсортированного массива
void test_sorted_array() {
  char *arr[] = {"apple", "banana", "cherry"};
  char *expected[] = {"apple", "banana", "cherry"};
  sort_bubble(arr, 3, compare_asc);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected[i]) == 0);
  }
  printf("✅ test_sorted_array passed!\n");
}

// Тестирование сортировки массива с одинаковыми элементами
void test_identical_elements() {
  char *arr[] = {"same", "same", "same"};
  char *expected[] = {"same", "same", "same"};
  sort_bubble(arr, 3, compare_asc);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected[i]) == 0);
  }
  printf("✅ test_identical_elements passed!\n");
}

// Тестирование сортировки массива с разным регистром букв
void test_case_sensitive() {
  char *arr[] = {"Banana", "apple", "Cherry"};
  char *expected_asc[] = {"Banana", "Cherry", "apple"}; // ASCII сортировка
  sort_bubble(arr, 3, compare_asc);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_asc[i]) == 0);
  }
  printf("✅ test_case_sensitive passed!\n");
}

// Тестирование сортировки строк, содержащих числа
void test_numeric_strings() {
  char *arr[] = {"100", "20", "3"};
  char *expected_asc[] = {"100", "20", "3"}; // Строковое сравнение
  sort_bubble(arr, 3, compare_asc);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_asc[i]) == 0);
  }
  printf("✅ test_numeric_strings passed!\n");
}

// Тестирование сортировки строк с символами и спецзнаками
void test_special_characters() {
  char *arr[] = {"!hello", "#world", "@apple"};
  char *expected_asc[] = {"!hello", "#world", "@apple"}; // ASCII порядок
  sort_bubble(arr, 3, compare_asc);
  for (int i = 0; i < 3; i++) {
    assert(strcmp(arr[i], expected_asc[i]) == 0);
  }
  printf("✅ test_special_characters passed!\n");
}

// Запуск всех тестов
int main() {
  test_bubble_sort();
  test_insertion_sort();
  test_merge_sort();
  test_quick_sort();
  test_radix_sort();
  test_single_element();
  test_sorted_array();
  test_identical_elements();
  test_case_sensitive();
  test_numeric_strings();
  test_special_characters();

  printf("✅ All sorting tests passed!\n");
  return 0;
}

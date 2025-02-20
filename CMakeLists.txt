cmake_minimum_required(VERSION 3.10)
project(sort_strings C)

set(CMAKE_C_STANDARD 11)

option(USE_MMAP "Use mmap for file reading" OFF)

add_executable(sort_strings src/main.c src/sortings.c src/utils.c)
include_directories(include)

if(USE_MMAP)
    target_compile_definitions(sort_strings PRIVATE USE_MMAP)
endif()

# Добавляем тесты
enable_testing()
add_executable(test_sort tests/test_sort.c src/sortings.c src/utils.c)
add_test(NAME test_sort COMMAND test_sort)
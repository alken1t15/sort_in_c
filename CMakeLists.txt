cmake_minimum_required(VERSION 3.10)
project(sort_strings C)

set(CMAKE_C_STANDARD 11)

# Опция для выбора mmap
option(USE_MMAP "Use mmap for file reading" OFF)

# Создаем исполняемый файл
add_executable(sort_strings src/main.c src/sortings.c src/utils.c)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Выводим сообщение о выбранном методе чтения
if(USE_MMAP)
    message(STATUS "Using mmap for file reading")
    target_compile_definitions(sort_strings PRIVATE USE_MMAP)
else()
    message(STATUS "Using standard file I/O (fread, read)")
endif()

# Добавляем тесты
enable_testing()
add_executable(test_sort tests/test_sort.c src/sortings.c src/utils.c)
add_test(NAME test_sort COMMAND test_sort)
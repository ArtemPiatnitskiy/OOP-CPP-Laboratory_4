cmake_minimum_required(VERSION 3.10)
project(Laboratory_3)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")


# Установка Google Test
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)

# Отключаем использование статической библиотеки и переключаем на динамическую (Более подробно про это можно прочитать в файле Materials.md)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(${PROJECT_NAME}_lib src/figure.cpp src/point.cpp src/arrayoffigures.cpp src/rectangle.cpp src/trapezoid.cpp src/rhombus.cpp)
add_executable(${PROJECT_NAME}_exe main.cpp)

target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)

# Добавление тестов
enable_testing()

# Тесты для класса Point
add_executable(test_point tests/test_point.cpp)
target_link_libraries(test_point ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Laboratory_3_tests_point COMMAND test_point)

# Тесты для класса Rectangle
add_executable(test_rectangle tests/test_rectangle.cpp)
target_link_libraries(test_rectangle ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Laboratory_3_tests_rectangle COMMAND test_rectangle)


# Тесты для класса Rhombus
add_executable(test_rhombus tests/test_rhombus.cpp)
target_link_libraries(test_rhombus ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Laboratory_3_tests_rhombus COMMAND test_rhombus)

# Тесты для класса Trapezoid
add_executable(test_trapezoid tests/test_trapezoid.cpp)
target_link_libraries(test_trapezoid ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Laboratory_3_tests_trapezoid COMMAND test_trapezoid)

# Тесты для класса ArrayOfFigures
add_executable(test_arrayoffigures tests/test_arrayoffigures.cpp)
target_link_libraries(test_arrayoffigures ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Laboratory_3_tests_arrayoffigures COMMAND test_arrayoffigures)
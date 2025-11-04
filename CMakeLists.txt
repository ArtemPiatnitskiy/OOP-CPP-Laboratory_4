cmake_minimum_required(VERSION 3.10)
project(Laboratory_4)


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


# Библиотека реализована в заголовочных файлах (header-only).
# Создаём интерфейсную цель, которая передаёт include-путь и опции потребителям.
add_library(${PROJECT_NAME}_lib INTERFACE)
target_include_directories(${PROJECT_NAME}_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME}_exe main.cpp)

target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)

# Добавление тестов
enable_testing()

# Тесты для класса Point
add_executable(test_point_${PROJECT_NAME} tests/test_point.cpp)
target_link_libraries(test_point_${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Laboratory_4_tests_point COMMAND test_point_${PROJECT_NAME})

# Тесты для класса Hexagon
add_executable(test_hexagon_${PROJECT_NAME} tests/test_hexagon.cpp)
target_link_libraries(test_hexagon_${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Laboratory_4_tests_hexagon COMMAND test_hexagon_${PROJECT_NAME})


# Тесты для класса Rhombus
add_executable(test_rhombus_${PROJECT_NAME} tests/test_rhombus.cpp)
target_link_libraries(test_rhombus_${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Laboratory_4_tests_rhombus COMMAND test_rhombus_${PROJECT_NAME})

# Тесты для класса Trapezoid
add_executable(test_pentagon_${PROJECT_NAME} tests/test_pentagon.cpp)
target_link_libraries(test_pentagon_${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Laboratory_4_tests_pentagon COMMAND test_pentagon_${PROJECT_NAME})

# Тесты для класса ArrayOfFigures
add_executable(test_arrayoffigures_${PROJECT_NAME} tests/test_arrayoffigures.cpp)
target_link_libraries(test_arrayoffigures_${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib gtest_main)

add_test(NAME Laboratory_4_tests_arrayoffigures COMMAND test_arrayoffigures_${PROJECT_NAME})
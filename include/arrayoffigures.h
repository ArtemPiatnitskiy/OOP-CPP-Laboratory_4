#pragma once

#include "figure.h"
#include <cstddef>
#include <iostream>

class ArrayOfFigures {
    public:
        // Конструктор по умолчанию.
        ArrayOfFigures() = default;
        
        // Конструктор с параметром размера массива.
        ArrayOfFigures(size_t capacity);

        // Конструктор с инициализацией из initializer списка в котором фигуры.
        ArrayOfFigures(std::initializer_list<Figure*> list);

        // Конструктор перемещения.
        ArrayOfFigures(ArrayOfFigures&& other) noexcept;

        // Конструктор копирования.
        ArrayOfFigures(const ArrayOfFigures& other);

        // Оператор присваивания.
        ArrayOfFigures& operator=(const ArrayOfFigures& other);
        // Оператор перемещения.
        ArrayOfFigures& operator=(ArrayOfFigures&& other) noexcept;

        // Деструктор.
        ~ArrayOfFigures();

        // Функция для добавления фигуры в массив.
        void add_figure(Figure* figure);

        // Перегрузка оператора индексации для доступа к фигурам в массиве.
        // Необходимо реализовать перегрузку метода для const, и для non-const версий.
        // Возвращаемый тип - указатель на Figure (не const), чтобы можно было изменять фигуры.
        Figure*& operator[](size_t index);
        // Const версия оператора индексации.
        // Возвращает копию указателя на Figure, чтобы предотвратить изменение фигур.
        Figure* operator[](size_t index) const;

        // Функция для удаления фигуры из массива по индексу.
        void remove_figure(size_t index);

        // Получение текущего размера массива.
        size_t get_size() const;

        // Получение текущей емкости массива.
        size_t get_capacity() const;

        // Функция для вывода всех фигур в массиве.
        void print_figures(std::ostream& os) const;

        // Функция для нахождения общей площади всех фигур в массиве.
        double total_square() const;

    private:
        // Динамический массив указателей на фигуры.
        Figure** figures{nullptr};
        // Текущий размер массива.
        size_t size{0};
        // Текущая емкость массива.
        size_t capacity{0};
        // Функция для изменения размера массива.
        void resize();

        // Метод для обмена ресурсами между двумя объектами класса ArrayOfFigures.
        void swap(ArrayOfFigures& other) noexcept;
};
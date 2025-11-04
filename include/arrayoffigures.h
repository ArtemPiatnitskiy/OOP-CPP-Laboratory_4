#pragma once

#include "figure.h"
#include <cstddef>
#include <iostream>
#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <utility>


template<class Figure>
// Концепт проверяет, что Figure - это класс или структура
concept Arrayable = std::is_class_v<Figure>;

template<Arrayable Figure>
class ArrayOfFigures {
    public:
        // Конструктор по умолчанию.
        ArrayOfFigures() = default;
        
        // Конструктор с параметром размера массива.
        ArrayOfFigures(size_t cap){
            size = 0;
            capacity = (cap == 0) ? 1 : (cap * 2);
            figures = std::make_shared<std::shared_ptr<Figure>[]>(capacity);
            std::fill_n(figures.get(), capacity, nullptr);
        };

        // Конструктор с инициализацией из initializer списка в котором фигуры.
        ArrayOfFigures(std::initializer_list<std::shared_ptr<Figure>> list) {
            size = list.size();
            capacity = (size == 0) ? 1 : (size * 2);
            figures = std::make_shared<std::shared_ptr<Figure>[]>(capacity);
            std::fill_n(figures.get(), capacity, nullptr);
            // Глубокое копирование указателей из списка в массив.
            std::transform(list.begin(), list.end(), figures,
                        [](Figure* fig) { return (fig ? fig->clone() : nullptr); });
        };

        // Конструктор перемещения.
        ArrayOfFigures(ArrayOfFigures&& other) noexcept
            : figures(other.figures), size(other.size), capacity(other.capacity) {
            other.figures.reset();
            other.size = 0;
            other.capacity = 0;
        };
        

        // Конструктор копирования.
        ArrayOfFigures(const ArrayOfFigures& other) {
            size = other.size;
            capacity = other.capacity;
            figures = std::make_shared<std::shared_ptr<Figure>[]>(capacity);
            std::fill_n(figures.get(), capacity, nullptr);
            for (size_t i = 0; i < size; ++i) {
                figures[i] = other.figures[i] ? other.figures[i]->clone() : nullptr;
            }
        };

        // Оператор присваивания.
        ArrayOfFigures& operator=(const ArrayOfFigures& other) {
            if (this == &other) return *this;
            ArrayOfFigures temp(other); // Используем конструктор копирования.
            swap(temp); // Обмениваемся ресурсами с временным объектом.
            return *this;
        };

        // Оператор перемещения.
        ArrayOfFigures& operator=(ArrayOfFigures&& other) noexcept {
            if (this == &other) return *this;
            // Удаляем только сам массив, так как shared_ptr сам управляет памятью под фигуры.
            figures.reset();

            // Перемещаем ресурсы из другого объекта.
            figures = other.figures;
            size = other.size;
            capacity = other.capacity;

            // Обнуляем другой объект.
            other.figures.reset();
            other.size = 0;
            other.capacity = 0;
            return *this;
        };

        // Деструктор.
        ~ArrayOfFigures() {
            figures.reset(); // shared_ptr автоматически освободит память под фигуры и массив.
        };

        // Функция для добавления фигуры в массив.
        void add_figure(std::shared_ptr<Figure> figure) {
            if (size >= capacity) {
                resize();
            }
            figures[size++] = figure;
        };
        

        // Перегрузка оператора индексации для доступа к фигурам в массиве.
        // Необходимо реализовать перегрузку метода для const, и для non-const версий.
        // Возвращаемый тип - указатель на Figure (не const), чтобы можно было изменять фигуры.
        // Возвращаем ссылку на указатель, чтобы можно было изменять указатель в массиве (например, присваивать новый объект).
        // Это увеличивает счётчик ссылок, так как возвращаем shared_ptr по ссылке.
        std::shared_ptr<Figure>& operator[](size_t index){
        if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            return figures[index];
        };
        
        // Const версия оператора индексации.
        // Возвращает копию указателя на Figure, чтобы предотвратить изменение фигур.
        // Не увеличиваем счетчик ссылок, так как возвращаем ссылку на существующий shared_ptr.
        const std::shared_ptr<Figure>& operator[](size_t index) const{
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            return figures[index];
        };

        // Функция для удаления фигуры из массива по индексу.
        void remove_figure(size_t index) {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            figures[index].reset(); // Освобождение shared_ptr.
            for (size_t i = index; i < size - 1; ++i) {
                figures[i] = figures[i + 1]; // Сдвиг элементов влево.
            }
            --size;
            if (size >= 0) figures[size] = nullptr; // Обнуляем последний элемент.
        };

        // Получение текущего размера массива.
        size_t get_size() const{
            return size;
        };

        // Получение текущей емкости массива.
        size_t get_capacity() const{
            return capacity;
        };

        // Функция для вывода всех фигур в массиве.
        void print_figures(std::ostream& os) const {
            for (size_t i = 0; i < size; ++i) {
                if (figures[i]) {
                    os << *figures[i] << std::endl;
                }
            }
        };

        // Функция для нахождения общей площади всех фигур в массиве.
        double total_square() const{
            double total = 0.0;
            for (size_t i = 0; i < size; ++i) {
                if (figures[i]) {
                    // Используется неявное преобразование к double через перегруженный оператор.
                    // total += *figures[i]; Так тодже работает, но ниже будет быолее явно, с помощью функции square().
                    total += figures[i]->square();
                }
            }
            return total;
        };

    private:
        // Динамический массив указателей на фигуры.
        std::shared_ptr<std::shared_ptr<Figure>[]> figures{nullptr};
        // Текущий размер массива.
        size_t size{0};
        // Текущая емкость массива.
        size_t capacity{0};
        // Функция для изменения размера массива.
        void resize(){
            capacity = (capacity == 0) ? 1 : capacity * 2;
            std::shared_ptr<std::shared_ptr<Figure>[]> new_figures = std::make_shared<std::shared_ptr<Figure>[]>(capacity);
            std::fill_n(new_figures.get(), capacity, nullptr);
            for (size_t i = 0; i < size; ++i) {
                new_figures[i] = figures[i];
            }
            figures.reset();
            figures = new_figures;
        };

        // Метод для обмена ресурсами между двумя объектами класса ArrayOfFigures.
        void swap(ArrayOfFigures& other) noexcept {
            std::swap(figures, other.figures);
            std::swap(size, other.size);
            std::swap(capacity, other.capacity);
        };
};
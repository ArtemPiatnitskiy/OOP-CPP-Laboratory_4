#include <initializer_list>
#include <iostream>
#include "../include/arrayoffigures.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

// Конструктор с параметром размера массива.
ArrayOfFigures::ArrayOfFigures(size_t cap){
    size = 0;
    capacity = (cap == 0) ? 1 : (cap * 2);
    figures = new Figure*[capacity];
    std::fill_n(figures, capacity, nullptr);
}

// Конструктор с инициализацией из initializer списка в котором фигуры.
ArrayOfFigures::ArrayOfFigures(std::initializer_list<Figure*> list) {
    size = list.size();
    capacity = (size == 0) ? 1 : (size * 2);
    figures = new Figure*[capacity];
    std::fill_n(figures, capacity, nullptr);
    // Глубокое копирование указателей из списка в массив.
    std::transform(list.begin(), list.end(), figures,
                   [](Figure* fig) { return (fig ? fig->clone() : nullptr); });
}

// Конструктор перемещения.
ArrayOfFigures::ArrayOfFigures(ArrayOfFigures&& other) noexcept
    : figures(other.figures), size(other.size), capacity(other.capacity) {
    other.figures = nullptr;
    other.size = 0;
    other.capacity = 0;
}

// Конструктор копирования (глубокое копирование).
ArrayOfFigures::ArrayOfFigures(const ArrayOfFigures& other) {
    size = other.size;
    capacity = other.capacity;
    figures = new Figure*[capacity];
    std::fill_n(figures, capacity, nullptr);
    for (size_t i = 0; i < size; ++i) {
        figures[i] = other.figures[i] ? other.figures[i]->clone() : nullptr;
    }
}

// Оператор присваивания.
ArrayOfFigures& ArrayOfFigures::operator=(const ArrayOfFigures& other) {
    if (this == &other) return *this;
    ArrayOfFigures temp(other); // Используем конструктор копирования.
    swap(temp); // Обмениваемся ресурсами с временным объектом.
    return *this;
}

// Оператор перемещения.
ArrayOfFigures& ArrayOfFigures::operator=(ArrayOfFigures&& other) noexcept {
    if (this == &other) return *this;
    // Освобождаем текущие ресурсы.
    for (size_t i = 0; i < size; ++i) {
        delete figures[i];
    }
    delete[] figures;
    // Перемещаем ресурсы из другого объекта.
    figures = other.figures;
    size = other.size;
    capacity = other.capacity;
    // Обнуляем другой объект.
    other.figures = nullptr;
    other.size = 0;
    other.capacity = 0;
    return *this;
}

// Swap метод для обмена ресурсами между двумя объектами.
void ArrayOfFigures::swap(ArrayOfFigures& other) noexcept {
    std::swap(figures, other.figures);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
}



// Деструктор.
ArrayOfFigures::~ArrayOfFigures() {
    for (size_t i = 0; i < size; ++i) {
        delete figures[i]; // Освобождение памяти под каждую фигуру.
    }
    delete[] figures; // Освобождение памяти под массив указателей.
}

// Функция для добавления фигуры в массив.
void ArrayOfFigures::add_figure(Figure* figure) {
    if (size >= capacity) {
        resize();
    }
    figures[size++] = figure;
}

// Перегрузка оператора индексации для доступа к фигурам в массиве.
Figure* ArrayOfFigures::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return figures[index];
}

Figure*& ArrayOfFigures::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return figures[index];
}

// Функция для удаления фигуры из массива по индексу.
void ArrayOfFigures::remove_figure(size_t index) {
    if (index < size) {
        throw std::out_of_range("Index out of range");
    }
    delete figures[index]; // Освобождение памяти под фигуру.
    for (size_t i = index; i < size - 1; ++i) {
        figures[i] = figures[i + 1]; // Сдвиг элементов влево.
    }
    --size;
    if (size >= 0) figures[size] = nullptr; // Обнуляем последний элемент.
}

// Получение текущего размера массива.
size_t ArrayOfFigures::get_size() const {
    return size;
}

// Получение текущей емкости массива.
size_t ArrayOfFigures::get_capacity() const {
    return capacity;
}

// Функция для вывода всех фигур в массиве.
void ArrayOfFigures::print_figures(std::ostream& os) const {
    for (size_t i = 0; i < size; ++i) {
        if (figures[i]) {
            os << *figures[i] << std::endl;
        } 
    }
}

// Функция для нахождения общей площади всех фигур в массиве.
double ArrayOfFigures::total_square() const {
    double total = 0.0;
    for (size_t i = 0; i < size; ++i) {
        if (figures[i]) {
            // Используется неявное преобразование к double через перегруженный оператор.
            // total += *figures[i]; Так тодже работает, но ниже будет быолее явно, с помощью функции square().
            total += figures[i]->square();
        }
    }
    return total;
}

// Функция для изменения размера массива.
void ArrayOfFigures::resize() {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    Figure** new_figures = new Figure*[capacity];
    std::fill_n(new_figures, capacity, nullptr);
    for (size_t i = 0; i < size; ++i) {
        new_figures[i] = figures[i];
    }
    delete[] figures;
    figures = new_figures;
}
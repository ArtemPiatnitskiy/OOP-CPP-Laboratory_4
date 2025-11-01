#pragma once
#include <compare>
#include <string>
#include "point.h"
#include "figure.h"

class Rectangle : public Figure {
    public:
        // Конструктор по умолчанию.
        Rectangle() : Figure("rectangle") {};

        // Конструктор точками противоположных углов.
        Rectangle(const Point& p1, const Point& p2, std::string description = "rectangle");

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Rectangle(const Rectangle& other);
        Rectangle& operator=(const Rectangle& other);
        // Конструктор перемещения.
        Rectangle(Rectangle&& other) noexcept;
        Rectangle& operator=(Rectangle&& other) noexcept;

        // Перегрузка оператора сравниния ==.
        bool operator==(const Rectangle& other) const;
        // Перегрузка оператора сравнения <=>
        std::partial_ordering operator<=>(const Rectangle& other) const;

        // Переопределение виртуальных методов базового класса.
        Point geometric_center() const override;
        double square() const override;
        double perimeter() const override;

        // Функция для нахождения площади фигуры через перегрузку оператора double().
        // Возвращает площадь фигуры.
        // Мы не используем explicit здесь, чтобы позволить неявное преобразование к double.
        operator double() const override;

        // Перегрузка операторов ввода/вывода.
        void print(std::ostream& os) const override;
        void read(std::istream& is) override;

        // Функция для клонирования фигуры.
        Figure* clone() const override;

    private:
        Point points[4];

};
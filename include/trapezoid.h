#pragma once
#include <string>
#include "point.h"
#include "figure.h"

class Trapezoid : public Figure {
    public:
        // Конструктор по умолчанию.
        Trapezoid() : Figure("trapezoid") {};
        // Конструктор точками.
        Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4, std::string description = "trapezoid");

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Trapezoid(const Trapezoid& other);
        Trapezoid& operator=(const Trapezoid& other);
        // Конструктор перемещения.
        Trapezoid(Trapezoid&& other) noexcept;
        Trapezoid& operator=(Trapezoid&& other) noexcept;

        // Перегрузка оператора сравниения ==.
        bool operator==(const Trapezoid& other) const;
        // Перегрузка оператора сравнения <=>
        std::partial_ordering operator<=>(const Trapezoid& other) const;

        // Переопределение виртуальных методов базового класса.
        Point geometric_center() const override;
        double square() const override;
        double perimeter() const override;

        operator double() const override;

        // Перегрузка операторов ввода/вывода.
        void print(std::ostream& os) const override;
        void read(std::istream& is) override;

        // Функция для клонирования фигуры.
        Figure* clone() const override;

    private:
        Point points[4];

};
#pragma once
#include <string>
#include "point.h"
#include "figure.h"

class Rhombus : public Figure {
    public:
        // Конструктор по умолчанию.
        Rhombus() : Figure("rhombus") {};
        // Конструктор точками.
        Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4, std::string description = "rhombus");

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Rhombus(const Rhombus& other);
        Rhombus& operator=(const Rhombus& other);
        // Конструктор перемещения.
        Rhombus(Rhombus&& other) noexcept;
        Rhombus& operator=(Rhombus&& other) noexcept;

        // Перегрузка оператора сравниения ==.
        bool operator==(const Rhombus& other) const;
        // Перегрузка оператора сравнения <=>
        std::partial_ordering operator<=>(const Rhombus& other) const;

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
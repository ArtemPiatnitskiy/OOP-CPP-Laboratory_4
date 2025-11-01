#include "../include/trapezoid.h"
#include "../include/point.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

// Конструктор с параметрами описания и четырьмя точками.
Trapezoid::Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4, std::string description)
    : Figure(description) {
        // Координаты векторов сторон трапеции.
        Point AB = Point(p1.get_x() - p2.get_x(), p1.get_y() - p2.get_y());
        Point BC = Point(p2.get_x() - p3.get_x(), p2.get_y() - p3.get_y());
        Point CD = Point(p3.get_x() - p4.get_x(), p3.get_y() - p4.get_y());
        Point DA = Point(p4.get_x() - p1.get_x(), p4.get_y() - p1.get_y());
        // Проверка, что хотя бы одна пара противоположных сторон параллельна. Если векторное произведение равно нулю, то векторы параллельны.
        if (!((AB.get_x() * CD.get_y() - AB.get_y() * CD.get_x()) > 1e-10 ||
              (BC.get_x() * DA.get_y() - BC.get_y() * DA.get_x()) > 1e-10)) {
            throw std::invalid_argument("Invalid trapezoid points: at least one pair of opposite sides must be parallel.");
        }
        // Если проверки пройдены, сохраняем точки.
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
        points[3] = p4;
}

// Перегрузка операторов = копирования и перемещения.
// Конструктор копирования.
Trapezoid::Trapezoid(const Trapezoid& other) {
    for (int i = 0; i < 4; ++i) {
        points[i] = other.points[i];
    }
}
// Перегрузка копирования.
Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

// Конструктор перемещения.
Trapezoid::Trapezoid(Trapezoid&& other) noexcept {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::move(other.points[i]);
    }
}
// Перегрузка перемещения.
Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

// Перегрузка оператора сравниения ==.
bool Trapezoid::operator==(const Trapezoid& other) const {
    if (this->square() != other.square()) {
        return false;
    }
    return true;
}

// Перегрузка оператора сравнения <=>
std::partial_ordering Trapezoid::operator<=>(const Trapezoid& other) const {
    return this->square() <=> other.square();
}

Point Trapezoid::geometric_center() const {
    double center_x = (points[0].get_x() + points[2].get_x() + points[1].get_x() + points[3].get_x()) / 4.0;
    double center_y = (points[0].get_y() + points[2].get_y() + points[1].get_y() + points[3].get_y()) / 4.0;
    return Point(center_x, center_y);
}

// Вычисление площади трапеции с помощью формулы площади многоугольника.
/*
“Шнуровка” (формула Гаусса) для многоугольников Это универсальная формула для площади многоугольника по упорядоченным вершинам (по обходу).

Формула: S = 1/2 · |Σ_{i=1..n} (x_i·y_{i+1} − y_i·x_{i+1})|, где (x_{n+1}, y_{n+1}) = (x_1, y_1).

Для 4 точек A→B→C→D→A: S = 1/2 · |x_A y_B + x_B y_C + x_C y_D + x_D y_A − (y_A x_B + y_B x_C + y_C x_D + y_D x_A)|
*/
double Trapezoid::square() const {
    double square = 0.5 * fabs((points[0].get_x() * points[1].get_y() + points[1].get_x() * points[2].get_y() +
                          points[2].get_x() * points[3].get_y() + points[3].get_x() * points[0].get_y()) -
                    (points[1].get_x() * points[0].get_y() + points[2].get_x() * points[1].get_y() +
                           points[3].get_x() * points[2].get_y() + points[0].get_x() * points[3].get_y()));
    return square;
}

double Trapezoid::perimeter() const {
    double lenth1 = distance(points[0] ,points[1]);
    double length2 = distance(points[2], points[3]);
    double length3 = distance(points[1], points[2]);
    double length4 = distance(points[3], points[0]);
    return lenth1 + length2 + length3 + length4;
}

Trapezoid::operator double() const {
    return this->square();
}

void Trapezoid::print(std::ostream& os) const {
    for (const auto& point : points) {
        os << point << std::endl;
    }
}

void Trapezoid::read(std::istream& is) {
    for (auto& point : points) {
        is >> point;
    }
}

Figure* Trapezoid::clone() const {
    return new Trapezoid(this->points[0], this->points[1], this->points[2], this->points[3]);
}
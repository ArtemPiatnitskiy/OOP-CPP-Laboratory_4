#include "../include/rhombus.h"
#include "../include/point.h"
#include <compare>
#include <cmath>
#include <stdexcept>

// Конструктор с параметрами описания и четырьмя точками.
Rhombus::Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4, std::string description)
    : Figure(description) {
        // Координаты векторов сторон ромба.
        Point AB = Point(p1.get_x() - p2.get_x(), p1.get_y() - p2.get_y());
        Point BC = Point(p2.get_x() - p3.get_x(), p2.get_y() - p3.get_y());
        Point CD = Point(p3.get_x() - p4.get_x(), p3.get_y() - p4.get_y());
        Point DA = Point(p4.get_x() - p1.get_x(), p4.get_y() - p1.get_y());
        // Проверка, что все стороны равны.
        if (distance(p1, p2) != distance(p2, p3) ||
            distance(p2, p3) != distance(p3, p4) ||
            distance(p3, p4) != distance(p4, p1)) {
            throw std::invalid_argument("Invalid rhombus points: all sides must be of equal length.");
        }
        // Проверка, что соседние стороны параллельны. Если косинус угла между векторами равен 1, то векторы параллельны. Вариант с косинусом:
        /*
        else if (!(((fabs(AB.get_x() * CD.get_x() + AB.get_y() * CD.get_y()) / (distance(p1, p2) * distance(p3, p4))) - 1 < 1e-9) &&
                 ((fabs(DA.get_x() * BC.get_x() + DA.get_y() * BC.get_y()) / (distance(p2, p3) * distance(p4, p1))) - 1 < 1e-9))) {
            throw std::invalid_argument("Invalid rhombus points: adjacent sides must be non-parallel.");
        }
        */
        // Через векторное произведение для проверки порядка точек и непараллельности соседних сторон:
        else if (!((AB.get_x() * BC.get_y() - AB.get_y() * BC.get_x()) > 1e-10 &&
                   (BC.get_x() * CD.get_y() - BC.get_y() * CD.get_x()) > 1e-10 &&
                   (CD.get_x() * DA.get_y() - CD.get_y() * DA.get_x()) > 1e-10 &&
                   (DA.get_x() * AB.get_y() - DA.get_y() * AB.get_x()) > 1e-10)) {
            throw std::invalid_argument("Invalid rhombus points: adjacent sides must be non-parallel and ordered correctly.");
        }
        // Если проверки пройдены, сохраняем точки.
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
        points[3] = p4;
}

// Перегрузка операторов = копирования и перемещения.
// Конструктор копирования.
Rhombus::Rhombus(const Rhombus& other) {
    for (int i = 0; i < 4; ++i) {
        points[i] = other.points[i];
    }
}
// Перегрузка копирования.
Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

// Конструктор перемещения.
Rhombus::Rhombus(Rhombus&& other) noexcept {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::move(other.points[i]);
    }
}
// Перегрузка перемещения.
Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

// Перегрузка оператора сравниения ==.
bool Rhombus::operator==(const Rhombus& other) const {
    if (this->square() != other.square()) {
        return false;
    }
    return true;
}

// Перегрузка оператора сравнения <=>
std::partial_ordering Rhombus::operator<=>(const Rhombus& other) const {
    return this->square() <=> other.square();
}

Point Rhombus::geometric_center() const {
    double center_x = (points[0].get_x() + points[2].get_x() + points[1].get_x() + points[3].get_x()) / 4.0;
    double center_y = (points[0].get_y() + points[2].get_y() + points[1].get_y() + points[3].get_y()) / 4.0;
    return Point(center_x, center_y);
}

double Rhombus::square() const {
    double diagonal1 = distance(points[0], points[2]);
    double diagonal2 = distance(points[1], points[3]);
    return (diagonal1 * diagonal2) / 2.0;
}

double Rhombus::perimeter() const {
    double length = distance(points[0], points[1]);
    double width = distance(points[0], points[3]);
    return 2 * (length + width);
}

Rhombus::operator double() const {
    return this->square();
}

void Rhombus::print(std::ostream& os) const {
    for (const auto& point : points) {
        os << point << std::endl;
    }
}

void Rhombus::read(std::istream& is) {
    for (auto& point : points) {
        is >> point;
    }
}

Figure* Rhombus::clone() const {
    return new Rhombus(this->points[0], this->points[1], this->points[2], this->points[3]);
}
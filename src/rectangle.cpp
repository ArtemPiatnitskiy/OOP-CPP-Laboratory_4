#include "../include/rectangle.h"
#include "../include/point.h"
#include <stdexcept>

// Конструктор с параметрами описания и двумя точками противоположных углов.
Rectangle::Rectangle(const Point& p1, const Point& p2, std::string description)
    : Figure(description) {
        if (p1.get_x() == p2.get_x() || p1.get_y() == p2.get_y()) {
            throw std::invalid_argument("Invalid rectangle points: points must not be aligned vertically or horizontally.");
        }
    points[0] = p1;
    points[1] = Point(p2.get_x(), p1.get_y());
    points[2] = p2;
    points[3] = Point(p1.get_x(), p2.get_y());
}

// Перегрузка операторов = копирования и перемещения.
// Конструктор копирования.
Rectangle::Rectangle(const Rectangle& other) {
    for (int i = 0; i < 4; ++i) {
        points[i] = other.points[i];
    }
}
// Перегрузка копирования.
Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

// Конструктор перемещения.
Rectangle::Rectangle(Rectangle&& other) noexcept {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::move(other.points[i]);
    }
}
// Перегрузка перемещения.
Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

// Перегрузка оператора сравниения ==.
bool Rectangle::operator==(const Rectangle& other) const {
    if (this->square() != other.square()) {
        return false;
    }
    return true;
}

// Перегрузка оператора сравнения <=>
std::partial_ordering Rectangle::operator<=>(const Rectangle& other) const {
    return this->square() <=> other.square();
}

Point Rectangle::geometric_center() const {
    double center_x = (points[0].get_x() + points[2].get_x()) / 2.0;
    double center_y = (points[0].get_y() + points[2].get_y()) / 2.0;
    return Point(center_x, center_y);
}

double Rectangle::square() const {
    double length = distance(points[0], points[1]);
    double width = distance(points[0], points[3]);
    return length * width;
}

double Rectangle::perimeter() const {
    double length = distance(points[0], points[1]);
    double width = distance(points[0], points[3]);
    return 2 * (length + width);
}

Rectangle::operator double() const {
    return this->square();
}

void Rectangle::print(std::ostream& os) const {
    for (const auto& point : points) {
        os << point << std::endl;
    }
}

void Rectangle::read(std::istream& is) {
    for (auto& point : points) {
        is >> point;
    }
}

Figure* Rectangle::clone() const {
    return new Rectangle(this->points[0], this->points[2]);
}
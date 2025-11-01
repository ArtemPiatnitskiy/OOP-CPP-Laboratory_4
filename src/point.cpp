#include "../include/point.h"
#include <iostream>
#include <cmath>

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.point_x << ", " << point.point_y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point& point) {
    char delimetr;
    double x, y;
    if (is >> delimetr >> x >> delimetr >> y >> delimetr) {
        point.point_x = x;
        point.point_y = y;
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

double distance(const Point& p1, const Point& p2) {
    double dx = p2.get_x() - p1.get_x();
    double dy = p2.get_y() - p1.get_y();
    return std::sqrt(dx * dx + dy * dy);
}

Point::Point(double p_x, double p_y): point_x(p_x), point_y(p_y) {}

double Point::get_x() const {
    return point_x;
}

double Point::get_y() const {
    return point_y;
}

void Point::move(double new_x, double new_y) {
    point_x = new_x;
    point_y = new_y;
}
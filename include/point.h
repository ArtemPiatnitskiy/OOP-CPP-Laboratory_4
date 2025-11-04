#pragma once
#include <iostream>
#include <iterator>
#include <cmath>

// Концепт для проверки, что тип является скалярным (числовым).
template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

// Класс для представления точки в пространстве, используя концепт Scalar.
template<Scalar T>
class Point {
    // Аналогично классу Figure, перегружаем операторы ввода/вывода.
    // Функции объявлены как friend, чтобы иметь доступ к приватным членам класса.

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.point_x << ", " << point.point_y << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point& point) {
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

    // Функция для нахождения расстояния между двумя точками.
    // Является friend функцией, чтобы иметь доступ к приватным членам класса.
    // Friend позволяет не давать приоритет левому значению, как в случае с методом класса (this->point_x + p.point_x).
    friend double distance(const Point& p1, const Point& p2) {
        double dx = p2.get_x() - p1.get_x();
        double dy = p2.get_y() - p1.get_y();
        return std::sqrt(dx * dx + dy * dy);
    }

    public:
        // Конструктор по умолчанию.
        Point() = default;
        // Конструктор с параметрами координат точки.
        Point(T p_x, T p_y): point_x(p_x), point_y(p_y) {}

        // Геттеры для координат точки.
        // Получить координату X.
        T get_x() const{
            return point_x;
        };
        // Получить координату Y.
        T get_y() const{
            return point_y;
        };

        // Функция для перемещения точки на новые координаты.
        // Не const, так как мы изменяем состояние объекта.
        void move(T new_x, T new_y){
            point_x = new_x;
            point_y = new_y;
        };


    private:
        // Координаты точки.
        T point_x{0};
        T point_y{0};


};

#pragma once
#include <iostream>


class Point {
    // Аналогично классу Figure, перегружаем операторы ввода/вывода.
    // Функции объявлены как friend, чтобы иметь доступ к приватным членам класса.
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
    friend std::istream& operator>>(std::istream& is, Point& point);

    // Функция для нахождения расстояния между двумя точками.
    // Является friend функцией, чтобы иметь доступ к приватным членам класса.
    // Friend позволяет не давать приоритет левому значению, как в случае с методом класса (this->point_x + p.point_x).
    friend double distance (const Point& p1, const Point& p2);

    public:
        // Конструктор по умолчанию.
        Point() = default;
        // Конструктор с параметрами координат точки.
        Point(double point_x, double point_y);

        // Геттеры для координат точки.
        // Получить координату X.
        double get_x() const;
        // Получить координату Y.
        double get_y() const;

        // Функция для перемещения точки на новые координаты.
        // Не const, так как мы изменяем состояние объекта.
        void move(double new_x, double new_y);



    private:
        // Координаты точки.
        double point_x{0};
        double point_y{0};


};

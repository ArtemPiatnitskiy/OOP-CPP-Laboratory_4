#pragma once
#include <memory>
#include <string>
#include "point.h"
#include "figure.h"
#include <cmath>
#include <stdexcept>
#include <iostream>


template<Scalar T>
class Hexagon : public Figure<T> {
    public:
        // Конструктор по умолчанию.
        Hexagon() : Figure<T>("hexagon") {};
        // Конструктор точками.
        Hexagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5, const Point<T>& p6, std::string description = "hexagon")
            : Figure<T>(description) {
                // Координаты векторов сторон шестиугольника.
                Point AB = Point(p1.get_x() - p2.get_x(), p1.get_y() - p2.get_y());
                Point BC = Point(p2.get_x() - p3.get_x(), p2.get_y() - p3.get_y());
                Point CD = Point(p3.get_x() - p4.get_x(), p3.get_y() - p4.get_y());
                Point DE = Point(p4.get_x() - p5.get_x(), p4.get_y() - p5.get_y());
                Point EF = Point(p5.get_x() - p6.get_x(), p5.get_y() - p6.get_y());
                Point FA = Point(p6.get_x() - p1.get_x(), p6.get_y() - p1.get_y());
                // Проверка, что все стороны равны (с учётом небольшой погрешности)
                const double SIDE_EPS = 1e-6;
                if (std::fabs(distance(p1, p2) - distance(p2, p3)) > SIDE_EPS ||
                    std::fabs(distance(p2, p3) - distance(p3, p4)) > SIDE_EPS ||
                    std::fabs(distance(p3, p4) - distance(p4, p5)) > SIDE_EPS ||
                    std::fabs(distance(p4, p5) - distance(p5, p6)) > SIDE_EPS ||
                    std::fabs(distance(p5, p6) - distance(p6, p1)) > SIDE_EPS) {
                    throw std::invalid_argument("Invalid hexagon points: all sides must be equal.");
                }
                // Проверка, что мы можем вписать правильный шестиугольник в окружность
                Point<T> center = Point<T>((p1.get_x() + p2.get_x() + p3.get_x() + p4.get_x() + p5.get_x() + p6.get_x()) / 6.0,
                                                   (p1.get_y() + p2.get_y() + p3.get_y() + p4.get_y() + p5.get_y() + p6.get_y()) / 6.0);
                double radius = distance(center, p1);
                const double CONCYCLIC_EPS = 1e-6;
                for (const auto& point : {p1, p2, p3, p4, p5, p6}) {
                    if (std::fabs(distance(center, point) - radius) > CONCYCLIC_EPS) {
                        throw std::invalid_argument("Invalid hexagon points: points must be concyclic.");
                    }
                }
                // Если проверки пройдены, сохраняем точки.
                points[0] = std::make_unique<Point<T>>(p1);
                points[1] = std::make_unique<Point<T>>(p2);
                points[2] = std::make_unique<Point<T>>(p3);
                points[3] = std::make_unique<Point<T>>(p4);
                points[4] = std::make_unique<Point<T>>(p5);
                points[5] = std::make_unique<Point<T>>(p6);
        };

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Hexagon(const Hexagon& other){
            for (int i = 0; i < 6; ++i) {
                points[i] = std::make_unique<Point<T>>(*other.points[i]);
            }
        };
        // Перегрузка копирования.
        Hexagon& operator=(const Hexagon& other) {
            if (this != &other) {
                for (int i = 0; i < 6; ++i) {
                    points[i] = std::make_unique<Point<T>>(*other.points[i]);
                }
            }
            return *this;
        };
        // Конструктор перемещения.
        Hexagon(Hexagon&& other) noexcept {
            if (this != &other) {
                for (int i = 0; i < 6; ++i) {
                    points[i] = std::move(other.points[i]);
                }
            }
        };
        // Перегрузка перемещения.
        Hexagon& operator=(Hexagon&& other) noexcept {
            if (this != &other) {
                for (int i = 0; i < 6; ++i) {
                    points[i] = std::move(other.points[i]);
                }
            }
            return *this;
        };

        // Перегрузка оператора сравниения ==.
        bool operator==(const Hexagon& other) const {
            // Сравниваем площади с учётом погрешности
            return std::abs(this->square() - other.square()) < 1e-9;
        };
        // Перегрузка оператора сравнения <=>
        std::partial_ordering operator<=>(const Hexagon& other) const {
            return this->square() <=> other.square();
        };

        // Переопределение виртуальных методов базового класса.
        std::unique_ptr<Point<T>> geometric_center() const override {
            double center_x = (points[0]->get_x() + points[2]->get_x() + points[1]->get_x() + points[3]->get_x() + points[4]->get_x() + points[5]->get_x()) / 6.0;
            double center_y = (points[0]->get_y() + points[2]->get_y() + points[1]->get_y() + points[3]->get_y() + points[4]->get_y() + points[5]->get_y()) / 6.0;
            return std::make_unique<Point<T>>(center_x, center_y);
        };
        // Вычисление площади трапеции с помощью формулы площади многоугольника.
        /*
        “Шнуровка” (формула Гаусса) для многоугольников Это универсальная формула для площади многоугольника по упорядоченным вершинам (по обходу).

        Формула: S = 1/2 · |Σ_{i=1..n} (x_i·y_{i+1} − y_i·x_{i+1})|, где (x_{n+1}, y_{n+1}) = (x_1, y_1).

        Для 4 точек A→B→C→D→A: S = 1/2 · |x_A y_B + x_B y_C + x_C y_D + x_D y_A − (y_A x_B + y_B x_C + y_C x_D + y_D x_A)|
        */
        double square() const override {
            double sum = 0.0;
            for (int i = 0; i < 6; ++i) {
                int next = (i + 1) % 6;
                sum += (points[i]->get_x() * points[next]->get_y() - 
                        points[i]->get_y() * points[next]->get_x());
            }
            return std::fabs(sum) / 2.0;
        };
        // Вычисление периметра шестиугольника.
        double perimeter() const override{
            double res = 0;
            for (int i = 0; i < 6; ++i) {
                res += distance(*points[i], *points[(i + 1) % 6]);
            }
            return res;
        };

        // Функция для нахождения площади фигуры через перегрузку оператора double().
        // Возвращает площадь фигуры.
        // Мы не используем explicit здесь, чтобы позволить неявное преобразование к double.
        operator double() const override{
            return this->square();
        };

        // Перегрузка операторов ввода/вывода.
        void print(std::ostream& os) const override{
            for (const auto& point : points) {
                os << *point << std::endl;
            }
        };
        void read(std::istream& is) override{
            Point<T> temp;
            for (auto& point : points) {
                is >> temp;
                point = std::make_unique<Point<T>>(temp);
            }
        };

        // Функция для клонирования фигуры.
        std::shared_ptr<Figure<T>> clone() const override{
            return std::make_shared<Hexagon<T>>(*points[0], *points[1], *points[2], *points[3], *points[4], *points[5]);
        };

    private:
        std::unique_ptr<Point<T>> points[6];

};
#pragma once
#include <memory>
#include <string>
#include "point.h"
#include "figure.h"
#include <compare>
#include <cmath>
#include <stdexcept>


template<Scalar T>  
class Rhombus : public Figure<T> {
    public:
        // Конструктор по умолчанию.
        Rhombus() : Figure<T>("rhombus") {};
        // Конструктор точками.
        Rhombus(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, std::string description = "rhombus")
        : Figure<T>(description) {
            // Координаты векторов сторон ромба.
            Point<T> AB = Point<T>(p1.get_x() - p2.get_x(), p1.get_y() - p2.get_y());
            Point<T> BC = Point<T>(p2.get_x() - p3.get_x(), p2.get_y() - p3.get_y());
            Point<T> CD = Point<T>(p3.get_x() - p4.get_x(), p3.get_y() - p4.get_y());
            Point<T> DA = Point<T>(p4.get_x() - p1.get_x(), p4.get_y() - p1.get_y());
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
            else if (!(std::fabs((AB.get_x() * BC.get_y() - AB.get_y() * BC.get_x())) > 1e-10 &&
                    std::fabs((BC.get_x() * CD.get_y() - BC.get_y() * CD.get_x())) > 1e-10 &&
                    std::fabs((CD.get_x() * DA.get_y() - CD.get_y() * DA.get_x())) > 1e-10 &&
                    std::fabs((DA.get_x() * AB.get_y() - DA.get_y() * AB.get_x())) > 1e-10)) {
                throw std::invalid_argument("Invalid rhombus points: adjacent sides must be non-parallel and ordered correctly.");
            }
            // Если проверки пройдены, сохраняем точки.
            points[0] = std::make_unique<Point<T>>(p1);
            points[1] = std::make_unique<Point<T>>(p2);
            points[2] = std::make_unique<Point<T>>(p3);
            points[3] = std::make_unique<Point<T>>(p4);
        };

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Rhombus(const Rhombus& other) {
            for (int i = 0; i < 4; ++i) {
                points[i] = std::make_unique<Point<T>>(*other.points[i]);
            }
        };

        // Перегрузка копирования.
        Rhombus& operator=(const Rhombus& other) {
            if (this != &other) {
                for (int i = 0; i < 4; ++i) {
                    points[i] = std::make_unique<Point<T>>(*other.points[i]);
                }
            }
            return *this;
        };
        // Конструктор перемещения.
        Rhombus(Rhombus&& other) noexcept {
            for (int i = 0; i < 4; ++i) {
                points[i] = std::move(other.points[i]);
            }
        };
        // Перегрузка перемещения.
        Rhombus& operator=(Rhombus&& other) noexcept {
            if (this != &other) {
                for (int i = 0; i < 4; ++i) {
                    points[i] = std::move(other.points[i]);
                }
            }
            return *this;
        };

        // Перегрузка оператора сравнения ==.
        bool operator==(const Rhombus& other) const {
            // Сравниваем площади с учётом погрешности
            return std::abs(this->square() - other.square()) < 1e-9;
        };

        // Перегрузка оператора сравнения <=>
        std::partial_ordering operator<=>(const Rhombus& other) const {
            return this->square() <=> other.square();
        };

        // Переопределение виртуальных методов базового класса.
        std::unique_ptr<Point<T>> geometric_center() const override{
            double center_x = (points[0]->get_x() + points[2]->get_x() + points[1]->get_x() + points[3]->get_x()) / 4.0;
            double center_y = (points[0]->get_y() + points[2]->get_y() + points[1]->get_y() + points[3]->get_y()) / 4.0;
            return std::make_unique<Point<T>>(center_x, center_y);
        };
        double square() const override{
            double diagonal1 = distance(*points[0], *points[2]);
            double diagonal2 = distance(*points[1], *points[3]);
            return (diagonal1 * diagonal2) / 2.0;
        };
        double perimeter() const override{
            double length = distance(*points[0], *points[1]);
            double width = distance(*points[0], *points[3]);
            return 2 * (length + width);
        };

        operator double() const override {
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
            return std::make_shared<Rhombus>(*points[0], *points[1], *points[2], *points[3]);
        };

    private:
        std::unique_ptr<Point<T>> points[4];

};
#pragma once
#include <iostream>
#include "point.h"
#include <memory>
#include <string_view>
#include <string>
#include <ostream>

template<Scalar T> 
class Figure {
    // Функция перегрузки оператора вывода. Является friend функций, чтобы иметь доступ к приватным членам классса.
    // Функция будет возвращать ссылку на поток вывода для возможности цепочки выводов.
    // Пример использования:
    // Figure fig;
    // std::cout << fig << std::endl;
    friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
        os << figure.description << ":\n";
        figure.print(os);
        return os;
    }
    // Аналогичная функция перегрузки оператора ввода.
    // Не const, так как мы будем изменять объект figure при вводе данных.
    friend std::istream& operator>>(std::istream& is, Figure& figure) {
        figure.read(is);
        return is;
    };
    protected:
        // Конструкторы защищены, чтобы нельзя было создать объект базового класса напрямую.
        // Это абстрактный класс.
        // Конструктор по умолчанию.
        Figure() = default;
        // Конструктор с параметром описания фигуры.
        Figure(std::string_view descrip) : description(descrip) {};

        // Функции для реализации логики операторов ввода/вывода в наследниках.

        virtual void print(std::ostream& os) const = 0;
        virtual void read(std::istream& is) = 0;


    public:
        // Виртуальный деструктор.
        virtual ~Figure() = default;

        // Функция для нахождения геометрического центра фигуры.
        virtual std::unique_ptr<Point<T>> geometric_center() const = 0;
        // Функция для нахождения площади фигуры.
        virtual double square() const = 0;
        // Функция для нахождения периметра фигуры.
        virtual double perimeter() const = 0;

        virtual std::shared_ptr<Figure<T>> clone() const = 0;

        virtual operator double() const = 0;

    
    
    private:
        std::string description = "Figure";


};
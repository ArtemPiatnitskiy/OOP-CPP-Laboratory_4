#include <iostream>
#include <sstream>
#include <utility>
#include "include/point.h"
#include "include/rectangle.h"
#include "include/trapezoid.h"
#include "include/rhombus.h"
#include "include/arrayoffigures.h"

int main() {
    using std::cout;
    using std::endl;

    // --- Точки ---
    Point p1(0.0, 0.0);
    Point p2(3.0, 0.0);
    Point p3(3.0, 4.0);
    Point p4(0.0, 4.0);

    cout << "Точки: " << p1 << " " << p2 << " " << p3 << " " << p4 << endl;
    cout << "Расстояние между p1 и p3: " << distance(Point(0, 1), Point(-1, 0)) << endl;

    // --- Тесты прямоугольника ---
    Rectangle r1(p1, p3); // задаём по диагональным точкам
    cout << "Прямоугольник r1:" << endl << r1 << endl;
    cout << "  центр: " << r1.geometric_center() << endl;
    cout << "  площадь: " << r1.square() << " периметр: " << r1.perimeter() << endl;
    cout << "  приведение к double (площадь): " << static_cast<double>(r1) << endl;
    cout << "  r1 == r1: " << std::boolalpha << (r1 == r1) << endl;

    // Прямоугольник по умолчанию + чтение из потока
    Rectangle r2; // предполагается, что есть конструктор по умолчанию
    std::istringstream rin("(0,0) (3,0) (3,4) (0,4)");
    rin >> r2; // читаем 4 точки
    cout << "Прямоугольник r2 (прочитан):" << endl << r2 << endl;
    cout << "  r1 == r2 (площади равны?): " << std::boolalpha << (r1 == r2) << endl;

    // --- Трапеция и ромб ---
    Trapezoid t1(p1, p2, p3, p4);
    cout << "Трапеция t1:" << endl << t1 << endl;
    cout << "  площадь t1: " << t1.square() << " периметр: " << t1.perimeter() << endl;

    Rhombus h1(p1, p2, p3, p4);
    cout << "Ромб h1:" << endl << h1 << endl;
    cout << "  площадь h1: " << h1.square() << " периметр: " << h1.perimeter() << endl;

    // --- Тест clone() ---
    Figure* rc = r1.clone();
    Figure* tc = t1.clone();
    Figure* hc = h1.clone();
    cout << "Клонированные фигуры:" << endl;
    cout << *rc << endl << *tc << endl << *hc << endl;
    delete rc; delete tc; delete hc;

    // --- Тесты ArrayOfFigures: add / print / total / remove ---
    ArrayOfFigures arr(2);
    arr.add_figure(r1.clone());
    arr.add_figure(t1.clone());
    arr.add_figure(h1.clone()); // должен сработать resize
    cout << "Массив после добавления (size=" << arr.get_size() << ", cap=" << arr.get_capacity() << "):" << endl;
    arr.print_figures(std::cout);
    cout << "Общая площадь: " << arr.total_square() << endl;

    // копирование
    ArrayOfFigures arr_copy = arr;
    cout << "Скопированный массив (size=" << arr_copy.get_size() << "):" << endl;
    arr_copy.print_figures(std::cout);

    // перемещение
    ArrayOfFigures arr_moved = std::move(arr);
    cout << "Перемещённый массив (новый владелец size=" << arr_moved.get_size()
         << "), исходный размер=" << arr.get_size() << endl;
    arr_moved.print_figures(std::cout);

    // оператор присваивания (копирование)
    ArrayOfFigures arr_assign(1);
    arr_assign = arr_copy;
    cout << "После copy-assignment arr_assign size=" << arr_assign.get_size() << endl;

    // оператор присваивания (перемещение)
    ArrayOfFigures arr_move_assign(1);
    arr_move_assign = std::move(arr_copy);
    cout << "После move-assignment arr_move_assign size=" << arr_move_assign.get_size()
         << ", arr_copy size=" << arr_copy.get_size() << endl;

    // доступ через operator[] и удаление элемента
    if (arr_moved.get_size() > 0) {
        Figure* f0 = arr_moved[0];
        cout << "Первый элемент arr_moved через operator[]:" << endl;
        if (f0) cout << *f0 << endl;
    }
    if (arr_moved.get_size() > 1) {
        cout << "Удаляем элемент с индексом 1 из arr_moved" << endl;
        arr_moved.remove_figure(1);
        cout << "После удаления, размер=" << arr_moved.get_size() << endl;
        arr_moved.print_figures(std::cout);
    }

    cout << "Все проверки завершены." << endl;
    return 0;
}
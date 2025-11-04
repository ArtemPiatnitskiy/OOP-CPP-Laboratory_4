#include <iostream>
#include <sstream>
#include <utility>
#include <cmath>
#include "include/point.h"
#include "include/pentagon.h"
#include "include/hexagon.h"
#include "include/rhombus.h"
#include "include/arrayoffigures.h"

int main() {
    using std::cout;
    using std::endl;

    cout << "Laboratory 4" << endl << endl;

    // Создаём ромб
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    Rhombus<double> rhombus(p1, p2, p3, p4);
    cout << "Rhombus:" << endl << rhombus << endl;
    cout << "  Area: " << rhombus.square() << " Perimeter: " << rhombus.perimeter() << endl;
    
    // Создаём пятиугольник
    double radius = 1.0;
    Point<double> pp1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> pp2(radius * std::cos(72 * M_PI / 180), radius * std::sin(72 * M_PI / 180));
    Point<double> pp3(radius * std::cos(144 * M_PI / 180), radius * std::sin(144 * M_PI / 180));
    Point<double> pp4(radius * std::cos(216 * M_PI / 180), radius * std::sin(216 * M_PI / 180));
    Point<double> pp5(radius * std::cos(288 * M_PI / 180), radius * std::sin(288 * M_PI / 180));
    
    Pentagon<double> pentagon(pp1, pp2, pp3, pp4, pp5);
    cout << "Pentagon:" << endl << pentagon << endl;
    cout << "  Area: " << pentagon.square() << " Perimeter: " << pentagon.perimeter() << endl;
    
    // Создаём шестиугольник
    Point<double> ph1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> ph2(radius * std::cos(60 * M_PI / 180), radius * std::sin(60 * M_PI / 180));
    Point<double> ph3(radius * std::cos(120 * M_PI / 180), radius * std::sin(120 * M_PI / 180));
    Point<double> ph4(radius * std::cos(180 * M_PI / 180), radius * std::sin(180 * M_PI / 180));
    Point<double> ph5(radius * std::cos(240 * M_PI / 180), radius * std::sin(240 * M_PI / 180));
    Point<double> ph6(radius * std::cos(300 * M_PI / 180), radius * std::sin(300 * M_PI / 180));
    
    Hexagon<double> hexagon(ph1, ph2, ph3, ph4, ph5, ph6);
    cout << "Hexagon:" << endl << hexagon << endl;
    cout << "  Area: " << hexagon.square() << " Perimeter: " << hexagon.perimeter() << endl;
    
    // Создаём массив фигур
    ArrayOfFigures<Figure<double>> arr(3);
    arr.add_figure(std::make_shared<Rhombus<double>>(rhombus));
    arr.add_figure(std::make_shared<Pentagon<double>>(pentagon));
    arr.add_figure(std::make_shared<Hexagon<double>>(hexagon));
    
    cout << endl << "=== Array of Figures ===" << endl;
    cout << "Size: " << arr.get_size() << endl;
    cout << "Total area: " << arr.total_square() << endl;

    cout << endl << "All tests completed successfully!" << endl;
    return 0;
}
#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include "../include/hexagon.h"
#include "../include/point.h"

// Константа для сравнения чисел с плавающей точкой
static constexpr double EPS = 1e-6;

// ============================================================================
// ТЕСТЫ ДЛЯ КЛАССА HEXAGON (Правильный шестиугольник)
// ============================================================================

// Тест 1: Создание правильного шестиугольника
TEST(HexagonTest, ValidConstructorAndBasicMethods) {
    // Создаём правильный шестиугольник с центром в (0,0) и радиусом 1
    // Вершины расположены через угол 60 градусов (360/6)
    double radius = 1.0;
    Point<double> p1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> p2(radius * std::cos(60 * M_PI / 180), radius * std::sin(60 * M_PI / 180));
    Point<double> p3(radius * std::cos(120 * M_PI / 180), radius * std::sin(120 * M_PI / 180));
    Point<double> p4(radius * std::cos(180 * M_PI / 180), radius * std::sin(180 * M_PI / 180));
    Point<double> p5(radius * std::cos(240 * M_PI / 180), radius * std::sin(240 * M_PI / 180));
    Point<double> p6(radius * std::cos(300 * M_PI / 180), radius * std::sin(300 * M_PI / 180));
    
    Hexagon<double> hexagon(p1, p2, p3, p4, p5, p6);
    
    // Проверка, что площадь больше 0
    EXPECT_GT(hexagon.square(), 0.0);
    
    // Проверка периметра (6 равных сторон)
    double side_length = distance(p1, p2);
    EXPECT_NEAR(hexagon.perimeter(), 6.0 * side_length, EPS);
    
    // Проверка центра (должен быть около (0, 0))
    auto center = hexagon.geometric_center();
    EXPECT_NEAR(center->get_x(), 0.0, EPS);
    EXPECT_NEAR(center->get_y(), 0.0, EPS);
}

// Тест 2: Проверка, что конструктор бросает исключение для неравных сторон
TEST(HexagonTest, InvalidHexagonUnequalSides) {
    // Пытаемся создать шестиугольник с неравными сторонами
    Point<double> p1(0.0, 0.0);
    Point<double> p2(1.0, 0.0);
    Point<double> p3(2.0, 0.5);
    Point<double> p4(2.0, 1.5);
    Point<double> p5(1.0, 2.0);
    Point<double> p6(0.0, 1.5);
    
    EXPECT_THROW({
        Hexagon<double> hexagon(p1, p2, p3, p4, p5, p6);
    }, std::invalid_argument);
}

// Тест 3: Проверка, что точки не на одной окружности бросают исключение
TEST(HexagonTest, InvalidHexagonNotConcyclic) {
    // Создаём 6 точек с равными сторонами, но не на окружности
    Point<double> p1(0.0, 0.0);
    Point<double> p2(1.0, 0.0);
    Point<double> p3(2.0, 0.0);
    Point<double> p4(3.0, 0.0);
    Point<double> p5(4.0, 0.0);
    Point<double> p6(5.0, 0.0);
    
    EXPECT_THROW({
        Hexagon<double> hexagon(p1, p2, p3, p4, p5, p6);
    }, std::invalid_argument);
}

// Тест 4: Проверка оператора приведения к double
TEST(HexagonTest, OperatorDoubleConversion) {
    double radius = 2.0;
    Point<double> p1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> p2(radius * std::cos(60 * M_PI / 180), radius * std::sin(60 * M_PI / 180));
    Point<double> p3(radius * std::cos(120 * M_PI / 180), radius * std::sin(120 * M_PI / 180));
    Point<double> p4(radius * std::cos(180 * M_PI / 180), radius * std::sin(180 * M_PI / 180));
    Point<double> p5(radius * std::cos(240 * M_PI / 180), radius * std::sin(240 * M_PI / 180));
    Point<double> p6(radius * std::cos(300 * M_PI / 180), radius * std::sin(300 * M_PI / 180));
    
    Hexagon<double> hexagon(p1, p2, p3, p4, p5, p6);
    
    double area = static_cast<double>(hexagon);
    EXPECT_NEAR(area, hexagon.square(), EPS);
}

// Тест 5: Проверка конструктора копирования
TEST(HexagonTest, CopyConstructor) {
    double radius = 1.0;
    Point<double> p1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> p2(radius * std::cos(60 * M_PI / 180), radius * std::sin(60 * M_PI / 180));
    Point<double> p3(radius * std::cos(120 * M_PI / 180), radius * std::sin(120 * M_PI / 180));
    Point<double> p4(radius * std::cos(180 * M_PI / 180), radius * std::sin(180 * M_PI / 180));
    Point<double> p5(radius * std::cos(240 * M_PI / 180), radius * std::sin(240 * M_PI / 180));
    Point<double> p6(radius * std::cos(300 * M_PI / 180), radius * std::sin(300 * M_PI / 180));
    
    Hexagon<double> hexagon1(p1, p2, p3, p4, p5, p6);
    Hexagon<double> hexagon2(hexagon1);
    
    EXPECT_NEAR(hexagon1.square(), hexagon2.square(), EPS);
    EXPECT_TRUE(hexagon1 == hexagon2);
}

// Тест 6: Проверка оператора присваивания
TEST(HexagonTest, CopyAssignmentOperator) {
    double radius = 1.5;
    Point<double> p1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> p2(radius * std::cos(60 * M_PI / 180), radius * std::sin(60 * M_PI / 180));
    Point<double> p3(radius * std::cos(120 * M_PI / 180), radius * std::sin(120 * M_PI / 180));
    Point<double> p4(radius * std::cos(180 * M_PI / 180), radius * std::sin(180 * M_PI / 180));
    Point<double> p5(radius * std::cos(240 * M_PI / 180), radius * std::sin(240 * M_PI / 180));
    Point<double> p6(radius * std::cos(300 * M_PI / 180), radius * std::sin(300 * M_PI / 180));
    
    Hexagon<double> hexagon1(p1, p2, p3, p4, p5, p6);
    Hexagon<double> hexagon2;
    
    hexagon2 = hexagon1;
    
    EXPECT_NEAR(hexagon1.square(), hexagon2.square(), EPS);
}

// Тест 7: Проверка конструктора перемещения
TEST(HexagonTest, MoveConstructor) {
    double radius = 1.0;
    Point<double> p1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> p2(radius * std::cos(60 * M_PI / 180), radius * std::sin(60 * M_PI / 180));
    Point<double> p3(radius * std::cos(120 * M_PI / 180), radius * std::sin(120 * M_PI / 180));
    Point<double> p4(radius * std::cos(180 * M_PI / 180), radius * std::sin(180 * M_PI / 180));
    Point<double> p5(radius * std::cos(240 * M_PI / 180), radius * std::sin(240 * M_PI / 180));
    Point<double> p6(radius * std::cos(300 * M_PI / 180), radius * std::sin(300 * M_PI / 180));
    
    Hexagon<double> hexagon1(p1, p2, p3, p4, p5, p6);
    double area_before = hexagon1.square();
    
    Hexagon<double> hexagon2(std::move(hexagon1));
    
    EXPECT_NEAR(hexagon2.square(), area_before, EPS);
}

// Тест 8: Проверка метода clone()
TEST(HexagonTest, CloneMethod) {
    double radius = 2.0;
    Point<double> p1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> p2(radius * std::cos(60 * M_PI / 180), radius * std::sin(60 * M_PI / 180));
    Point<double> p3(radius * std::cos(120 * M_PI / 180), radius * std::sin(120 * M_PI / 180));
    Point<double> p4(radius * std::cos(180 * M_PI / 180), radius * std::sin(180 * M_PI / 180));
    Point<double> p5(radius * std::cos(240 * M_PI / 180), radius * std::sin(240 * M_PI / 180));
    Point<double> p6(radius * std::cos(300 * M_PI / 180), radius * std::sin(300 * M_PI / 180));
    
    Hexagon<double> hexagon1(p1, p2, p3, p4, p5, p6);
    
    auto cloned = hexagon1.clone();
    
    EXPECT_NEAR(hexagon1.square(), cloned->square(), EPS);
}

// Тест 9: Проверка оператора сравнения ==
TEST(HexagonTest, EqualityOperator) {
    double radius = 1.0;
    Point<double> p1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> p2(radius * std::cos(60 * M_PI / 180), radius * std::sin(60 * M_PI / 180));
    Point<double> p3(radius * std::cos(120 * M_PI / 180), radius * std::sin(120 * M_PI / 180));
    Point<double> p4(radius * std::cos(180 * M_PI / 180), radius * std::sin(180 * M_PI / 180));
    Point<double> p5(radius * std::cos(240 * M_PI / 180), radius * std::sin(240 * M_PI / 180));
    Point<double> p6(radius * std::cos(300 * M_PI / 180), radius * std::sin(300 * M_PI / 180));
    
    Hexagon<double> hexagon1(p1, p2, p3, p4, p5, p6);
    Hexagon<double> hexagon2(p1, p2, p3, p4, p5, p6);
    
    EXPECT_TRUE(hexagon1 == hexagon2);
}

// Тест 10: Проверка вывода
TEST(HexagonTest, OutputOperator) {
    double radius = 1.0;
    Point<double> p1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> p2(radius * std::cos(60 * M_PI / 180), radius * std::sin(60 * M_PI / 180));
    Point<double> p3(radius * std::cos(120 * M_PI / 180), radius * std::sin(120 * M_PI / 180));
    Point<double> p4(radius * std::cos(180 * M_PI / 180), radius * std::sin(180 * M_PI / 180));
    Point<double> p5(radius * std::cos(240 * M_PI / 180), radius * std::sin(240 * M_PI / 180));
    Point<double> p6(radius * std::cos(300 * M_PI / 180), radius * std::sin(300 * M_PI / 180));
    
    Hexagon<double> hexagon(p1, p2, p3, p4, p5, p6);
    
    std::ostringstream oss;
    oss << hexagon;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("hexagon") != std::string::npos);
}

// Тест 11: Проверка формулы площади правильного шестиугольника
// Площадь правильного шестиугольника: S = (3√3/2) * a²,  где a - сторона
// Для радиуса R: a = R, поэтому S = (3√3/2) * R²
TEST(HexagonTest, AreaFormulaValidation) {
    double radius = 2.0;
    Point<double> p1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> p2(radius * std::cos(60 * M_PI / 180), radius * std::sin(60 * M_PI / 180));
    Point<double> p3(radius * std::cos(120 * M_PI / 180), radius * std::sin(120 * M_PI / 180));
    Point<double> p4(radius * std::cos(180 * M_PI / 180), radius * std::sin(180 * M_PI / 180));
    Point<double> p5(radius * std::cos(240 * M_PI / 180), radius * std::sin(240 * M_PI / 180));
    Point<double> p6(radius * std::cos(300 * M_PI / 180), radius * std::sin(300 * M_PI / 180));
    
    Hexagon<double> hexagon(p1, p2, p3, p4, p5, p6);
    
    // Ожидаемая площадь для правильного шестиугольника с радиусом 2
    double expected_area = (3.0 * std::sqrt(3.0) / 2.0) * radius * radius;
    
    EXPECT_NEAR(hexagon.square(), expected_area, 0.01); // Допуск из-за формулы Гаусса
}


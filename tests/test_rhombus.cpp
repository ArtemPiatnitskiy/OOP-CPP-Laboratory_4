#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include "../include/rhombus.h"
#include "../include/point.h"

// Константа для сравнения чисел с плавающей точкой
static constexpr double EPS = 1e-9;

// ============================================================================
// ТЕСТЫ ДЛЯ КЛАССА RHOMBUS
// ============================================================================

// Тест 1: Корректное создание ромба и проверка всех основных методов
TEST(RhombusTest, ValidConstructorAndBasicMethods) {
    // Создаём правильный ромб с вершинами в порядке обхода против часовой стрелки
    // Ромб с диагоналями вдоль осей координат
    Point<double> p1(0.0, 1.0);   // верх
    Point<double> p2(-1.0, 0.0);  // лево
    Point<double> p3(0.0, -1.0);  // низ
    Point<double> p4(1.0, 0.0);   // право
    
    Rhombus<double> rhombus(p1, p2, p3, p4);
    
    // Проверка площади: диагонали 2 и 2, площадь = (d1 * d2) / 2 = 2
    EXPECT_NEAR(rhombus.square(), 2.0, EPS);
    
    // Проверка периметра: каждая сторона = sqrt(2), периметр = 4 * sqrt(2)
    EXPECT_NEAR(rhombus.perimeter(), 4.0 * std::sqrt(2.0), EPS);
    
    // Проверка геометрического центра (должен быть в (0, 0))
    auto center = rhombus.geometric_center();
    EXPECT_NEAR(center->get_x(), 0.0, EPS);
    EXPECT_NEAR(center->get_y(), 0.0, EPS);
}

// Тест 2: Проверка, что конструктор бросает исключение для неравных сторон
TEST(RhombusTest, InvalidRhombusUnequalSides) {
    // Пытаемся создать "ромб" с неравными сторонами (это прямоугольник)
    Point<double> p1(0.0, 0.0);
    Point<double> p2(2.0, 0.0);
    Point<double> p3(2.0, 1.0);
    Point<double> p4(0.0, 1.0);
    
    // Должно бросить исключение
    EXPECT_THROW({
        Rhombus<double> rhombus(p1, p2, p3, p4);
    }, std::invalid_argument);
}

// Тест 3: Проверка оператора приведения к double (должен возвращать площадь)
TEST(RhombusTest, OperatorDoubleConvertion) {
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    Rhombus<double> rhombus(p1, p2, p3, p4);
    
    // Приведение к double должно вернуть площадь
    double area = static_cast<double>(rhombus);
    EXPECT_NEAR(area, 2.0, EPS);
    EXPECT_NEAR(area, rhombus.square(), EPS);
}

// Тест 4: Проверка оператора сравнения ==
TEST(RhombusTest, EqualityOperator) {
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    Rhombus<double> rhombus1(p1, p2, p3, p4);
    
    // Создаём другой ромб с той же площадью (2), но другими пропорциями
    // Диагонали: 4 и 1, площадь = (4 * 1) / 2 = 2
    Point<double> p5(0.0, 2.0);   // верх
    Point<double> p6(-0.5, 0.0);  // лево
    Point<double> p7(0.0, -2.0);  // низ
    Point<double> p8(0.5, 0.0);   // право
    
    Rhombus<double> rhombus2(p5, p6, p7, p8);
    
    // Площади равны, поэтому ромбы должны считаться равными
    EXPECT_TRUE(rhombus1 == rhombus2);
}

// Тест 5: Проверка конструктора копирования
TEST(RhombusTest, CopyConstructor) {
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    Rhombus<double> rhombus1(p1, p2, p3, p4);
    
    // Копируем через конструктор копирования
    Rhombus<double> rhombus2(rhombus1);
    
    // Проверяем, что площади равны
    EXPECT_NEAR(rhombus1.square(), rhombus2.square(), EPS);
    EXPECT_TRUE(rhombus1 == rhombus2);
}

// Тест 6: Проверка оператора присваивания
TEST(RhombusTest, CopyAssignmentOperator) {
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    Rhombus<double> rhombus1(p1, p2, p3, p4);
    Rhombus<double> rhombus2; // конструктор по умолчанию
    
    // Присваиваем
    rhombus2 = rhombus1;
    
    EXPECT_NEAR(rhombus1.square(), rhombus2.square(), EPS);
}

// Тест 7: Проверка конструктора перемещения
TEST(RhombusTest, MoveConstructor) {
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    Rhombus<double> rhombus1(p1, p2, p3, p4);
    double area_before = rhombus1.square();
    
    // Перемещаем
    Rhombus<double> rhombus2(std::move(rhombus1));
    
    // Проверяем, что площадь сохранилась
    EXPECT_NEAR(rhombus2.square(), area_before, EPS);
}

// Тест 8: Проверка оператора перемещения
TEST(RhombusTest, MoveAssignmentOperator) {
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    Rhombus<double> rhombus1(p1, p2, p3, p4);
    double area_before = rhombus1.square();
    
    Rhombus<double> rhombus2;
    rhombus2 = std::move(rhombus1);
    
    EXPECT_NEAR(rhombus2.square(), area_before, EPS);
}

// Тест 9: Проверка метода clone()
TEST(RhombusTest, CloneMethod) {
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    Rhombus<double> rhombus1(p1, p2, p3, p4);
    
    // Клонируем через метод clone()
    auto cloned = rhombus1.clone();
    
    // Проверяем, что площади равны
    EXPECT_NEAR(rhombus1.square(), cloned->square(), EPS);
}

// Тест 10: Проверка операторов ввода/вывода
TEST(RhombusTest, InputOutputOperators) {
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    Rhombus<double> rhombus1(p1, p2, p3, p4);
    
    // Выводим в строковый поток
    std::ostringstream oss;
    oss << rhombus1;
    
    // Проверяем, что вывод содержит слово "rhombus"
    std::string output = oss.str();
    EXPECT_TRUE(output.find("rhombus") != std::string::npos);
}

// Тест 11: Проверка работы с разными скалярными типами (int, float, double)
TEST(RhombusTest, DifferentScalarTypes) {
    // Ромб с типом int
    Point<int> p1_int(0, 2);
    Point<int> p2_int(-2, 0);
    Point<int> p3_int(0, -2);
    Point<int> p4_int(2, 0);
    
    Rhombus<int> rhombus_int(p1_int, p2_int, p3_int, p4_int);
    EXPECT_NEAR(rhombus_int.square(), 8.0, EPS); // диагонали 4 и 4
    
    // Ромб с типом float
    Point<float> p1_float(0.0f, 1.0f);
    Point<float> p2_float(-1.0f, 0.0f);
    Point<float> p3_float(0.0f, -1.0f);
    Point<float> p4_float(1.0f, 0.0f);
    
    Rhombus<float> rhombus_float(p1_float, p2_float, p3_float, p4_float);
    EXPECT_NEAR(rhombus_float.square(), 2.0, EPS);
}

// Тест: print выводит 4 вершины (по одной на строку)
TEST(RhombusAllMethods, PrintOutputsFourPoints) {
    Rhombus r(Point(0,1), Point(-1,0), Point(0,-1), Point(1,0), "d");
    std::ostringstream oss;
    r.print(oss);
    std::string expected =
        "(0, 1)\n"
        "(-1, 0)\n"
        "(0, -1)\n"
        "(1, 0)\n";
    EXPECT_EQ(oss.str(), expected);
}

// Тест: read читает 4 вершины и обновляет ромб (проверяем по площади и центру)
TEST(RhombusAllMethods, ReadParsesFourPoints) {
    std::istringstream iss(
        "(0, 1)\n"
        "(-1, 0)\n"
        "(0, -1)\n"
        "(1, 0)\n"
    );
    Rhombus<double> r;
    r.read(iss);
    EXPECT_NEAR(r.square(), 2.0, EPS);
    auto center = r.geometric_center();
    EXPECT_NEAR(center->get_x(), 0.0, EPS);
    EXPECT_NEAR(center->get_y(), 0.0, EPS);
}

// Тест: clone создаёт копию с одинаковыми характеристиками
TEST(RhombusAllMethods, CloneProducesSameRhombus) {
    Rhombus<double> r(Point<double>(0,1), Point<double>(-1,0), Point<double>(0,-1), Point<double>(1,0), "orig");
    auto f = r.clone();
    auto rr = std::dynamic_pointer_cast<Rhombus<double>>(f);
    ASSERT_NE(rr, nullptr);
    EXPECT_NEAR(rr->square(), r.square(), EPS);
    auto c1 = r.geometric_center();
    auto c2 = rr->geometric_center();
    EXPECT_NEAR(c1->get_x(), c2->get_x(), EPS);
    EXPECT_NEAR(c1->get_y(), c2->get_y(), EPS);
}

// Тест: копирующее и перемещающее присваивание сохраняют/переносят данные
TEST(RhombusAllMethods, CopyAndMoveAssignment) {
    Rhombus<double> src(Point<double>(0,1), Point<double>(-1,0), Point<double>(0,-1), Point<double>(1,0), "src");
    Rhombus<double> dest;
    dest = src; // копирующее присваивание
    EXPECT_NEAR(dest.square(), src.square(), EPS);
    auto csrc = src.geometric_center();
    auto cdest = dest.geometric_center();
    EXPECT_NEAR(csrc->get_x(), cdest->get_x(), EPS);
    EXPECT_NEAR(csrc->get_y(), cdest->get_y(), EPS);

    Rhombus<double> msrc(Point<double>(0,2), Point<double>(-2,0), Point<double>(0,-2), Point<double>(2,0), "msrc");
    Rhombus<double> mdest;
    mdest = std::move(msrc); // перемещающее присваивание
    EXPECT_NEAR(mdest.square(), 8.0, EPS); // масштабированный ромб area = 8
}

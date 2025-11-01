#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include "../include/trapezoid.h"
#include "../include/point.h"

static constexpr double EPS = 1e-9;

// Тест: корректное создание "трапеции" с учётом текущей реализации конструктора
TEST(TrapezoidAllMethods, ConstructorSquarePerimeterCenter) {
    // Точки выбраны так, чтобы конструктор не бросал (внутренняя проверка требует хотя бы одного
    // положительного векторного произведения по реализации)
    Point p1(0.5, 0.5);
    Point p2(1.5, 0.5);
    Point p3(2.5, 1.5);
    Point p4(0.5, 2.5);

    Trapezoid t(p1, p2, p3, p4, "trap");
    // Ожидаемая площадь по формуле Гаусса (рассчитано вручную): 2.5
    EXPECT_NEAR(t.square(), 2.5, EPS);

    // Периметр (приближённо): AB=1, BC=sqrt2, CD=sqrt5, DA=2
    double expected_perim = 1.0 + std::sqrt(2.0) + std::sqrt(5.0) + 2.0;
    EXPECT_NEAR(t.perimeter(), expected_perim, 1e-12);

    // Геометрический центр (по реализации): (x0+x2+x1+x3)/4, (y0+y2+y1+y3)/4
    Point c = t.geometric_center();
    EXPECT_NEAR(c.get_x(), 1.25, EPS);
    EXPECT_NEAR(c.get_y(), 1.25, EPS);
}

// Тест: конструктор бросает исключение для фигур, где оба векторных произведения ≈ 0 (прямоугольник)
TEST(TrapezoidAllMethods, ConstructorThrowsOnBothPairsParallel) {
    // Прямоугольник (в координатах без нулей) — должен вызвать исключение по текущей проверке
    Point a(1.0, 1.0);
    Point b(3.0, 1.0);
    Point c(3.0, 2.0);
    Point d(1.0, 2.0);
    EXPECT_THROW(Trapezoid(a, b, c, d, "rect_like"), std::invalid_argument);
}

// Тест: operator double возвращает площадь
TEST(TrapezoidAllMethods, OperatorDoubleReturnsArea) {
    Trapezoid t(Point(0.5,0.5), Point(1.5,0.5), Point(2.5,1.5), Point(0.5,2.5));
    double area = static_cast<double>(t);
    EXPECT_NEAR(area, t.square(), EPS);
    EXPECT_NEAR(area, 2.5, EPS);
}

// Тест: оператор== и <=> сравнивают по площади
TEST(TrapezoidAllMethods, EqualityAndThreeWayComparison) {
    Trapezoid t1(Point(0.5,0.5), Point(1.5,0.5), Point(2.5,1.5), Point(0.5,2.5));
    Trapezoid t2 = t1; // одинаковая площадь
    Trapezoid t3(Point(0.5,0.5), Point(2.5,0.5), Point(3.5,2.0), Point(0.5,3.0)); // другая площадь

    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);

    auto cmp12 = t1.operator<=>(t2);
    auto cmp13 = t1.operator<=>(t3);
    auto cmp31 = t3.operator<=>(t1);

    EXPECT_EQ(cmp12, std::partial_ordering::equivalent);
    EXPECT_EQ(cmp13, std::partial_ordering::less);
    EXPECT_EQ(cmp31, std::partial_ordering::greater);
}

// Тест: print выводит 4 вершины (по одной на строку)
TEST(TrapezoidAllMethods, PrintOutputsFourPoints) {
    Trapezoid t(Point(0.5,0.5), Point(1.5,0.5), Point(2.5,1.5), Point(0.5,2.5));
    std::ostringstream oss;
    t.print(oss);
    std::string expected =
        "(0.5, 0.5)\n"
        "(1.5, 0.5)\n"
        "(2.5, 1.5)\n"
        "(0.5, 2.5)\n";
    EXPECT_EQ(oss.str(), expected);
}

// Тест: read читает 4 вершины и обновляет трапецию (проверяем по площади и центру)
TEST(TrapezoidAllMethods, ReadParsesFourPoints) {
    std::istringstream iss(
        "(0.5, 0.5)\n"
        "(1.5, 0.5)\n"
        "(2.5, 1.5)\n"
        "(0.5, 2.5)\n"
    );
    Trapezoid t; // используется default-конструктор, затем read переписывает точки
    t.read(iss);
    EXPECT_NEAR(t.square(), 2.5, EPS);
    Point center = t.geometric_center();
    EXPECT_NEAR(center.get_x(), 1.25, EPS);
    EXPECT_NEAR(center.get_y(), 1.25, EPS);
}

// Тест: clone создаёт копию с одинаковыми характеристиками
TEST(TrapezoidAllMethods, CloneProducesSameTrapezoid) {
    Trapezoid t(Point(0.5,0.5), Point(1.5,0.5), Point(2.5,1.5), Point(0.5,2.5));
    Figure* f = t.clone();
    Trapezoid* tt = dynamic_cast<Trapezoid*>(f);
    ASSERT_NE(tt, nullptr);
    EXPECT_NEAR(tt->square(), t.square(), EPS);
    Point c1 = t.geometric_center();
    Point c2 = tt->geometric_center();
    EXPECT_NEAR(c1.get_x(), c2.get_x(), EPS);
    EXPECT_NEAR(c1.get_y(), c2.get_y(), EPS);
    delete tt;
}

// Тест: копирующее и перемещающее присваивание сохраняют/переносят данные
TEST(TrapezoidAllMethods, CopyAndMoveAssignment) {
    Trapezoid src(Point(0.5,0.5), Point(1.5,0.5), Point(2.5,1.5), Point(0.5,2.5), "src");
    Trapezoid dest;
    dest = src; // копирующее присваивание
    EXPECT_NEAR(dest.square(), src.square(), EPS);
    Point csrc = src.geometric_center();
    Point cdest = dest.geometric_center();
    EXPECT_NEAR(csrc.get_x(), cdest.get_x(), EPS);
    EXPECT_NEAR(csrc.get_y(), cdest.get_y(), EPS);

    Trapezoid msrc(Point(1.0,0.5), Point(3.0,0.5), Point(3.5,2.0), Point(0.5,3.0), "msrc");
    Trapezoid mdest;
    mdest = std::move(msrc); // перемещающее присваивание — проверяем, что mdest получил корректные характеристики
    EXPECT_GT(mdest.square(), 0.0);
}
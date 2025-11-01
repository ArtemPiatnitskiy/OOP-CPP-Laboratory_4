#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <compare>
#include "../include/rectangle.h"
#include "../include/point.h"

static constexpr double EPS = 1e-9;

// Тест: корректное создание прямоугольника и вычисление площади/периметра
TEST(RectangleAllMethods, ConstructorSquarePerimeter) {
    // Прямоугольник от (0,0) до (3,4) -> стороны 3 и 4
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);
    Rectangle r(p1, p2, "rect");
    EXPECT_NEAR(r.square(), 12.0, EPS);      // 3 * 4
    EXPECT_NEAR(r.perimeter(), 14.0, EPS);   // 2*(3+4)
}

// Тест: конструктор должен бросать исключение при выровненных по x или y точках
TEST(RectangleAllMethods, ConstructorThrowsOnAlignedPoints) {
    Point a(1.0, 1.0);
    Point b_same_x(1.0, 5.0);
    Point b_same_y(4.0, 1.0);
    EXPECT_THROW(Rectangle(a, b_same_x, "bad"), std::invalid_argument);
    EXPECT_THROW(Rectangle(a, b_same_y, "bad"), std::invalid_argument);
}

// Тест: геометрический центр вычисляется как середина диагонали
TEST(RectangleAllMethods, GeometricCenter) {
    Point p1(0.0, 0.0);
    Point p2(4.0, 6.0);
    Rectangle r(p1, p2, "rect");
    Point center = r.geometric_center();
    EXPECT_NEAR(center.get_x(), 2.0, EPS);
    EXPECT_NEAR(center.get_y(), 3.0, EPS);
}

// Тест: operator double возвращает площадь (явное преобразование)
TEST(RectangleAllMethods, OperatorDoubleReturnsArea) {
    Rectangle r(Point(0,0), Point(2,5), "rect");
    double area = static_cast<double>(r);
    EXPECT_NEAR(area, r.square(), EPS);
    EXPECT_NEAR(area, 2.0 * 5.0, EPS);
}

// Тест: оператор double возвращает площадь (Неявное преобразование для проверки)
TEST(RectangleAllMethods, OperatorDoubleReturnsAreaImplicit) {
    Rectangle r(Point(0,0), Point(2,5), "rect");
    double area = r;
    EXPECT_NEAR(area, r.square(), EPS);
    EXPECT_NEAR(area, 2.0 * 5.0, EPS);
}

// Тест: оператор== сравнивает по площади
TEST(RectangleAllMethods, EqualityByArea) {
    Rectangle r1(Point(0,0), Point(2,5), "r1"); // area 10
    Rectangle r2(Point(0,0), Point(5,2), "r2"); // area 10 (rotated)
    Rectangle r3(Point(0,0), Point(3,4), "r3"); // area 12
    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 == r3);
}

// Тест: оператор <=> возвращает ожидаемое partial_ordering
TEST(RectangleAllMethods, ThreeWayComparison) {
    Rectangle small(Point(0,0), Point(1,1), "s"); // area 1
    Rectangle mid(Point(0,0), Point(2,2), "m");   // area 4
    Rectangle big(Point(0,0), Point(3,3), "b");   // area 9

    auto cmp_sm_mid = small.operator<=>(mid);
    auto cmp_mid_sm = mid.operator<=>(small);
    auto cmp_mid_big = mid.operator<=>(big);
    auto cmp_mid_mid = mid.operator<=>(Rectangle(Point(0,0), Point(2,2), "copy"));

    EXPECT_EQ(cmp_sm_mid, std::partial_ordering::less);
    EXPECT_EQ(cmp_mid_sm, std::partial_ordering::greater);
    EXPECT_EQ(cmp_mid_big, std::partial_ordering::less);
    EXPECT_EQ(cmp_mid_mid, std::partial_ordering::equivalent);
}

// Тест: print выводит 4 вершины (по одной на строку)
TEST(RectangleAllMethods, PrintOutputsFourPoints) {
    Rectangle r(Point(0,0), Point(3,4), "rect");
    std::ostringstream oss;
    r.print(oss);
    std::string expected =
        "(0, 0)\n"
        "(3, 0)\n"
        "(3, 4)\n"
        "(0, 4)\n";
    EXPECT_EQ(oss.str(), expected);
}

// Тест: read читает 4 вершины и обновляет прямоугольник (проверяем по площади и центру)
TEST(RectangleAllMethods, ReadParsesFourPoints) {
    // Текст с четырьмя точками в формате, ожидаемом operator>>
    std::istringstream iss(
        "(1, 1)\n"
        "(4, 1)\n"
        "(4, 5)\n"
        "(1, 5)\n"
    );
    Rectangle r(Point(0,0), Point(1,1), "tmp"); // значения будут перезаписаны
    r.read(iss);
    EXPECT_NEAR(r.square(), 12.0, EPS); // (4-1)*(5-1) = 3*4 = 12
    Point center = r.geometric_center();
    EXPECT_NEAR(center.get_x(), 2.5, EPS); // (1+4)/2
    EXPECT_NEAR(center.get_y(), 3.0, EPS); // (1+5)/2
}

// Тест: clone создаёт ровную копию (по площади и центру)
TEST(RectangleAllMethods, CloneProducesSameRectangle) {
    Rectangle r(Point(0,0), Point(3,4), "orig");
    Figure* f = r.clone();
    Rectangle* rc = dynamic_cast<Rectangle*>(f);
    ASSERT_NE(rc, nullptr);
    EXPECT_NEAR(rc->square(), r.square(), EPS);
    Point c1 = r.geometric_center();
    Point c2 = rc->geometric_center();
    EXPECT_NEAR(c1.get_x(), c2.get_x(), EPS);
    EXPECT_NEAR(c1.get_y(), c2.get_y(), EPS);
    delete rc;
}

// Тест: оператор присваивания (копирование) и присваивание перемещением
TEST(RectangleAllMethods, CopyAndMoveAssignment) {
    Rectangle src(Point(0,0), Point(3,4), "src");
    Rectangle dest(Point(0,0), Point(1,1), "dest");
    dest = src; // копирующее присваивание
    EXPECT_NEAR(dest.square(), src.square(), EPS);
    Point csrc = src.geometric_center();
    Point cdest = dest.geometric_center();
    EXPECT_NEAR(csrc.get_x(), cdest.get_x(), EPS);
    EXPECT_NEAR(csrc.get_y(), cdest.get_y(), EPS);

    Rectangle mover_src(Point(0,0), Point(2,6), "m");
    Rectangle mover_dest(Point(0,0), Point(1,1), "d");
    mover_dest = std::move(mover_src); // перемещающее присваивание
    EXPECT_NEAR(mover_dest.square(), 2.0 * 6.0, EPS);
}
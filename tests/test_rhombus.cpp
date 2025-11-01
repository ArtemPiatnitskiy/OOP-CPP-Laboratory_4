#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <compare>
#include "../include/rhombus.h"
#include "../include/point.h"

static constexpr double EPS = 1e-9;

// Тест: корректное создание ромба и проверка площади/периметра/центра
TEST(RhombusAllMethods, ConstructorSquarePerimeterCenter) {
    // Вершины ромба в порядке, дающем положительные векторные произведения:
    // (0,1), (-1,0), (0,-1), (1,0)
    Rhombus r(Point(0,1), Point(-1,0), Point(0,-1), Point(1,0), "diamond");
    EXPECT_NEAR(r.square(), 2.0, EPS); // диагонали 2 и 2 -> площадь = 2
    EXPECT_NEAR(r.perimeter(), 4.0 * std::sqrt(2.0), 1e-12); // 4 * sqrt(2)
    Point center = r.geometric_center();
    EXPECT_NEAR(center.get_x(), 0.0, EPS);
    EXPECT_NEAR(center.get_y(), 0.0, EPS);
}

// Тест: конструктор бросает исключение для точек с разной длиной сторон
TEST(RhombusAllMethods, ConstructorThrowsOnUnequalSides) {
    // Прямоугольник (не ромб): стороны не все равны
    EXPECT_THROW(
        Rhombus r(Point(0,0), Point(2,0), Point(2,1), Point(0,1), "not_rhombus"),
        std::invalid_argument
    );
}

// Тест: конструктор бросает исключение при неподходящем порядке точек (векторные произведения <= 1e-10)
TEST(RhombusAllMethods, ConstructorThrowsOnBadOrientation) {
    // Те же вершины ромба, но в неправильном порядке
    EXPECT_THROW(
        Rhombus r(Point(0,1), Point(0,-1), Point(-1,0), Point(1,0), "bad_order"),
        std::invalid_argument
    );
}

// Тест: оператор double возвращает площадь
TEST(RhombusAllMethods, OperatorDoubleReturnsArea) {
    Rhombus r(Point(0,1), Point(-1,0), Point(0,-1), Point(1,0), "d");
    double area = static_cast<double>(r);
    EXPECT_NEAR(area, r.square(), EPS);
    EXPECT_NEAR(area, 2.0, EPS);
}

// Тест: оператор == и <=> сравнивают по площади
TEST(RhombusAllMethods, EqualityAndThreeWayComparison) {
    Rhombus r1(Point(0,1), Point(-1,0), Point(0,-1), Point(1,0), "r1"); // area 2
    Rhombus r2 = r1; // точно такая же
    Rhombus r3(Point(0,2), Point(-2,0), Point(0,-2), Point(2,0), "r3"); // масштабированный, area 8

    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 == r3);

    auto cmp_r1_r3 = r1.operator<=>(r3);
    auto cmp_r3_r1 = r3.operator<=>(r1);
    EXPECT_EQ(cmp_r1_r3, std::partial_ordering::less);
    EXPECT_EQ(cmp_r3_r1, std::partial_ordering::greater);
    EXPECT_EQ(r1.operator<=>(r2), std::partial_ordering::equivalent);
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
    Rhombus r;
    r.read(iss);
    EXPECT_NEAR(r.square(), 2.0, EPS);
    Point center = r.geometric_center();
    EXPECT_NEAR(center.get_x(), 0.0, EPS);
    EXPECT_NEAR(center.get_y(), 0.0, EPS);
}

// Тест: clone создаёт копию с одинаковыми характеристиками
TEST(RhombusAllMethods, CloneProducesSameRhombus) {
    Rhombus r(Point(0,1), Point(-1,0), Point(0,-1), Point(1,0), "orig");
    Figure* f = r.clone();
    Rhombus* rr = dynamic_cast<Rhombus*>(f);
    ASSERT_NE(rr, nullptr);
    EXPECT_NEAR(rr->square(), r.square(), EPS);
    Point c1 = r.geometric_center();
    Point c2 = rr->geometric_center();
    EXPECT_NEAR(c1.get_x(), c2.get_x(), EPS);
    EXPECT_NEAR(c1.get_y(), c2.get_y(), EPS);
    delete rr;
}

// Тест: копирующее и перемещающее присваивание сохраняют/переносят данные
TEST(RhombusAllMethods, CopyAndMoveAssignment) {
    Rhombus src(Point(0,1), Point(-1,0), Point(0,-1), Point(1,0), "src");
    Rhombus dest;
    dest = src; // копирующее присваивание
    EXPECT_NEAR(dest.square(), src.square(), EPS);
    Point csrc = src.geometric_center();
    Point cdest = dest.geometric_center();
    EXPECT_NEAR(csrc.get_x(), cdest.get_x(), EPS);
    EXPECT_NEAR(csrc.get_y(), cdest.get_y(), EPS);

    Rhombus msrc(Point(0,2), Point(-2,0), Point(0,-2), Point(2,0), "msrc");
    Rhombus mdest;
    mdest = std::move(msrc); // перемещающее присваивание
    EXPECT_NEAR(mdest.square(), 8.0, EPS); // масштабированный ромб area = 8
}

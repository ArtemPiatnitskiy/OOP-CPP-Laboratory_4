#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <string>
#include <algorithm>
#include "../include/pentagon.h"
#include "../include/point.h"

// Точность для сравнения double
static constexpr double EPS = 1e-6;

// Вспомогательная функция для создания правильного пятиугольника
static std::array<Point<double>,5> make_regular_pentagon(double R, double angle_offset_deg = 0.0) {
    std::array<Point<double>,5> pts;
    for (int i = 0; i < 5; ++i) {
        double angle = (angle_offset_deg + i * 72.0) * M_PI / 180.0;
        pts[i] = Point<double>(R * std::cos(angle), R * std::sin(angle));
    }
    return pts;
}

// -----------------------------
// ТЕСТЫ ДЛЯ КЛАССА PENTAGON
// -----------------------------

TEST(PentagonTest, ValidConstructorAndBasicMethods) {
    auto pts = make_regular_pentagon(1.0);
    // Конструктор не должен бросать
    ASSERT_NO_THROW({ Pentagon<double> p(pts[0], pts[1], pts[2], pts[3], pts[4]); });

    Pentagon<double> pent(pts[0], pts[1], pts[2], pts[3], pts[4]);
    EXPECT_GT(pent.square(), 0.0);

    double side = distance(pts[0], pts[1]);
    EXPECT_NEAR(pent.perimeter(), 5.0 * side, EPS);

    auto center = pent.geometric_center();
    EXPECT_NEAR(center->get_x(), 0.0, EPS);
    EXPECT_NEAR(center->get_y(), 0.0, EPS);
}

TEST(PentagonTest, InvalidPentagonUnequalSides) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(1.0, 0.0);
    Point<double> p3(1.5, 1.0);
    Point<double> p4(0.5, 1.5);
    Point<double> p5(-0.5, 1.0);
    EXPECT_THROW({ Pentagon<double> pent(p1, p2, p3, p4, p5); }, std::invalid_argument);
}

TEST(PentagonTest, InvalidPentagonNotConcyclic) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(1.0, 0.0);
    Point<double> p3(2.0, 0.0);
    Point<double> p4(3.0, 0.0);
    Point<double> p5(4.0, 0.0);
    EXPECT_THROW({ Pentagon<double> pent(p1, p2, p3, p4, p5); }, std::invalid_argument);
}

TEST(PentagonTest, OperatorDoubleConversion) {
    auto pts = make_regular_pentagon(2.0);
    Pentagon<double> pent(pts[0], pts[1], pts[2], pts[3], pts[4]);
    double a = static_cast<double>(pent);
    EXPECT_NEAR(a, pent.square(), EPS);
}

TEST(PentagonTest, CopyAndMoveSemantics) {
    auto pts = make_regular_pentagon(1.3);
    Pentagon<double> p1(pts[0], pts[1], pts[2], pts[3], pts[4]);

    Pentagon<double> p2(p1);
    EXPECT_NEAR(p1.square(), p2.square(), EPS);

    Pentagon<double> p3;
    p3 = p1;
    EXPECT_NEAR(p1.square(), p3.square(), EPS);

    double before;
    {
        Pentagon<double> tmp(pts[0], pts[1], pts[2], pts[3], pts[4]);
        before = tmp.square();
        Pentagon<double> moved(std::move(tmp));
        EXPECT_NEAR(moved.square(), before, EPS);
    }
}

TEST(PentagonTest, CloneAndEquality) {
    auto pts = make_regular_pentagon(1.5);
    Pentagon<double> p(pts[0], pts[1], pts[2], pts[3], pts[4]);
    auto cloned = p.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_NEAR(p.square(), cloned->square(), EPS);

    Pentagon<double> q(pts[0], pts[1], pts[2], pts[3], pts[4]);
    EXPECT_TRUE(p == q);
}

TEST(PentagonTest, OutputOperator) {
    auto pts = make_regular_pentagon(0.7);
    Pentagon<double> p(pts[0], pts[1], pts[2], pts[3], pts[4]);
    std::ostringstream oss;
    oss << p;
    std::string out = oss.str();
    EXPECT_TRUE(out.find("pentagon") != std::string::npos);
}


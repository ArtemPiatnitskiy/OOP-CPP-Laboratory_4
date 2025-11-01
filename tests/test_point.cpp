#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include "../include/point.h"

static constexpr double EPS = 1e-9;

// Тест: конструктор по умолчанию и методы доступа возвращают нули
TEST(PointAllMethods, DefaultConstructorAndGetters) {
    Point p;
    EXPECT_NEAR(p.get_x(), 0.0, EPS);
    EXPECT_NEAR(p.get_y(), 0.0, EPS);
}

// Тест: параметризованный конструктор корректно задаёт координаты
TEST(PointAllMethods, ParameterizedConstructorAndGetters) {
    Point p(1.5, -2.25);
    EXPECT_NEAR(p.get_x(), 1.5, EPS);
    EXPECT_NEAR(p.get_y(), -2.25, EPS);
}

// Тест: move устанавливает абсолютные координаты (не относительный сдвиг)
TEST(PointAllMethods, MoveSetsAbsoluteCoordinates) {
    Point p(0.0, 0.0);
    p.move(3.14, -1.618);
    EXPECT_NEAR(p.get_x(), 3.14, EPS);
    EXPECT_NEAR(p.get_y(), -1.618, EPS);

    // ещё один вызов проверяет, что координаты перезаписываются
    p.move(-100.0, 200.0);
    EXPECT_NEAR(p.get_x(), -100.0, EPS);
    EXPECT_NEAR(p.get_y(), 200.0, EPS);
}

// Тест: свободная функция distance вычисляет эвклидово расстояние
TEST(PointAllMethods, DistanceFunction) {
    Point a(0.0, 0.0);
    Point b(3.0, 4.0);
    EXPECT_NEAR(distance(a, b), 5.0, EPS);
    EXPECT_NEAR(distance(b, a), 5.0, EPS);

    Point c(-1.0, -1.0);
    Point d(2.0, 3.0);
    double expected = std::hypot(d.get_x() - c.get_x(), d.get_y() - c.get_y());
    EXPECT_NEAR(distance(c, d), expected, EPS);
}

// Тест: оператор вывода форматирует точку как "(x, y)"
TEST(PointAllMethods, StreamOutputFormatting) {
    Point p(1.5, -2.25);
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "(1.5, -2.25)");
}

// Тест: корректный ввод через оператор>> парсит координаты
TEST(PointAllMethods, StreamInputValid) {
    std::istringstream iss("(2.5, -3.75)");
    Point p;
    iss >> p;
    EXPECT_FALSE(iss.fail());
    EXPECT_NEAR(p.get_x(), 2.5, EPS);
    EXPECT_NEAR(p.get_y(), -3.75, EPS);
}

// Тест: при некорректном вводе поток устанавливает fail и точка не меняется
TEST(PointAllMethods, StreamInputInvalidDoesNotModifyPointAndSetsFail) {
    Point original(0.0, 0.0);
    Point p = original;
    std::istringstream iss("2.5, -3.75"); // отсутствуют ожидаемые скобки/разделители
    iss >> p;
    EXPECT_TRUE(iss.fail());
    // убедиться, что точка осталась без изменений после неудачного разбора
    EXPECT_NEAR(p.get_x(), original.get_x(), EPS);
    EXPECT_NEAR(p.get_y(), original.get_y(), EPS);
}

// Тест: конструктор копирования и оператор присваивания сохраняют координаты
TEST(PointAllMethods, CopyConstructorAndAssignment) {
    Point src(7.7, -8.8);
    Point copy = src;
    EXPECT_NEAR(copy.get_x(), src.get_x(), EPS);
    EXPECT_NEAR(copy.get_y(), src.get_y(), EPS);

    Point assigned;
    assigned = src;
    EXPECT_NEAR(assigned.get_x(), src.get_x(), EPS);
    EXPECT_NEAR(assigned.get_y(), src.get_y(), EPS);
}
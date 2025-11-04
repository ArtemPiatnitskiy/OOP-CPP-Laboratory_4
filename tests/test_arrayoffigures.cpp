#include <gtest/gtest.h>
#include <memory>
#include "../include/arrayoffigures.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/figure.h"
#include "../include/point.h"

static constexpr double EPS = 1e-6;

// ============================================================================
// ТЕСТЫ ДЛЯ КЛАССА ARRAYOFFIGURES
// ============================================================================

// =========================
// ЧАСТЬ 1: Массив одного типа фигур (Rhombus)
// Задание требует: "проверить для Array<Rhombus<double>>"
// =========================

TEST(ArrayOfFiguresTest, SingleTyp_AddAndSize) {
    // Создаём массив для хранения ТОЛЬКО ромбов
    ArrayOfFigures<Rhombus<double>> rhombus_array(2);
    
    EXPECT_EQ(rhombus_array.get_size(), 0);
    
    // Создаём ромб
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    auto rhombus1 = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    
    // Добавляем в массив
    rhombus_array.add_figure(rhombus1);
    
    EXPECT_EQ(rhombus_array.get_size(), 1);
}

TEST(ArrayOfFiguresTest, SingleType_AccessByIndex) {
    ArrayOfFigures<Rhombus<double>> rhombus_array(5);
    
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    auto rhombus1 = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    
    rhombus_array.add_figure(rhombus1);
    
    // Доступ через operator[]
    auto retrieved = rhombus_array[0];
    
    EXPECT_NE(retrieved, nullptr);
    EXPECT_NEAR(retrieved->square(), 2.0, EPS);
}

TEST(ArrayOfFiguresTest, SingleType_TotalSquare) {
    ArrayOfFigures<Rhombus<double>> rhombus_array(5);
    
    // Добавляем несколько ромбов
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    auto rhombus1 = std::make_shared<Rhombus<double>>(p1, p2, p3, p4); // area = 2
    
    Point<double> p5(0.0, 2.0);
    Point<double> p6(-2.0, 0.0);
    Point<double> p7(0.0, -2.0);
    Point<double> p8(2.0, 0.0);
    
    auto rhombus2 = std::make_shared<Rhombus<double>>(p5, p6, p7, p8); // area = 8
    
    rhombus_array.add_figure(rhombus1);
    rhombus_array.add_figure(rhombus2);
    
    // Проверяем общую площадь
    double total = rhombus_array.total_square();
    EXPECT_NEAR(total, 10.0, EPS); // 2 + 8 = 10
}

// =========================
// ЧАСТЬ 2: Полиморфный массив разных типов фигур
// Задание требует: "проверить для Array<Figure<double>*>"
// =========================

TEST(ArrayOfFiguresTest, PolymorphicArray_MixedFigures) {
    // Создаём массив для хранения ЛЮБЫХ фигур (полиморфизм через Figure<double>)
    ArrayOfFigures<Figure<double>> mixed_array(5);
    
    // Создаём ромб
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    auto rhombus = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    
    // Создаём пятиугольник
    double radius_pent = 1.0;
    Point<double> pp1(radius_pent * std::cos(0 * M_PI / 180), radius_pent * std::sin(0 * M_PI / 180));
    Point<double> pp2(radius_pent * std::cos(72 * M_PI / 180), radius_pent * std::sin(72 * M_PI / 180));
    Point<double> pp3(radius_pent * std::cos(144 * M_PI / 180), radius_pent * std::sin(144 * M_PI / 180));
    Point<double> pp4(radius_pent * std::cos(216 * M_PI / 180), radius_pent * std::sin(216 * M_PI / 180));
    Point<double> pp5(radius_pent * std::cos(288 * M_PI / 180), radius_pent * std::sin(288 * M_PI / 180));
    auto pentagon = std::make_shared<Pentagon<double>>(pp1, pp2, pp3, pp4, pp5);
    
    // Создаём шестиугольник
    double radius_hex = 1.0;
    Point<double> ph1(radius_hex * std::cos(0 * M_PI / 180), radius_hex * std::sin(0 * M_PI / 180));
    Point<double> ph2(radius_hex * std::cos(60 * M_PI / 180), radius_hex * std::sin(60 * M_PI / 180));
    Point<double> ph3(radius_hex * std::cos(120 * M_PI / 180), radius_hex * std::sin(120 * M_PI / 180));
    Point<double> ph4(radius_hex * std::cos(180 * M_PI / 180), radius_hex * std::sin(180 * M_PI / 180));
    Point<double> ph5(radius_hex * std::cos(240 * M_PI / 180), radius_hex * std::sin(240 * M_PI / 180));
    Point<double> ph6(radius_hex * std::cos(300 * M_PI / 180), radius_hex * std::sin(300 * M_PI / 180));
    auto hexagon = std::make_shared<Hexagon<double>>(ph1, ph2, ph3, ph4, ph5, ph6);
    
    // Добавляем разные фигуры в один массив
    mixed_array.add_figure(rhombus);
    mixed_array.add_figure(pentagon);
    mixed_array.add_figure(hexagon);
    
    EXPECT_EQ(mixed_array.get_size(), 3);
}

TEST(ArrayOfFiguresTest, PolymorphicArray_TotalSquare) {
    ArrayOfFigures<Figure<double>> mixed_array(5);
    
    // Ромб с площадью 2
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    auto rhombus = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    
    // Пятиугольник
    double radius = 1.0;
    Point<double> pp1(radius * std::cos(0 * M_PI / 180), radius * std::sin(0 * M_PI / 180));
    Point<double> pp2(radius * std::cos(72 * M_PI / 180), radius * std::sin(72 * M_PI / 180));
    Point<double> pp3(radius * std::cos(144 * M_PI / 180), radius * std::sin(144 * M_PI / 180));
    Point<double> pp4(radius * std::cos(216 * M_PI / 180), radius * std::sin(216 * M_PI / 180));
    Point<double> pp5(radius * std::cos(288 * M_PI / 180), radius * std::sin(288 * M_PI / 180));
    auto pentagon = std::make_shared<Pentagon<double>>(pp1, pp2, pp3, pp4, pp5);
    
    mixed_array.add_figure(rhombus);
    mixed_array.add_figure(pentagon);
    
    // Проверяем, что общая площадь > 0 и является суммой
    double total = mixed_array.total_square();
    EXPECT_GT(total, 2.0); // Больше, чем просто площадь ромба
}

TEST(ArrayOfFiguresTest, PolymorphicArray_PrintFigures) {
    ArrayOfFigures<Figure<double>> mixed_array(3);
    
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    auto rhombus = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    
    mixed_array.add_figure(rhombus);
    
    // Проверяем, что print_figures работает без ошибок
    std::ostringstream oss;
    mixed_array.print_figures(oss);
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// =========================
// ЧАСТЬ 3: Тесты копирования/перемещения массива
// =========================

TEST(ArrayOfFiguresTest, CopyConstructor) {
    ArrayOfFigures<Figure<double>> array1(3);
    
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    auto rhombus = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    
    array1.add_figure(rhombus);
    
    // Копируем массив
    ArrayOfFigures<Figure<double>> array2(array1);
    
    EXPECT_EQ(array1.get_size(), array2.get_size());
    EXPECT_NEAR(array1.total_square(), array2.total_square(), EPS);
}

TEST(ArrayOfFiguresTest, MoveConstructor) {
    ArrayOfFigures<Figure<double>> array1(3);
    
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    auto rhombus = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    
    array1.add_figure(rhombus);
    
    size_t size_before = array1.get_size();
    
    // Перемещаем массив
    ArrayOfFigures<Figure<double>> array2(std::move(array1));
    
    EXPECT_EQ(array2.get_size(), size_before);
    EXPECT_EQ(array1.get_size(), 0); // Исходный массив должен быть пустым
}

TEST(ArrayOfFiguresTest, CopyAssignment) {
    ArrayOfFigures<Figure<double>> array1(3);
    ArrayOfFigures<Figure<double>> array2(3);
    
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    auto rhombus = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    
    array1.add_figure(rhombus);
    
    // Присваивание
    array2 = array1;
    
    EXPECT_EQ(array1.get_size(), array2.get_size());
}

TEST(ArrayOfFiguresTest, MoveAssignment) {
    ArrayOfFigures<Figure<double>> array1(3);
    ArrayOfFigures<Figure<double>> array2(3);
    
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    auto rhombus = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    
    array1.add_figure(rhombus);
    
    size_t size_before = array1.get_size();
    
    // Перемещение через присваивание
    array2 = std::move(array1);
    
    EXPECT_EQ(array2.get_size(), size_before);
    EXPECT_EQ(array1.get_size(), 0);
}

// =========================
// ЧАСТЬ 4: Тест автоматического увеличения capacity
// =========================

TEST(ArrayOfFiguresTest, AutoResize) {
    // Создаём массив с начальной ёмкостью 2
    ArrayOfFigures<Figure<double>> array(1);
    
    EXPECT_EQ(array.get_capacity(), 2); // capacity должна быть cap * 2
    
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    // Добавляем фигуры, превышая начальную ёмкость
    for (int i = 0; i < 5; ++i) {
        auto rhombus = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
        array.add_figure(rhombus);
    }
    
    EXPECT_EQ(array.get_size(), 5);
    EXPECT_GE(array.get_capacity(), 5); // Ёмкость должна была увеличиться
}

// =========================
// ЧАСТЬ 5: Тест удаления фигур
// =========================

TEST(ArrayOfFiguresTest, RemoveFigure) {
    ArrayOfFigures<Figure<double>> array(5);
    
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    auto rhombus1 = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    auto rhombus2 = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    auto rhombus3 = std::make_shared<Rhombus<double>>(p1, p2, p3, p4);
    
    array.add_figure(rhombus1);
    array.add_figure(rhombus2);
    array.add_figure(rhombus3);
    
    EXPECT_EQ(array.get_size(), 3);
    
    // Удаляем фигуру с индексом 1
    array.remove_figure(1);
    
    EXPECT_EQ(array.get_size(), 2);
}

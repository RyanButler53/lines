#include <gtest/gtest.h>
#include "fraction.hpp"

// Test constructor and simplify method
TEST(FractionTest, Simplify) {
    Fraction f(4, 8);
    f.simplify();
    EXPECT_EQ(f.num_, 1);
    EXPECT_EQ(f.den_, 2);
}

TEST(FractionTest, StringConstructor) {
    Fraction f("3/4");
    Fraction f2{3, 4};
    EXPECT_EQ(f, f2);
}

// Test comparison operators
TEST(FractionTest, ComparisonOperators) {
    Fraction f1(1, 2);
    Fraction f2(2, 4);
    Fraction f3(3, 4);

    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 < f2);
    EXPECT_TRUE(f1 < f3);
}

// Test arithmetic operators
TEST(FractionTest, ArithmeticOperators) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);

    Fraction sum = f1 + f2;
    EXPECT_EQ(sum.num_, 5);
    EXPECT_EQ(sum.den_, 6);

    Fraction diff = f1 - f2;
    EXPECT_EQ(diff.num_, 1);
    EXPECT_EQ(diff.den_, 6);

    Fraction diff2 = f1 - Fraction{"2/3"};
    EXPECT_EQ(diff2, Fraction("-1/6"));

    Fraction product = f1 * f2;
    EXPECT_EQ(product.num_, 1);
    EXPECT_EQ(product.den_, 6);

    Fraction quotient = f1 / f2;
    EXPECT_EQ(quotient.num_, 3);
    EXPECT_EQ(quotient.den_, 2);
}

TEST(FractionTest, ComparisonOperator) {
    Fraction f1(-1, 2);
    Fraction f2(1, 3);
    Fraction f3("-2/3");
    Fraction f4("15/9");
    Fraction f5("5/3");
    Fraction f6(0, 1);

    EXPECT_TRUE(f1 < f2);
    EXPECT_FALSE(f4 < f1);
    EXPECT_TRUE(f3 < f1);
    EXPECT_FALSE(f4 < f3);

    EXPECT_TRUE(f1 <= f2);
    EXPECT_FALSE(f3 >= f4);
    EXPECT_TRUE(f6 <= f5);
    EXPECT_TRUE(f3 != f4);
    EXPECT_FALSE(f4 != f5);
    EXPECT_TRUE(f5 > f2);
}

// Test stream operator
TEST(FractionTest, StreamOperator) {
    Fraction f(1, 2);
    std::ostringstream os;
    os << f;
    EXPECT_EQ(os.str(), "1/2");
    os.clear();


    Fraction f2(5, 1);
    std::ostringstream os2;
    os2 << f2;
    EXPECT_EQ(os2.str(), "5");
}

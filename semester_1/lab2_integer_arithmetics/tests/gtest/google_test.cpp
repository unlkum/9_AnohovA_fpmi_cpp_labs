// #include "pch.h"
#include "../task.h"

#include <gtest/gtest.h>
#include <stdexcept>

// IsValidNumber
TEST(IsValidNumber, ValidCases) {
    EXPECT_TRUE(IsValidNumber(1));
    EXPECT_TRUE(IsValidNumber(999));
}

TEST(IsValidNumber, InvalidCases) {
    EXPECT_FALSE(IsValidNumber(0));
    EXPECT_FALSE(IsValidNumber(-5));
}

// BinPow
TEST(BinPow, CorrectValues) {
    EXPECT_EQ(1, BinPow(10, 0));
    EXPECT_EQ(10, BinPow(10, 1));
    EXPECT_EQ(1000, BinPow(10, 3));
}

// FindMinDigit
TEST(FindMinDigit, CorrectValues) {
    EXPECT_EQ(1, FindMinDigit(123));
    EXPECT_EQ(1, FindMinDigit(100));
    EXPECT_EQ(5, FindMinDigit(505'050));
}

TEST(FindMinDigit, ThrowsExceptions) {
    EXPECT_THROW(FindMinDigit(0), std::invalid_argument);
    EXPECT_THROW(FindMinDigit(-1), std::invalid_argument);
}

// CountDigits
TEST(CountDigits, Basic) {
    EXPECT_EQ(1, CountDigits(5));
    EXPECT_EQ(2, CountDigits(42));
    EXPECT_EQ(3, CountDigits(999));
}

// ProcessNumber
TEST(ProcessNumber, WorksCorrectly) {
    EXPECT_EQ(111, ProcessNumber(1));
    EXPECT_EQ(11'231, ProcessNumber(123));
    EXPECT_EQ(19'876'543'211LL, ProcessNumber(987'654'321));
}

TEST(ProcessNumber, Throws) {
    EXPECT_THROW(ProcessNumber(0), std::invalid_argument);
    EXPECT_THROW(ProcessNumber(-1), std::invalid_argument);
}

// GetNumber
TEST(GetNumber, ReadsValidInput) {
    std::stringstream ss("123");
    std::cin.rdbuf(ss.rdbuf());
    EXPECT_EQ(123, GetNumber());
}

TEST(GetNumber, ZeroIsNotNatural) {
    std::stringstream ss("0");
    std::cin.rdbuf(ss.rdbuf());
    EXPECT_THROW(GetNumber(), std::invalid_argument);
}

TEST(GetNumber, OverflowLargeNumber) {
    std::stringstream ss("9999999999999999999999999");
    std::cin.rdbuf(ss.rdbuf());
    EXPECT_THROW(GetNumber(), std::runtime_error);
}

TEST(GetNumber, PreventOverflowNumber) {
    std::stringstream ss("10000000000000000");
    std::cin.rdbuf(ss.rdbuf());
    EXPECT_THROW(GetNumber(), std::out_of_range);
}

// Main
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

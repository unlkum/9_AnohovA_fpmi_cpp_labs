// #include "pch.h"
#include "task3.h"
#include <gtest/gtest.h>
#include <string>

// IsValidNaturalNumber
TEST(IsValidNaturalNumberTest, Valid) {
    EXPECT_TRUE(IsValidNaturalNumber("1"));
    EXPECT_TRUE(IsValidNaturalNumber("123"));
    EXPECT_TRUE(IsValidNaturalNumber("987654321"));
}

TEST(IsValidNaturalNumberTest, Invalid) {
    EXPECT_FALSE(IsValidNaturalNumber(""));
    EXPECT_FALSE(IsValidNaturalNumber("0"));
    EXPECT_FALSE(IsValidNaturalNumber("12a34"));
    EXPECT_FALSE(IsValidNaturalNumber("-123"));
    EXPECT_FALSE(IsValidNaturalNumber("1.234"));
}

TEST(IsValidNaturalNumberTest, VeryLongNumbers) {
    std::string long_number(1000, '9');
    EXPECT_TRUE(IsValidNaturalNumber(long_number));

    std::string very_long(10'000, '1');
    EXPECT_TRUE(IsValidNaturalNumber(very_long));
}

// FindMinNonZeroDigit
TEST(FindMinNonZeroDigitTest, Basic) {
    EXPECT_EQ('1', FindMinNonZeroDigit("123"));
    EXPECT_EQ('1', FindMinNonZeroDigit("100"));
    EXPECT_EQ('9', FindMinNonZeroDigit("9"));
    EXPECT_EQ('9', FindMinNonZeroDigit("0000"));
}

TEST(FindMinNonZeroDigitTest, VeryLongNumbers) {
    std::string long_num = "9" + std::string(1000, '0') + "1";
    EXPECT_EQ('1', FindMinNonZeroDigit(long_num));

    std::string all_nines(500, '9');
    EXPECT_EQ('9', FindMinNonZeroDigit(all_nines));
}

// ProcessNumber
TEST(ProcessNumberTest, Basic) {
    EXPECT_EQ("111", ProcessNumber("1"));
    EXPECT_EQ("11231", ProcessNumber("123"));
    EXPECT_EQ("19876543211", ProcessNumber("987654321"));
}

TEST(ProcessNumberTest, LongNumbers) {
    std::string num = "1" + std::string(1000, '0') + "2";
    std::string expected = "1" + num + "1";
    EXPECT_EQ(expected, ProcessNumber(num));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
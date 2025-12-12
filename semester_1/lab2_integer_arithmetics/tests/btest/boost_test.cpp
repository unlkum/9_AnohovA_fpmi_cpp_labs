#define BOOST_TEST_MODULE TaskTests
#include "../task.h"

#include <boost/test/included/unit_test.hpp>

#include <sstream>
#include <stdexcept>

// IsValidNumber
BOOST_AUTO_TEST_CASE(IsValidNumber_ValidCases) {
    BOOST_CHECK(IsValidNumber(1));
    BOOST_CHECK(IsValidNumber(999));
}

BOOST_AUTO_TEST_CASE(IsValidNumber_InvalidCases) {
    BOOST_CHECK(!IsValidNumber(0));
    BOOST_CHECK(!IsValidNumber(-5));
}

// BinPow
BOOST_AUTO_TEST_CASE(BinPow_CorrectValues) {
    BOOST_CHECK_EQUAL(BinPow(10, 0), 1);
    BOOST_CHECK_EQUAL(BinPow(10, 1), 10);
    BOOST_CHECK_EQUAL(BinPow(10, 3), 1000);
}

// FindMinDigit
BOOST_AUTO_TEST_CASE(FindMinDigit_CorrectValues) {
    BOOST_CHECK_EQUAL(FindMinDigit(123), 1);
    BOOST_CHECK_EQUAL(FindMinDigit(100), 1);
    BOOST_CHECK_EQUAL(FindMinDigit(505'050), 5);
}

BOOST_AUTO_TEST_CASE(FindMinDigit_ThrowsExceptions) {
    BOOST_CHECK_THROW(FindMinDigit(0), std::invalid_argument);
    BOOST_CHECK_THROW(FindMinDigit(-1), std::invalid_argument);
}

// CountDigits
BOOST_AUTO_TEST_CASE(CountDigits_Basic) {
    BOOST_CHECK_EQUAL(CountDigits(5), 1);
    BOOST_CHECK_EQUAL(CountDigits(42), 2);
    BOOST_CHECK_EQUAL(CountDigits(999), 3);
}

// ProcessNumber
BOOST_AUTO_TEST_CASE(ProcessNumber_WorksCorrectly) {
    BOOST_CHECK_EQUAL(ProcessNumber(1), 111);
    BOOST_CHECK_EQUAL(ProcessNumber(123), 11'231);
    BOOST_CHECK_EQUAL(ProcessNumber(987'654'321), 19'876'543'211LL);
}

BOOST_AUTO_TEST_CASE(ProcessNumber_Throws) {
    BOOST_CHECK_THROW(ProcessNumber(0), std::invalid_argument);
    BOOST_CHECK_THROW(ProcessNumber(-1), std::invalid_argument);
}

// GetNumber
BOOST_AUTO_TEST_CASE(GetNumber_ReadsValidInput) {
    std::stringstream ss("123");
    std::cin.rdbuf(ss.rdbuf());
    BOOST_CHECK_EQUAL(GetNumber(), 123);
}

BOOST_AUTO_TEST_CASE(GetNumber_ZeroIsNotNatural) {
    std::stringstream ss("0");
    std::cin.rdbuf(ss.rdbuf());
    BOOST_CHECK_THROW(GetNumber(), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(GetNumber_OverflowLargeNumber) {
    std::stringstream ss("9999999999999999999999999");
    std::cin.rdbuf(ss.rdbuf());
    BOOST_CHECK_THROW(GetNumber(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(GetNumber_PreventOverflowNumber) {
    std::stringstream ss("10000000000000000");
    std::cin.rdbuf(ss.rdbuf());
    BOOST_CHECK_THROW(GetNumber(), std::out_of_range);
}

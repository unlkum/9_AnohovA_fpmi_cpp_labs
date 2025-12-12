/*
С клавиатуры вводится натуральное число n. Добавить слева
и справа от этого числа наименьшую отличную от нуля цифру
*/

#include "task.h"
// #include "pch.h"

#include <cctype>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

bool IsValidNumber(int64_t num) {
    return num > 0;
}

// 2^9  9-1 = 8, 2^8 = 4^4
int64_t BinPow(int64_t base, int64_t exp) {
    int64_t result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return result;
}

int64_t GetNumber() {
    std::cout << "Enter a natural number:\n";

    int64_t num;

    if (!(std::cin >> num)) {
        throw std::runtime_error("Input error: failed to read number");
    }

    if (num <= 0) {
        throw std::invalid_argument("Error: number must be positive");
    }

    if (std::to_string(num).size() > 16) {
        throw std::out_of_range("Error: number is too large");
    }

    return num;
}

int FindMinDigit(int64_t num) {
    if (num <= 0) {
        throw std::invalid_argument("Number must be positive");
    }

    int min_digit = 10;
    while (num > 0) {
        int digit = num % 10;
        if (digit != 0 && digit < min_digit) {
            min_digit = digit;
        }
        num /= 10;
    }
    if (min_digit == 10) {
        throw std::logic_error("No non-zero digits");
    }

    return min_digit;
}

int CountDigits(int64_t num) {
    int cnt = 0;
    while (num > 0) {
        num /= 10;
        ++cnt;
    }
    return cnt;
}

int64_t ProcessNumber(int64_t num) {
    if (num <= 0) {
        throw std::invalid_argument("Number must be positive");
    }
    int digits = CountDigits(num);
    int min_digit = FindMinDigit(num);

    int64_t left = min_digit * BinPow(10, digits + 1);
    int64_t middle = num * 10;
    int64_t right = min_digit;

    return left + middle + right;
}

void PrintResult(const int64_t result) {
    std::cout << result << '\n';
}

/*
int main() {
    try {
        int64_t num = GetNumber();
        int64_t result = ProcessNumber(num);
        PrintResult(result);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
*/
/*
С клавиатуры вводится натуральное число n. Добавить слева
и справа от этого числа наименьшую отличную от нуля цифру
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

bool IsValidNaturalNumber(const std::string& s) {
    if (s.empty()) {
        return false;
    }
    // All characters are digits
    for (const char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    // Natural number can't start with 0
    if (s[0] == '0') {
        return false;
    }

    return true;
}

std::string GetNumber() {
    std::string num;
    std::cout << "Enter a natural number:\n";

    if (!(std::cin >> num)) {
        throw std::runtime_error("Input error: failed to read number");
    }

    if (!IsValidNaturalNumber(num)) {
        throw std::invalid_argument("Error: invalid natural number");
    }

    return num;
}

char FindMinNonZeroDigit(const std::string& num) {
    char min_digit = '9';
    for (const char c : num) {
        if (c != '0' && c < min_digit) {
            min_digit = c;
        }
    }
    return min_digit;
}

std::string ProcessNumber(const std::string& num) {
    char min_digit = FindMinNonZeroDigit(num);
    
    std::string result(num.size() + 2, min_digit);
    
    std::copy(num.begin(), num.end(), result.begin() + 1);
    
    return result;
}

void PrintResult(const std::string& result) {
    std::cout << result << '\n';
}

int main() {
    try {
        std::string num = GetNumber();
        std::string result = ProcessNumber(num);
        PrintResult(result);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
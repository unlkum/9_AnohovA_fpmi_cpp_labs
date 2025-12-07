#include "task.h"

#include <iostream>

int main() {
    Fraction a;
    Fraction b(-3, 4);
    Fraction c(10);
    std::cout << b.numerator() << ' ' << b.denominator() << '\n';
    std::cout << c.numerator() << ' ' << c.denominator() << '\n';

    std::cout << a + b;
}
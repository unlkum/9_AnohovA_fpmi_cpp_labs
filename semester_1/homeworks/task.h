#pragma once

#include <numeric>
#include <stdexcept>

class Fraction {
   private:
    int numer_;
    int denom_;

    void normalize() {
        if (denom_ == 0) {
            throw std::invalid_argument("Denom can't be 0");
        }
        // numer_ = abs(numer_);
        // denom_ = abs(denom_);
        int g = std::gcd(numer_ < 0 ? -numer_ : numer_, denom_);
        if (g > 1) {
            numer_ /= g;
            denom_ /= g;
        }
    }

   public:
    // Constructors
    Fraction(int n, int m) : numer_(n), denom_(m) {
        normalize();
    }

    Fraction(int n) : numer_(n), denom_(1) {
        normalize();
    }

    Fraction() : numer_(0), denom_(1) {
    }

    // Operators
    Fraction operator+(const Fraction& a) const {
        
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(other.numer_ * numer_, other.denom_ * denom_);
    }

    Fraction operator-(const Fraction& a) {
        int n = a.numerator() * b.denominator() - b.numerator() * a.denominator();
        int d = a.denominator() * b.denominator();
        return Fraction(n, d);
    }

    Fraction operator/(const Fraction& a, const Fraction& b) {
        if (b.numerator() == 0) {
            throw std::invalid_argument("Division by zero fraction");
        }
        return Fraction(a.numerator() * b.denominator(), a.denominator() * b.numerator());
    }

    // Get
    int numerator() const {
        return numer_;
    }

    int denominator() const {
        return denom_;
    }

    // Destructor
    ~Fraction();
};
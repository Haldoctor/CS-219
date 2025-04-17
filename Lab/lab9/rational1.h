#pragma once 
#include <iostream>

class Rational {
private:
    static int id;
    int numerator;
    int denominator;
public:
    Rational(int n = 0, int d = 1) : numerator(n), denominator(d) {  // 允许隐式转换
        std::cout << "Construct_" << ++id << ", n:" << numerator << " , d:" << denominator << std::endl;
    }

    friend Rational operator*(const Rational& lhs, const Rational& rhs);
    friend Rational operator*(int n, const Rational& rhs);
    friend Rational operator*(const Rational& lhs, int n);
    friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);
};

int Rational::id = 0;

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator * rhs.numerator, lhs.denominator * rhs.denominator);
}

Rational operator*(int n, const Rational& rhs) {
    return Rational(n * rhs.numerator, rhs.denominator);
}

Rational operator*(const Rational& lhs, int n) {
    return Rational(lhs.numerator * n, lhs.denominator);
}

std::ostream& operator<<(std::ostream& os, const Rational& rhs) {
    os << rhs.numerator << "/" << rhs.denominator;
    return os;
}

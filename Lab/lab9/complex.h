#ifndef _MYCOMPLEX_H_
#define _MYCOMPLEX_H_

#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double re = 0, double im = 0) : real(re), imag(im) {}  

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator~() const;

    friend Complex operator+(int scalar, const Complex& c);   
    friend Complex operator-(int scalar, const Complex& c);    
    friend Complex operator*(int scalar, const Complex& c);    
    friend Complex operator+(const Complex& c, int scalar);    
    friend Complex operator-(const Complex& c, int scalar);   
    friend Complex operator*(const Complex& c, int scalar);    

    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend std::istream& operator>>(std::istream& is, Complex& c);
};

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(
        real * other.real - imag * other.imag,
        real * other.imag + imag * other.real
    );
}

Complex Complex::operator~() const {
    return Complex(real, -imag);
}

Complex operator+(int scalar, const Complex& c) {
    return Complex(scalar + c.real, c.imag);
}

Complex operator-(int scalar, const Complex& c) {
    return Complex(scalar - c.real, -c.imag);
}

Complex operator*(int scalar, const Complex& c) {
    return Complex(scalar * c.real, scalar * c.imag);
}

Complex operator+(const Complex& c, int scalar) {
    return Complex(c.real + scalar, c.imag);
}

Complex operator-(const Complex& c, int scalar) {
    return Complex(c.real - scalar, c.imag);
}

Complex operator*(const Complex& c, int scalar) {
    return Complex(c.real * scalar, c.imag * scalar);
}

bool Complex::operator==(const Complex& other) const {
    return (real == other.real) && (imag == other.imag);
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real;
    os << (c.imag >= 0 ? "+" : "-") << std::abs(c.imag) << "i";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c) {
    is >> c.real >> c.imag;
    return is;
}

#endif

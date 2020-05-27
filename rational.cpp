//
// Created by Mina on 26.05.2020.
//

#include "rational.hpp"
#include "exception.hpp"

// ----------------------------------------- global functions -----------------------------------------

int gcd(int a, int b) { // gcd = greatest common divisor (groesster gemeinsamer Teiler)
    int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r._numerator << "/" << r._denominator;
    return os;
}

Rational Rational::add(const Rational& x) const {
    Rational r;
    r._numerator = _numerator * x._denominator + _denominator * x._numerator;
    r._denominator = _denominator * x._denominator;
    r.cancel();
    return r;
}

Rational Rational::sub(const Rational& x) const {
    return add(-x);
}

Rational Rational::mul(const Rational& x) const {
    //std::cout << "Beginning of method mul()" << std::endl;
    Rational r(_numerator * x._numerator , _denominator * x._denominator);
    r.cancel();
    return r;
}

Rational Rational::div(Rational x) {
    x.inverse();
    return mul(x);
}

void Rational::inverse() {
    if (_numerator == 0) {
        throw DivisionByZeroException();
    }
    int t = _numerator;
    _numerator = _denominator;
    _denominator = t;
}

void Rational::cancel() {
    int div = gcd(_numerator, _denominator);
    _numerator /= div;
    _denominator /= div;
}

Rational::Rational(int z, int n) {
    if (n == 0) {
        throw DivisionByZeroException();
    }
    std::cout << "Constructor is working..." << std::endl;
    _numerator = z;
    _denominator = n;
}

Rational::Rational(const Rational& x) {
    std::cout << "Copy constructor is working..." << std::endl;
    _numerator = x._numerator;
    _denominator = x._denominator;
}

Rational::Rational(const Rational&& x)  noexcept {
    std::cout << "Move constructor is working..." << std::endl;
    _numerator = x._numerator;
    _denominator = x._denominator;
}

Rational::~Rational() {
    std::cout << "Destructor is working..." << std::endl;
}

Rational& Rational::operator=(const Rational& orig) {
    std::cout << "Assignment operator is working..." << std::endl;
    _numerator = orig._numerator;
    _denominator = orig._denominator;
    return *this;
}

Rational Rational::operator-() const {
    return Rational(-_numerator, -_denominator);
}

Rational Rational::operator+(const Rational& x) const {
    return add(x);
}

Rational Rational::operator-(const Rational& x) const {
    return sub(x);
}

Rational Rational::operator*(const Rational& x) const {
    //std::cout << "Anfang Methode operator*" << std::endl;
    return mul(x);
}

Rational Rational::operator/(const Rational& x) {
    return div(x);
}

bool Rational::operator<(const Rational& x) const {
    return static_cast<double>(this->_numerator)/static_cast<double>(this->_denominator) < static_cast<double>(x._numerator)/ static_cast<double>(x._denominator);
}

bool Rational::operator>(const Rational& x) const {
    return static_cast<double>(this->_numerator)/static_cast<double>(this->_denominator) > static_cast<double>(x._numerator)/ static_cast<double>(x._denominator);
}

bool Rational::operator==(const Rational& x) const {
    double a = static_cast<double>(this->_numerator)/static_cast<double>(this->_denominator);
    double b = static_cast<double>(x._numerator)/ static_cast<double>(x._denominator);
    bool equality = a - 0.0000001 < b && a + 0.0000001 > b;
    return equality;
}
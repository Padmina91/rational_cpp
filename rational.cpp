//
// Created by Mina on 26.05.2020.
//

#include "rational.hpp"
#include "exception.hpp"
#include <iostream>

// ----------------------------------------- global functions -----------------------------------------

/**
 * Calculates the greatest common divisor.
 * @param a (long long int)
 * @param b (long long int)
 * @return gcd (long long int)
 */
long long int gcd(long long int a, long long int b) {
    long long int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

/**
 * Output operator overloading.
 * @param os (std::ostream&)
 * @param r (const Rational&)
 * @return os (std::ostream&)
 */
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r._numerator << "/" << r._denominator;
    return os;
}

/**
 * Adds two Rational objects.
 * @param x (const Rational&)
 * @return result (Rational)
 */
Rational Rational::add(const Rational& x) const {
    Rational r;
    r._numerator = _numerator * x._denominator + _denominator * x._numerator;
    r._denominator = _denominator * x._denominator;
    r.cancel();
    return r;
}

/**
 * Subtracts the passed in Rational object from the one it's called on.
 * @param x (const Rational&)
 * @return result (Rational)
 */
Rational Rational::sub(const Rational& x) const {
    return add(-x);
}

/**
 * Multiplies two Rational objects.
 * @param x (const Rational&)
 * @return result (Rational)
 */
Rational Rational::mul(const Rational& x) const {
    //std::cout << "Beginning of method mul()" << std::endl;
    Rational r(_numerator * x._numerator, _denominator * x._denominator);
    r.cancel();
    return r;
}

/**
 * Divides the Rational object this method is called on by the one passed in as parameter.
 * @param x (Rational)
 * @return result (Rational)
 */
Rational Rational::div(Rational x) {
    x.inverse();
    return mul(x);
}

/**
 * Inverts the Rational object.
 */
void Rational::inverse() {
    if (_numerator == 0) {
        throw DivisionByZeroException();
    }
    long long int t = _numerator;
    _numerator = _denominator;
    _denominator = t;
}

/**
 * Cancels the Rational object.
 */
void Rational::cancel() {
    long long int div = gcd(_numerator, _denominator);
    _numerator /= div;
    _denominator /= div;
}

/**
 * Default constructor for Rational.
 * @param z (long long int) default: 1
 * @param n (long long int) default: 1
 * @param nf (NumberFormat*) default: nullptr
 */
Rational::Rational(long long int z, long long int n, NumberFormat *nf) : _numerator(z), _denominator(n), _nf(nf) {
    if (n == 0) {
        throw DivisionByZeroException();
    }
    this->cancel();
    std::cout << "Constructor of Rational is working..." << std::endl;
}

/**
 * Copy constructor of Rational.
 * @param x (Rational&)
 */
Rational::Rational(const Rational& x) : _numerator(x._numerator), _denominator(x._denominator), _nf(x._nf) {
    std::cout << "Copy constructor of Rational is working..." << std::endl;
}

/**
 * Destructor of Rational.
 */
Rational::~Rational() {
    std::cout << "Destructor of Rational is working..." << std::endl;
}

/**
 * Getter-method for _numerator.
 * @return _numerator (long long int)
 */
long long int Rational::get_numerator() const {
    return _numerator;
}

/**
 * Getter-method for _denominator.
 * @return _denominator (long long int)
 */
long long int Rational::get_denominator() const {
    return _denominator;
}

/**
 * Assignment operator overloading.
 * @param orig (const Rational&)
 * @return *this (Rational&)
 */
Rational& Rational::operator=(const Rational& orig) {
    if (&orig != this) {
        std::cout << "Assignment operator is working..." << std::endl;
        _numerator = orig._numerator;
        _denominator = orig._denominator;
        return *this;
    }
    std::cout << "Assignment operator aborted!" << std::endl;
    return *this;
}

/**
 * Algebraic sign - overloading.
 * @return negative (Rational)
 */
Rational Rational::operator-() const {
    return Rational(-_numerator, -_denominator);
}

/**
 * Plus operator overloading.
 * @param x (const Rational&)
 * @return result (Rational)
 */
Rational Rational::operator+(const Rational& x) const {
    return add(x);
}

/**
 * Minus operator overloading.
 * @param x (const Rational&)
 * @return result (Rational)
 */
Rational Rational::operator-(const Rational& x) const {
    return sub(x);
}

/**
 * Multiplication operator overloading.
 * @param x (const Rational&)
 * @return result (Rational)
 */
Rational Rational::operator*(const Rational& x) const {
    //std::cout << "Anfang Methode operator*" << std::endl;
    return mul(x);
}

/**
 * Division operator overloading.
 * @param x (const Rational&)
 * @return result (Rational)
 */
Rational Rational::operator/(const Rational& x) {
    return div(x);
}

/**
 * "Less than" operator overloading.
 * @param x (const Rational&)
 * @return is_less_than (bool)
 */
bool Rational::operator<(const Rational& x) const {
    bool is_less_than = static_cast<double>(this->_numerator) / static_cast<double>(this->_denominator) <
                        static_cast<double>(x._numerator) / static_cast<double>(x._denominator);
    return is_less_than;
}

/**
 * "Greater than" operator overloading.
 * @param x (const Rational&)
 * @return is_greater_than (bool)
 */
bool Rational::operator>(const Rational& x) const {
    bool is_greater_than = static_cast<double>(this->_numerator) / static_cast<double>(this->_denominator) >
                           static_cast<double>(x._numerator) / static_cast<double>(x._denominator);
    return is_greater_than;
}

/**
 * Equality operator overloading.
 * @param x (const Rational&)
 * @return equality (bool)
 */
bool Rational::operator==(const Rational& x) const {
    double a = static_cast<double>(this->_numerator) / static_cast<double>(this->_denominator);
    double b = static_cast<double>(x._numerator) / static_cast<double>(x._denominator);
    bool equality = a - 0.0000001 < b && a + 0.0000001 > b;
    return equality;
}

/**
 * Returns the double value of the Rational object.
 * @return val (double)
 */
double Rational::double_value() const {
    double val = static_cast<double>(_numerator) / static_cast<double>(_denominator);
    return val;
}

/**
 * Converts the Rational object to a string, based on the format.
 * @return str (std::string)
 */
std::string Rational::to_string() {
    if (_nf != nullptr) {
        return _nf->format(*this);
    }
    return "";
}
//
// Created by Mina on 26.05.2020.
//

#ifndef RATIONAL_CPP_RATIONAL_HPP
#define RATIONAL_CPP_RATIONAL_HPP

#include <iostream>

class Rational {
    friend std::ostream& operator<<(std::ostream&, const Rational&);
    
private:
    int _numerator, _denominator;
    
    Rational add(Rational);
    Rational sub(Rational);
    Rational mul(Rational);
    Rational div(Rational);
    void inverse();
    void cancel();

public:
    explicit Rational(int z = 1, int n = 1);
    Rational(const Rational&);
    ~Rational();
    
    Rational& operator=(const Rational&);
    Rational operator-();
    Rational operator+(const Rational&);
    Rational operator-(const Rational&);
    Rational operator*(const Rational&);
    Rational operator/(const Rational&);
    
    bool operator<(const Rational&);
    bool operator>(const Rational&);
    bool operator==(const Rational&);
};

#endif //RATIONAL_CPP_RATIONAL_HPP
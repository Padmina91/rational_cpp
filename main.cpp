//
// Created by Mina on 26.05.2020.
//

#include "rational.hpp"

int main() {
    Rational a(1,2), b(2,3), x;
    Rational c = a * b; // Kopier-Konstruktor?
    std::cout  << c << std::endl;
    x = a * b; //  Zuweisungsoperator?
    std::cout  << x << std::endl;
}
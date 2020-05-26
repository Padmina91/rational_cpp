//
// Created by Mina on 26.05.2020.
//

#include "rational.hpp"
using std::cout;
using std::endl;

int main() {
    Rational a(1,2), b(2,3), x;
    cout << "-----------------------------------------" << endl;
    Rational c = a * b; // Kopier-Konstruktor?
    cout << "-----------------------------------------" << endl;
    cout  << c << endl;
    cout << "-----------------------------------------" << endl;
    x = a * b; //  Zuweisungsoperator?
    cout << "-----------------------------------------" << endl;
    cout  << x << endl;
    cout << "-----------------------------------------" << endl;
}
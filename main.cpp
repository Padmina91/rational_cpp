//
// Created by Mina on 26.05.2020.
//

#include "rational.hpp"
#include <iostream>
using std::cout;
using std::endl;

int main() {
    
    NumberFormatEN en;
    
    Rational r = en.parse("125,458,148.48");
    
    cout << r << endl;

    
    
    
}
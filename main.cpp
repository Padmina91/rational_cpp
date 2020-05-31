//
// Created by Mina on 26.05.2020.
//

#include "rational.hpp"
#include <iostream>
using std::cout;
using std::endl;

int main() {
    
    NumberFormatDE de;
    
    //Rational r = de.parse("125,458,148.48");
    
    //cout << r << endl;

    Rational asdf(400000000, 1, &de);
    
    cout << asdf.to_string() << endl;
}
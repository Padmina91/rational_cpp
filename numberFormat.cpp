//
// Created by Schne on 30.05.2020.
//

#include "numberFormat.hpp"
#include <iostream>


NumberFormat::NumberFormat(Format format) : _format(format) {
        std::cout << "Constructor of NumberFormat is working..." << std::endl;
}


std::string NumberFormat::format(Rational *x) {
    return ""; //TODO: implement Function!
}

Rational NumberFormat::parse(std::string val_string) {
    return Rational(1, 2); //TODO: implement Function!
}




NumberFormatDE::NumberFormatDE() : NumberFormat(Format::european) {
    std::cout << "Constructor of NumberFormatDE is working..." << std::endl;
}




NumberFormatEN::NumberFormatEN() : NumberFormat(Format::english) {
    std::cout << "Constructor of NumberFormatEN is working..." << std::endl;
}
//
// Created by Schne on 30.05.2020.
//

#include "numberFormat.hpp"
#include <iostream>


NumberFormat::NumberFormat(Format format) : _format(format) {
        std::cout << "Constructor of NumberFormat is working..." << std::endl;
}








NumberFormatDE::NumberFormatDE() : NumberFormat(Format::european) {
    std::cout << "Constructor of NumberFormatDE is working..." << std::endl;
}




NumberFormatEN::NumberFormatEN() : NumberFormat(Format::english) {
    std::cout << "Constructor of NumberFormatEN is working..." << std::endl;
}
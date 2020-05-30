//
// Created by Mina on 30.05.2020.
//

#ifndef RATIONAL_CPP_NUMBERFORMAT_HPP
#define RATIONAL_CPP_NUMBERFORMAT_HPP

#include <string>
#include "rational.hpp"

class NumberFormat {
protected:
    enum class Format {
        european, english
    };
    
    Format _format;
    
public:
    NumberFormat(Format format);
    
    std::string format(Rational* x);
    
};


class NumberFormatDE : public NumberFormat {
public:
    NumberFormatDE();
};


class NumberFormatEN : public NumberFormat {
public:
    NumberFormatEN();
};


#endif //RATIONAL_CPP_NUMBERFORMAT_HPP
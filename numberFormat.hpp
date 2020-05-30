//
// Created by Mina on 30.05.2020.
//

#ifndef RATIONAL_CPP_NUMBERFORMAT_HPP
#define RATIONAL_CPP_NUMBERFORMAT_HPP

#include <string>
#include "rational.hpp"

class Rational;

class NumberFormat {
protected:
    enum class Format {
        european, english
    };
    
    Format _format;
    
    
    static std::string format_help(Rational* x);
    static Rational parse_help(std::string val_string);
    
public:
    NumberFormat(Format format);
    
    std::string format(Rational* x);
    Rational parse(std::string val_string);
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
//
// Created by Mina on 26.05.2020.
//

#ifndef RATIONAL_CPP_EXCEPTION_HPP
#define RATIONAL_CPP_EXCEPTION_HPP

#include <exception>

class DivisionByZeroException : public std::exception {};

class NotANumberException : public std::exception {};

#endif //RATIONAL_CPP_EXCEPTION_HPP
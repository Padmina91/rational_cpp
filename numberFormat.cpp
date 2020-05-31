//
// Created by Mina on 30.05.2020.
//

#include "numberFormat.hpp"
#include "exception.hpp"
#include <iostream>
#include <cmath>

NumberFormat::NumberFormat(Format format) : _format(format) {
    std::cout << "Constructor of NumberFormat is working..." << std::endl;
}

NumberFormat::~NumberFormat() noexcept {
    std::cout << "Destructor of NumberFormat is working..." << std::endl;
}

bool NumberFormat::check_string_correctness(const std::string& str, Format format) {
    bool string_correct = true;
    char thousand_sep = format == Format::german ? '.' : ',';
    char decimal_sep = format == Format::german ? ',' : '.';
    // first check if the spacing of thousand separators are correct, if applicable
    size_t thousand_sep_at = str.find_first_of(thousand_sep);
    size_t another_thousand_sep_at;
    do {
        if (thousand_sep_at != std::string::npos) {
            another_thousand_sep_at = str.find_first_of(thousand_sep, thousand_sep_at + 1);
            if (another_thousand_sep_at != std::string::npos) {
                string_correct = another_thousand_sep_at - 4 == thousand_sep_at;
                thousand_sep_at = another_thousand_sep_at;
            }
        }
    } while (thousand_sep_at != std::string::npos && another_thousand_sep_at != std::string::npos);
    // now thousand_sep_at has either the value npos or the position of the last thousand separator
    // next check that that there are exactly 3 positions between the last thousand separator and the decimal separator
    size_t decimal_sep_at = str.find_first_of(decimal_sep);
    if (decimal_sep_at != std::string::npos && thousand_sep_at != std::string::npos && string_correct) {
        string_correct = decimal_sep_at - 4 == thousand_sep_at;
    }
    // next make sure there is only one decimal separator in the string
    if (str.find_first_of(decimal_sep, decimal_sep_at + 1) != std::string::npos) {
        string_correct = false;
    }
    // next check if there are only numbers and separators in the string
    if (str.find_first_not_of("-0123456789,.") != std::string::npos) {
        string_correct = false;
    }
    // make sure that the algebraic sign '-' is either at the first position or non-existent
    if (str.find_first_of('-') != 0 && str.find_first_of('-') != std::string::npos) {
        string_correct = false;
    }
    return string_correct;
}

void NumberFormat::remove_all(std::string& str, char to_remove) {
    size_t index_to_remove = str.find_first_of(to_remove);
    while (index_to_remove != std::string::npos) {
        str.erase(str.begin() + index_to_remove);
        index_to_remove = str.find_first_of(to_remove);
    }
}

void NumberFormat::replace_character(std::string& str, char to_remove, std::string&& to_put_instead) {
    size_t index_to_replace = str.find_first_of(to_remove);
    if (index_to_replace != std::string::npos) {
        str.replace(index_to_replace, 1, to_put_instead);
    }
}

void NumberFormat::add_thoudands_sep(std::string& str, Format format) {
    std::string thousand_sep = format == Format::german ? "." : ",";
    char decimal_sep = format == Format::german ? ',' : '.';
    size_t pos_of_decimal_sep = str.find_first_of(decimal_sep);
    pos_of_decimal_sep = pos_of_decimal_sep == std::string::npos ? str.length() : pos_of_decimal_sep;
    size_t pos_of_thoudand_sep = pos_of_decimal_sep - 4;
    while (pos_of_thoudand_sep > str.length()) {
        str.insert(pos_of_thoudand_sep, thousand_sep);
        pos_of_thoudand_sep -= 4;
    }
}

std::string NumberFormat::format_help(const Rational& x, Format format) {
    double rational = static_cast<double>(x.get_numerator()) / static_cast<double>(x.get_denominator());
    std::string return_string = std::to_string(rational);
    if (format == Format::german) {
        replace_character(return_string, '.', ",");
    }
    if (rational > 1000.0) {
        add_thoudands_sep(return_string, format);
    }
    return return_string;
}

Rational NumberFormat::parse_help(std::string& val_string, Format format) {
    bool correct_number = check_string_correctness(val_string, format);
    if (!correct_number) {
        throw NotANumberException();
    }
    if (format == Format::german) {
        NumberFormat::remove_all(val_string, '.');
        NumberFormat::replace_character(val_string, ',', ".");
    } else {
        NumberFormat::remove_all(val_string, ',');
    }
    double val_double = std::stod(val_string);
    long long int denominator = 1;
    while (static_cast<double>(static_cast<long long int>(val_double)) + 0.0000001 < val_double &&
           static_cast<double>(static_cast<long long int>(val_double)) + 0.999999 > val_double) {
        denominator *= 10;
        val_double *= 10.0;
    }
    auto numerator = static_cast<long long int>(std::round(val_double));
    Rational r(numerator, denominator);
    return r;
}

NumberFormatDE::NumberFormatDE() : NumberFormat(Format::german) {
    std::cout << "Constructor of NumberFormatDE is working..." << std::endl;
}

NumberFormatDE::~NumberFormatDE() noexcept {
    std::cout << "Destructor of NumberFormatDE is working..." << std::endl;
}

std::string NumberFormatDE::format(const Rational& x) const {
    return NumberFormat::format_help(x, Format::german);
}

Rational NumberFormatDE::parse(std::string&& val_string) {
    std::string to_parse = val_string;
    return parse(to_parse);
}

Rational NumberFormatDE::parse(std::string& val_string) {
    return NumberFormat::parse_help(val_string, Format::german);
}

NumberFormatEN::NumberFormatEN() : NumberFormat(Format::english) {
    std::cout << "Constructor of NumberFormatEN is working..." << std::endl;
}

NumberFormatEN::~NumberFormatEN() noexcept {
    std::cout << "Destructor of NumberFormatEN is working..." << std::endl;
}

std::string NumberFormatEN::format(const Rational& x) const {
    return NumberFormat::format_help(x, Format::english);
}

Rational NumberFormatEN::parse(std::string&& val_string) {
    std::string to_parse = val_string;
    return parse(to_parse);
}

Rational NumberFormatEN::parse(std::string& val_string) {
    return NumberFormat::parse_help(val_string, Format::english);
}
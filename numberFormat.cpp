//
// Created by Mina on 30.05.2020.
//

#include "numberFormat.hpp"
#include "exception.hpp"
#include <cmath>
#include <iostream>
#define DEBUG false

/**
 * Only for debugging and testing: Keeps track of the number of NumberFormat objects alive.
 */
int NumberFormat::num_of_NumberFormat_objects_alive = 0;

/**
 * Only for debugging and testing: Keeps track of the number of NumberFormatDE objects alive.
 */
int NumberFormatDE::num_of_NumberFormatDE_objects_alive = 0;

/**
 * Only for debugging and testing: Keeps track of the number of NumberFormatEN objects alive.
 */
int NumberFormatEN::num_of_NumberFormatEN_objects_alive = 0;

/**
 * Default constructor of NumberFormat.
 * @param format (Format)
 */
NumberFormat::NumberFormat(Format format) : _format(format) {
#if DEBUG
    std::cout << "Constructor of NumberFormat is working..." << std::endl;
#endif
    num_of_NumberFormat_objects_alive++;
}

/**
 * Copy constructor of NumberFormat.
 * @param orig (NumberFormat&)
 */
NumberFormat::NumberFormat(NumberFormat& orig) : _format(orig._format) {
#if DEBUG
    std::cout << "Copy Constructor of NumberFormat is working..." << std::endl;
#endif
    num_of_NumberFormat_objects_alive++;
}

/**
 * Default destructor of NumberFormat.
 */
NumberFormat::~NumberFormat() noexcept {
#if DEBUG
    std::cout << "Destructor of NumberFormat is working..." << std::endl;
#endif
    num_of_NumberFormat_objects_alive--;
}

/**
 * Getter method for _format.
 * @return _format (NumberFormat::Format)
 */
NumberFormat::Format NumberFormat::get_format() {
    return _format;
}

/**
 * Checks if the string is a correct floating point number.
 * @param str (const std::string&)
 * @param format (Format)
 * @return string_correct
 */
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

/**
 * Removes all occurrences of the specified character within the string.
 * @param str (std::string&)
 * @param to_remove (char)
 */
void NumberFormat::remove_all(std::string& str, char to_remove) {
    size_t index_to_remove = str.find_first_of(to_remove);
    while (index_to_remove != std::string::npos) {
        str.erase(str.begin() + index_to_remove);
        index_to_remove = str.find_first_of(to_remove);
    }
}

/**
 * Replaces the specified character in the string with the desired string.
 * @param str (std::string&)
 * @param to_remove (char)
 * @param to_put_instead (std::string&&) - rvalue
 */
void NumberFormat::replace_character(std::string& str, char to_remove, std::string&& to_put_instead) {
    size_t index_to_replace = str.find_first_of(to_remove);
    if (index_to_replace != std::string::npos) {
        str.replace(index_to_replace, 1, to_put_instead);
    }
}

/**
 * Depending on the format, inserts the thousand separator into the string.
 * @param str (std::string&)
 * @param format (Format)
 */
void NumberFormat::add_thoudands_sep(std::string& str, Format format) {
    std::string thousand_sep = format == Format::german ? "." : ",";
    char decimal_sep = format == Format::german ? ',' : '.';
    size_t pos_of_decimal_sep = str.find_first_of(decimal_sep);
    pos_of_decimal_sep = pos_of_decimal_sep == std::string::npos ? str.length() : pos_of_decimal_sep;
    size_t pos_of_thoudand_sep = pos_of_decimal_sep - 3;
    while (pos_of_thoudand_sep < str.length() && pos_of_thoudand_sep != 0) {
        str.insert(pos_of_thoudand_sep, thousand_sep);
        pos_of_thoudand_sep -= 3;
    }
}

/**
 * Removes unnecessary zero's behind the decimal separator.
 * @param str (std::string&)
 * @param decimal_sep (char)
 */
void NumberFormat::remove_unnecessary_zeros(std::string& str, char decimal_sep) {
    int last_index_neq_null = str.find_last_not_of('0'); // neq = not equal
    str.resize(last_index_neq_null + 1);
    // remove the decimal separator if not needed
    if (str[str.length() - 1] == decimal_sep) {
        str.resize(str.size() - 1);
    }
    str.shrink_to_fit();
}

/**
 * Converts the rational number x into a string, depending on the desired format.
 * @param x (const Rational&)
 * @param format (Format)
 * @return return_string (std::string)
 */
std::string NumberFormat::format_help(const Rational& x, Format format) {
    char decimal_sep = format == Format::german ? ',' : '.';
    double rational = x.double_value();
    std::string return_string = std::to_string(rational);
    if (format == Format::german) {
        replace_character(return_string, '.', ",");
    }
    if (rational > 1000.0) {
        add_thoudands_sep(return_string, format);
    }
    // remove unnecessary 0's at the end of string, if behind a decimal separator
    if (return_string.find_first_of(decimal_sep) != std::string::npos && return_string.find_last_of('0') + 1 == return_string.length()) {
        remove_unnecessary_zeros(return_string, decimal_sep);
    }
    return return_string;
}

/**
 * Parses the string to a rational number.
 * @param val_string (std::string&)
 * @param format (Format)
 * @throws NotANumberException
 * @throws std::invalid_argument (from stod())
 * @return r (Rational)
 */
Rational NumberFormat::parse_help(std::string& val_string, NumberFormat& nf) {
    Format format =  nf.get_format() == Format::english ? Format::english : Format::german;
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
    Rational r(numerator, denominator, &nf);
    return r;
}

/**
 * Default constructor of NumberFormatDE.
 */
NumberFormatDE::NumberFormatDE() : NumberFormat(Format::german) {
#if DEBUG
    std::cout << "Constructor of NumberFormatDE is working..." << std::endl;
#endif
    num_of_NumberFormatDE_objects_alive++;
}

/**
 * Copy constructor of NumberFormatDE.
 * @param orig (NumberFormat&)
 */
NumberFormatDE::NumberFormatDE(NumberFormatDE& orig) : NumberFormat(orig._format) {
#if DEBUG
    std::cout << "Copy Constructor of NumberFormatDE is working..." << std::endl;
#endif
    num_of_NumberFormatDE_objects_alive++;
}

/**
 * Destructor of NumberFormatDE.
 */
NumberFormatDE::~NumberFormatDE() noexcept {
#if DEBUG
    std::cout << "Destructor of NumberFormatDE is working..." << std::endl;
#endif
    num_of_NumberFormatDE_objects_alive--;
}

/**
 * Converts the rational number into a string (german format).
 * @param x (const Rational&)
 * @return return_string (std::string)
 */
std::string NumberFormatDE::format(const Rational& x) const {
    return NumberFormat::format_help(x, Format::german);
}

/**
 * Parses the rvalue string to a rational number.
 * @param val_string (std::string&&) - rvalue
 * @return r (Rational)
 */
Rational NumberFormatDE::parse(std::string&& val_string) {
    std::string to_parse = val_string;
    return parse(to_parse);
}

/**
 * Parses the lvalue string to a rational number.
 * @param val_string (std::string&) - lvalue
 * @return r (Rational)
 */
Rational NumberFormatDE::parse(std::string& val_string) {
    return NumberFormat::parse_help(val_string, *this);
}

/**
 * Default constructor of NumberFormatEN.
 */
NumberFormatEN::NumberFormatEN() : NumberFormat(Format::english) {
#if DEBUG
    std::cout << "Constructor of NumberFormatEN is working..." << std::endl;
#endif
    num_of_NumberFormatEN_objects_alive++;
}

/**
 * Copy constructor of NumberFormatEN.
 * @param orig (NumberFormat&)
 */
NumberFormatEN::NumberFormatEN(NumberFormatEN& orig) : NumberFormat(orig._format) {
#if DEBUG
    std::cout << "Copy Constructor of NumberFormatDE is working..." << std::endl;
#endif
    num_of_NumberFormatEN_objects_alive++;
}

/**
 * Destructor of NumberFormatEN.
 */
NumberFormatEN::~NumberFormatEN() noexcept {
#if DEBUG
    std::cout << "Destructor of NumberFormatEN is working..." << std::endl;
#endif
    num_of_NumberFormatEN_objects_alive--;
}

/**
 * Converts the rational number into a string (english format).
 * @param x (const Rational&)
 * @return return_string (std::string)
 */
std::string NumberFormatEN::format(const Rational& x) const {
    return NumberFormat::format_help(x, Format::english);
}

/**
 * Parses the rvalue string to a rational number.
 * @param val_string (std::string&&) - rvalue
 * @return r (Rational)
 */
Rational NumberFormatEN::parse(std::string&& val_string) {
    std::string to_parse = val_string;
    return parse(to_parse);
}

/**
 * Parses the lvalue string to a rational number.
 * @param val_string (std::string&) - lvalue
 * @return r (Rational)
 */
Rational NumberFormatEN::parse(std::string& val_string) {
    return NumberFormat::parse_help(val_string, *this);
}
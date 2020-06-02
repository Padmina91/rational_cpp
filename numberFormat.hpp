//
// Created by Mina on 30.05.2020.
//

#ifndef RATIONAL_CPP_NUMBERFORMAT_HPP
#define RATIONAL_CPP_NUMBERFORMAT_HPP

#include <string>
#include "rational.hpp"

class Rational;

class NumberFormat {
public:
    enum class Format;
protected:
    NumberFormat::Format _format;
    
    static bool check_string_correctness(const std::string& str, Format format);
    static void remove_all(std::string& str, char to_remove);
    static void replace_character(std::string& str, char to_remove, std::string&& to_put_instead);
    static void add_thoudands_sep(std::string& str, Format format);
    static void remove_unnecessary_zeros(std::string& str, char decimal_sep);
    static std::string format_help(const Rational& x, Format format);
    static Rational parse_help(std::string& val_string, NumberFormat& nf);
    
public:
    enum class Format {
        german, english
    };
    
    static int num_of_NumberFormat_objects_alive;
    
    NumberFormat(Format format);
    NumberFormat(NumberFormat& orig);
    virtual ~NumberFormat() noexcept;
    
    Format get_format();
    
    virtual std::string format(const Rational& x) const = 0;
    virtual Rational parse(std::string&& val_string) = 0;
    virtual Rational parse(std::string& val_string) = 0;
};


class NumberFormatDE : public NumberFormat {
public:
    static int num_of_NumberFormatDE_objects_alive;
    
    NumberFormatDE();
    NumberFormatDE(NumberFormatDE& orig);
    virtual ~NumberFormatDE() noexcept;
    
    virtual std::string format(const Rational& x) const override;
    virtual Rational parse(std::string&& val_string) override;
    virtual Rational parse(std::string& val_string) override;
};


class NumberFormatEN : public NumberFormat {
public:
    static int num_of_NumberFormatEN_objects_alive;
    
    NumberFormatEN();
    NumberFormatEN(NumberFormatEN& orig);
    virtual ~NumberFormatEN() noexcept;
    
    virtual std::string format(const Rational& x) const override;
    virtual Rational parse(std::string&& val_string) override;
    virtual Rational parse(std::string& val_string) override;
};


#endif //RATIONAL_CPP_NUMBERFORMAT_HPP
//
// Created by Mina on 02.06.2020.
//

#include "testdriver.hpp"
#include "exception.hpp"
#include <iostream>

/**
 * Tests if the double_value method correctly converts a rational number into a double.
 */
void Testdriver::test01() {
    bool test_successful = false;
    Rational r(3, 4);
    double d = r.double_value();
    if (d - 0.0000001 < 0.75 && d + 0.0000001 > 0.75) {
        test_successful = true;
    }
    print_success_message(test_successful, 1);
}

/**
 * Tests if the to_string method of Rational correctly returns an empty string if
 * there's no specified NumberFormat.
 */
void Testdriver::test02() {
    bool test_successful = false;
    Rational r;
    std::string str = r.to_string();
    if (str.empty()) {
        test_successful = true;
    }
    print_success_message(test_successful, 2);
}

/**
 * Tests if the parse methode correctly blocks invalid input.
 * @param nf (NumberFormat&)
 */
void Testdriver::test03(NumberFormat& nf) {
    bool test_successful = false;
    std::string to_parse = "asdf";
    try {
        nf.parse(to_parse);
    } catch (NotANumberException&) {
        test_successful = true;
    }
    print_success_message(test_successful, 3);
}

/**
 * Tests if the parse methode correctly blocks invalid input.
 * @param nf (NumberFormat&)
 */
void Testdriver::test04(NumberFormat& nf) {
    bool test_successful = false;
    std::string to_parse;
    if (nf.get_format() == NumberFormat::Format::english) {
        to_parse = "wef,asf,kwa.*a%&3";
    } else {
        to_parse = "wef.asf.kwa,*a%&3";
    }
    try {
        nf.parse(to_parse);
    } catch (NotANumberException&) {
        test_successful = true;
    }
    print_success_message(test_successful, 4);
}

/**
 * Tests if the parse method accepts numbers without separators.
 * @param nf (NumberFormat&)
 */
void Testdriver::test05(NumberFormat& nf) {
    bool test_successful = true;
    std::string to_parse = "124225544";
    try {
        nf.parse(to_parse);
    } catch (NotANumberException&) {
        test_successful = false;
    }
    print_success_message(test_successful, 5);
}

/**
 * Tests the parse_help method of NumberFormat.
 * @param nf (NumberFormat&)
 */
void Testdriver::test06(NumberFormat& nf) {
    bool test_successful = false;
    std::string to_parse;
    if (nf.get_format() == NumberFormat::Format::english) {
        to_parse = "478,145.25";
    } else {
        to_parse = "478.145,25";
    }
    Rational r = nf.parse(to_parse);
    if (r.double_value() == 478145.25) {
        test_successful = true;
    }
    print_success_message(test_successful, 6);
}

/**
 * Tests if the parsing and formatting works as intended.
 * @param nf (NumberFormat&)
 */
void Testdriver::test07(NumberFormat& nf) {
    bool test_successful = false;
    std::string to_parse;
    if (nf.get_format() == NumberFormat::Format::english) {
        to_parse = "8,145.2";
    } else {
        to_parse = "8.145,2";
    }
    std::string to_parse_copy = std::string(to_parse); // parse() modifies the original string, so a copy is needed
    Rational r = nf.parse(to_parse);
    std::string test_string = r.to_string();
    if (test_string == to_parse_copy) {
        test_successful = true;
    }
    print_success_message(test_successful, 7);
}

/**
 * Tests if zero cropping after the decimal separator works as intended.
 * @param nf (NumberFormat&)
 */
void Testdriver::test08(NumberFormat& nf) {
    bool test_successful = false;
    std::string to_parse;
    if (nf.get_format() == NumberFormat::Format::english) {
        to_parse = "8,145.000";
    } else {
        to_parse = "8.145,000";
    }
    std::string to_compare;
    if (nf.get_format() == NumberFormat::Format::english) {
        to_compare = "8,145";
    } else {
        to_compare = "8.145";
    }
    Rational r = nf.parse(to_parse);
    std::string test_string = r.to_string();
    if (test_string == to_compare) {
        test_successful = true;
    }
    print_success_message(test_successful, 8);
}

/**
 * Prints whether the test was successful or not.
 * @param test_successful (bool)
 * @param test_number (int)
 */
void Testdriver::print_success_message(bool test_successful, int test_number) {
    if (test_successful) {
        std::cout << "Test " << test_number << " successful." << std::endl;
    } else {
        std::cout << "Test " << test_number << " FAILED!!!" << std::endl;
    }
}

/**
 * Executes all tests with german localization.
 */
void Testdriver::execute_tests_DE() {
    NumberFormatDE de;
    test03(de);
    test04(de);
    test05(de);
    test06(de);
    test07(de);
    test08(de);
}

/**
 * Executes all tests with english localization.
 */
void Testdriver::execute_tests_EN() {
    NumberFormatEN en;
    test03(en);
    test04(en);
    test05(en);
    test06(en);
    test07(en);
    test08(en);
}

/**
 * Executes all tests.
 */
void Testdriver::execute_tests() {
    test01();
    test02();
    std::cout << std::endl;
    
    execute_tests_DE();
    std::cout << std::endl;
    
    execute_tests_EN();
}
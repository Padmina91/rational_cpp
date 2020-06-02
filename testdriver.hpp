//
// Created by Mina on 02.06.2020.
//

#ifndef RATIONAL_CPP_TESTDRIVER_HPP
#define RATIONAL_CPP_TESTDRIVER_HPP

#include "numberFormat.hpp"

class Testdriver {
protected:
    static void test01();
    static void test02();
    static void test03(NumberFormat& nf);
    static void test04(NumberFormat& nf);
    static void test05(NumberFormat& nf);
    static void test06(NumberFormat& nf);
    static void test07(NumberFormat& nf);
    static void test08(NumberFormat& nf);
    
    static void execute_tests_DE();
    static void execute_tests_EN();
    static void print_success_message(bool test_successful, int test_number);
    
public:
    static void execute_tests();
};


#endif //RATIONAL_CPP_TESTDRIVER_HPP
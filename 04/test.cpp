#include "bigint.h"

#define FAIL(test, result, right_result) std::cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl; 
#define OK(test, result, right_result) std::cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl;

void operator_eq_test() {
    Big_int a("-987654321098765432109876543210");
    Big_int b("-987654321098765432109876543210");

    if (b==a)
        OK("operator_eq", "true", "true")
    else
        FAIL("operator_eq", "false", "true")
}

void operator_not_eq_test() {
    Big_int a("987654321098765432109876543210");
    Big_int b("987654321098765432109876543211");

    if (b!=a)
        OK("operator_not_eq", "true", "true")
    else
        FAIL("operator_not_eq", "false", "true")
}

void operator_less_test() {
    Big_int a("12345678901234567890");
    Big_int b("-12345678901234567891");

    if (b<a)
        OK("operator_less", "true", "true")
    else
        FAIL("operator_less", "false", "true")
}

void operator_more_test() {
    Big_int a("-12345678901234567892");
    Big_int b("-12345678901234567891");

    if (b>a)
        OK("operator_more", "true", "true")
    else
        FAIL("operator_more", "false", "true")
}

void assignment_test() {
    Big_int a("12345678901234567890");
    Big_int b("987654321098765432109876543210");
    a = -b;

    if (a==Big_int("-987654321098765432109876543210"))
        OK("assignment", a, "-987654321098765432109876543210")
    else
        FAIL("assignment", a, "-987654321098765432109876543210")
}

void operator_unary_minus_test() {
    Big_int  a("-9111223987222222222222");
   
    if ((-a)==Big_int("9111223987222222222222"))
        OK("unary_minus", -a, "9111223987222222222222")
    else
        FAIL("unary_minus", -a, "9111223987222222222222")
}

void operator_plus_test() {
    Big_int  a("91111111111111222222222222222");
    Big_int b("666666666666666333333333333333");
    Big_int c = a + b;

    if (c==Big_int("757777777777777555555555555555"))
        OK("plus", c, "757777777777777555555555555555")
    else
        FAIL("plus", c, "757777777777777555555555555555")
}

void operator_minus_test() {
    Big_int  a("-91111111111111222222222222222");
    Big_int b("-666666666666666333333333333333");
    Big_int c = a - b;
   
    if (c==Big_int("575555555555555111111111111111"))
        OK("minus", c, "575555555555555111111111111111")
    else
        FAIL("minus", c, "575555555555555111111111111111")
}

void operator_mul_test() {
    Big_int a("111111111111111");
    Big_int b("-111111111111111");
    Big_int c = a * b;

    if (c==Big_int("-12345679012345654320987654321"))
        OK("multiply", c, "-12345679012345654320987654321")
    else
        FAIL("multiply", c, "-12345679012345654320987654321")
}

void new_1_test() {
    Big_int a("99999999999999999999999");
    Big_int b("99999999999999999999999");
    std::cout << a * b << std::endl; 
    Big_int c = a * b;

    if (c==Big_int("9999999999999999999999800000000000000000000001"))
        OK("new_test_1", c, "9999999999999999999999800000000000000000000001")
    else
        FAIL("new_test_1", c, "9999999999999999999999800000000000000000000001")
}



void new_2_test() {
    Big_int a("99999999999999999999999");
    Big_int b("0");
    std::cout << b - a << std::endl; 
    Big_int c = b - a;

    if (c==Big_int("-99999999999999999999999"))
        OK("new_test_2", c, "-99999999999999999999999")
    else
        FAIL("new_test_2", c, "-99999999999999999999999")
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() {
    operator_eq_test();
    operator_not_eq_test();
    operator_less_test();
    operator_more_test();
    assignment_test();
    operator_unary_minus_test();
    operator_plus_test();
    operator_minus_test();
    operator_mul_test();

    new_1_test();
    new_2_test();
}
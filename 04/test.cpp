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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() {
    operator_eq_test();
    operator_not_eq_test();
    operator_less_test();
    operator_more_test();
    assignment_test();
}
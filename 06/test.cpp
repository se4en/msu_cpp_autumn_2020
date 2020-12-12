#include "format.h"

#define FAIL(test, result, right_result) std::cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl; 
#define OK(test, result, right_result) std::cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl;

void base_work_test() {
    std::string text = format("{1} + {1} = {0}", 2, "one");
    
    if (text=="one + one = 2") 
        OK("base_work", text, "one + one = 2")
    else
        FAIL("base_work", text, "one + one = 2")
}

void few_parameters_test() {

    if (text=="one + one = 2") 
        OK("base_work", text, "one + one = 2")
    else
        FAIL("base_work", text, "one + one = 2")
}

void many_parameters_test() {

    if (text=="one + one = 2") 
        OK("base_work", text, "one + one = 2")
    else
        FAIL("base_work", text, "one + one = 2")
}

void wrong_index_test() {
    std::string text = format("{1} + {1} = {0}", 2, "one");
    
    if (text=="one + one = 2") 
        OK("base_work", text, "one + one = 2")
    else
        FAIL("base_work", text, "one + one = 2")
}

int main() {
    base_work_test();
}
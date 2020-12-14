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
    try {
        std::string text = format("{2} + {1} + {0} = 8 ", 4, "four");
    }
    catch(Bad_index& err) {
        OK("few_parametrs", "worng index", err.what())
        return;
    }
    catch(...) {
        FAIL("few_parametrs", "worng index", "{another exception}")
        return;
    }
    FAIL("few_parametrs", "worng index", "{no exception}")
}

void many_parameters_test() {
    try {
        std::string text = format("{1} + {0} = 8 ", 4, "four", 8);
    }
    catch(Bad_index& err) {
        OK("many_parametrs", "too much parameters", err.what())
        return;
    }
    catch(...) {
        FAIL("many_parametrs", "too much parameters", "{another exception}")
        return;
    }
    FAIL("many_parametrs", "too much parameters", "{no exception}")
}

void no_open_bracket_test() {
    try {
        std::string text = format("{0} + {1} + 0} = 8 ", 4, "four");
    }
    catch(Bad_bracket& err) {
        OK("no open bracket", "expected '}', find not '}'", err.what())
        return;
    }
    catch(...) {
        FAIL("no open bracket", "expected '}', find not '}'", "{another exception}")
        return;
    }
    FAIL("no open bracket", "expected '}', find not '}'", "{no exception}")
}

void no_close_bracket_test() {
    try {
        std::string text = format("{0} + {1 + {0} = 8 ", 4, "four");
    }
    catch(Bad_bracket& err) {
        OK("no close bracket", "find '}', expected not '}'", err.what())
        return;
    }
    catch(...) {
        FAIL("no close bracket", "find '}', expected not '}'", "{another exception}")
        return;
    }
    FAIL("no close bracket", "find '}', expected not '}'", "{no exception}")
}

void wrong_index_test() {
    try {
        std::string text = format("{0} + {1} + {-1} = 8 ", 4, "four", 6);
    }
    catch(Bad_bracket& err) {
        OK("wrong index", "find '}', expected not '}'", err.what())
        return;
    }
    catch(...) {
        FAIL("wrong index", "find '}', expected not '}'", "{another exception}")
        return;
    }
    FAIL("wrong index", "find '}', expected not '}'", "{no exception}")
}

int main() {
    base_work_test();
    few_parameters_test();
    many_parameters_test();
    no_open_bracket_test();
    wrong_index_test();
}
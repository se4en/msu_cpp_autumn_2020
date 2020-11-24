#include "format.h"

using namespace std;

#define FAIL(test, result, right_result) cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << endl; 
#define OK(test, result, right_result) cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << endl;

void base_work_test() {
    std::string text = format("{1} + {1} = {0}", 2, "one");
    if (text=="one + one = 2") 
        OK("base_work", text, "one + one = 2")
    else
        FAIL("base_work", text, "one + one = 2")
}

int main() {
    /*try {
        std::string text = format(input, 2, "one");
        std::cout << text << std::endl;
    }
    catch(BadIndex& ex) {
        std::cout << "BadIndex:\n" << ex.what() << std::endl;
    }
    catch(BadBracket& ex) {
        std::cout << "BadBracket:\n" << ex.what() << std::endl;
    }*/
    base_work_test();
}
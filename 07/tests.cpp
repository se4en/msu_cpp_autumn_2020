#include "vector.h"
#include <iostream>

#define FAIL(test, result, right_result) cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << endl; 
#define OK(test, result, right_result) cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << endl;

void base_work_test() {
    vector<int> int_vec;
    int_vec.push_back(4);
    int_vec.push_back(3);
    int_vec.push_back(2);
    std::cout << int_vec[0] << int_vec[1] << int_vec[2] << int_vec.size() << std::endl;
}

int main() {
    vector<int> int_vec();
    base_work_test();
    return 0;
}
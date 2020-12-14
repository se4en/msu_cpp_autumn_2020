#include "vector.h"
#include <iostream>

#define FAIL(test, result, right_result) std::cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl; 
#define OK(test, result, right_result) std::cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl;

// push_pack and emplace_back test start

class Test_class {
    int v_;
public:
    Test_class() : v_(0) {};
    Test_class(int value) : v_(value) { };
    Test_class(const Test_class& other) { v_ = other.v_ + 1; };
    Test_class(Test_class&& other) { v_ = std::move(other.v_); v_ *= 2;}
    int get() { return v_; }
    ~Test_class() {}
};

void emplace_back_test() {
    vector<Test_class> test_vec;
    test_vec.emplace_back(Test_class(3));
    std::cout << test_vec.size() << " " << test_vec[0].get() << std::endl;
    test_vec.push_back(Test_class(3));
    std::cout << test_vec.size() << " " << test_vec[1].get() << std::endl;
    
    if (test_vec[0].get()==3)
        OK("emplace_back", test_vec[0].get(), 3)
    else
        FAIL("emplace_back", test_vec[0].get(), 3)
    if (test_vec[1].get()==4)
        OK("push_back", test_vec[1].get(), 4)
    else
        FAIL("push_back", test_vec[1].get(), 4)
}

// test end

void operator_test() {
    vector<int> int_vec;
    int_vec.push_back(4);
    int_vec.push_back(3);
    int_vec.push_back(2);
    const char* result = "432";

    if (int_vec[0]==4 && int_vec[1]==3 && int_vec[2]==2)
        OK("operator[]", result, int_vec[0] << int_vec[1] << int_vec[2])
    else
        FAIL("operator[]", result, int_vec[0] << int_vec[1] << int_vec[2])
}

void size_pop_test() {
    vector<char> char_vec;
    char_vec.push_back('a');
    char_vec.push_back('b');
    char_vec.push_back('c');
    int size_1 = char_vec.size();
    char_vec.pop_back();
    int size_2 = char_vec.size();

    if (size_1==3 && size_2==2)
        OK("size", "32", size_1 << size_2)
    else
        FAIL("size", "32", size_1 << size_2)
    if (char_vec[0]=='a' && char_vec[1]=='b')
        OK("pop_back", "'c'", "'c'")
    else
        FAIL("pop_back", "'c'", "not 'c'")
}

void empty_test() {
    vector<int> int_vec;

    if (int_vec.empty())
        OK("empty", "true", "true")
    else
        OK("empty", "true", "false")
}

void clear_test() {
    vector<char> char_vec;
    char_vec.push_back('a');
    char_vec.push_back('b');
    char_vec.push_back('c');
    char_vec.clear();

    if (char_vec.size()==0)
        OK("clear", "clean", "clean")
    else
        FAIL("clear", "clean", "not clean")
}

void begin_rbegin_test() {
    vector<char> char_vec;
    char_vec.push_back('a');
    char_vec.push_back('b');
    iterator<char> it = char_vec.begin(); ++it;
    reverse_iterator<char> itr = char_vec.rbegin(); ++itr;
    
    if ((*it)=='b')
        OK("begin", "'b'", (*it))
    else
        FAIL("begin", "'b'", (*it))
    if ((*itr)=='a')
        OK("rbegin", "'a'", (*it))
    else
        FAIL("rbegin", "'a'", (*it))

}

void end_rend_test() {
    
}

void reserve_capacity_test() {

}
    
void resize_test() {

}

int main() {
    emplace_back_test();
    operator_test();
    size_pop_test();
    empty_test();
    clear_test();
    begin_rbegin_test();
    end_rend_test();
    reserve_capacity_test();
    resize_test();
}
#include "vector.h"
#include <iostream>

#define FAIL(test, result, right_result) std::cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl; 
#define OK(test, result, right_result) std::cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl;

struct Test_int {
    int a, b, c;
    Test_int() {}
    Test_int(int a,int b,int c) : a(a), b(b), c(c) {}
    bool operator==(const Test_int& other) const {
        return (a==other.a) && (b==other.b) && (c==other.c);
    }
    friend std::ostream& operator<<(std::ostream& os, const Test_int& obj);
};

std::ostream& operator<<(std::ostream& os, const Test_int& obj) {
    os << obj.a << obj.b << obj.c;
    return os;
}

void emplace_back_test() {
    vector<Test_int> test_vec;
    test_vec.emplace_back(1, 2, 3);

    if (test_vec[0]==Test_int(1, 2, 3))
        OK("emplace_back", test_vec[0], "123")
    else
        FAIL("emplace_back", test_vec[0], "123")
}

void push_back_test() {
    vector<int> int_vec;
    int_vec.push_back(4);
    int_vec.push_back(3);
    int_vec.push_back(2);

    if (int_vec[0]==4 && int_vec[1]==3 && int_vec[2]==2)
        OK("push back", int_vec[0] << int_vec[1] << int_vec[2], "432")
    else
        FAIL("push back", int_vec[0] << int_vec[1] << int_vec[2], "432")
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
        OK("size", size_1 << size_2, "32")
    else
        FAIL("size", size_1 << size_2, "32")
    if (char_vec[0]=='a' && char_vec[1]=='b')
        OK("pop_back", "'c'", "'c'")
    else
        FAIL("pop_back", "not 'c'", "'c'")
}

void empty_test() {
    vector<int> int_vec;

    if (int_vec.empty())
        OK("empty", "true", "true")
    else
        OK("empty", "false", "true")
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
        FAIL("clear", "not clean", "clean")
}

void begin_rbegin_test() {
    vector<char> char_vec;
    char_vec.push_back('a');
    char_vec.push_back('b');
    iterator<char> it = char_vec.begin(); ++it;
    reverse_iterator<char> itr = char_vec.rbegin(); ++itr;
    
    if ((*it)=='b')
        OK("begin", (*it), "b")
    else
        FAIL("begin", (*it), "b")
    if ((*itr)=='a')
        OK("rbegin", (*itr), "a")
    else
        FAIL("rbegin", (*itr), "a")
}

void end_rend_test() {
    vector<char> char_vec;
    char_vec.push_back('a');
    char_vec.push_back('b');
    iterator<char> it = char_vec.end(); --it;
    reverse_iterator<char> itr = char_vec.rend(); --itr;
    
    if ((*it)=='b')
        OK("end", (*it), "b")
    else
        FAIL("end", (*it), "b")
    if ((*itr)=='a')
        OK("rend", (*itr), "a")
    else
        FAIL("rend", (*itr), "a")
}

void reserve_capacity_test() {
    vector<char> char_vec;
    char_vec.push_back('a');
    char_vec.push_back('b');
    char_vec.reserve(10);
    uint32_t cap = char_vec.capacity();

    if (cap==10)
        OK("reserve", cap, 10)
    else
        FAIL("reserve", cap, 10)
}
    
void resize_test() {
    vector<char> char_vec;
    char_vec.push_back('a');
    char_vec.push_back('b');
    uint32_t size_1 = char_vec.size();
    char_vec.resize(4);
    uint32_t size_2 = char_vec.size();

    if (size_1==2 && size_2==4)
        OK("size", size_1 << size_2, "24")
    else
        FAIL("size", size_1 << size_2, "24")
}

int main() {
    emplace_back_test();
    push_back_test();
    size_pop_test();
    empty_test();
    clear_test();
    begin_rbegin_test();
    end_rend_test();
    reserve_capacity_test();
    resize_test();
}
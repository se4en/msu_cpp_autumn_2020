#include "matrix.h"
#include <exception>
#include <string>

using namespace std;

#define FAIL(test, result, right_result) cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << endl; 
#define OK(test, result, right_result) cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << endl;

void rows_columns_test() {
    Matrix mt(13, 15);    
    if (mt.get_rows()==13) 
        OK("rows_getter", mt.get_rows(), 13)
    else
        FAIL("rows_getter", mt.get_rows(), 13)
    if (mt.get_columns()==15) 
        OK("columns_getter", mt.get_columns(), 15)
    else
        FAIL("columns_getter",  mt.get_columns(), 15)
}

void null_rows_test() {
    bool ok = false;
    try {
        Matrix mt(0, -1);
    }
    catch(invalid_argument& ex) {
        OK("wrong_shape", ex.what(), "invalid_argument");
        ok = true;
    }
    catch(exception& ex) {
        FAIL("wrong_shape", ex.what(), "invalid_argument");
    }
    if (!ok) 
        FAIL("wrong_shape", "none", "invalid argument")
}

void get_real_elem_test() {
    Matrix mt(2, 2);
    mt[1][0] = 3;
    if (mt[1][0]==3) 
        OK("get_real_elem", mt[1][0], 3)
    else
        FAIL("get_real_elem", mt[1][0], 3)
}

void get_fake_elem_test() {
    Matrix mt(2, 2);
    bool ok = false;
    try {
        mt[2][0];
    }
    catch(out_of_range& ex) {
        OK("wrong_row", ex.what(), "out_of_range");
        ok = true;
    }
    catch(exception& ex) {
        FAIL("wrong_row", ex.what(), "out_of_range");
    }
    if (!ok) 
        FAIL("wrong_row", "none", "out_of_range");
    ok = false;
    try {
        mt[1][2];
    }
    catch(out_of_range& ex) {
        OK("wrong_column", ex.what(), "out_of_range");
        ok = true;
    }
    catch(exception& ex) {
        FAIL("wrong_column", ex.what(), "out_of_range");
    }
    if (!ok) 
        FAIL("wrong_column", "none", "out_of_range");
}

void mul_test() {
    Matrix mt(2, 2);
    mt[0][0] = 1;
    mt[0][1] = 2;
    mt[1][0] = 3;
    mt[1][1] = 4;
    mt *= 2;
    if (mt[0][0]==2 && mt[0][1]==4 && mt[1][0]==6 && mt[1][1]==8) 
        OK("multiplication", "2468", "2468")
    else
        FAIL("multiplication", to_string(mt[0][0]) + to_string(mt[0][1]) +
            to_string(mt[1][0]) + to_string(mt[1][1]), "2468")
}

void right_sum_test() {
    Matrix mt1(2, 2);
    mt1[0][0] = 1;
    mt1[0][1] = 2;
    mt1[1][0] = 3;
    mt1[1][1] = 4;
    Matrix mt2(2, 2);
    mt2[0][0] = 4;
    mt2[0][1] = 3;
    mt2[1][0] = 2;
    mt2[1][1] = 1;  
    Matrix mt3(2, 2);
    mt3 = mt1 + mt2;  
    if (mt3[0][0]==5 && mt3[0][1]==5 && mt3[1][0]==5 && mt3[1][1]==5) 
        OK("multiplication", "5555", "5555")
    else
        FAIL("multiplication", to_string(mt3[0][0]) + to_string(mt3[0][1]) +
            to_string(mt3[1][0]) + to_string(mt3[1][1]), "5555")
}

void wrong_sum_test() {
    Matrix mt1(2, 1);
    Matrix mt2(1, 2);
    bool ok = false;
    try {
        mt1 + mt2;
    }
    catch(invalid_argument& ex) {
        OK("wrong_add", ex.what(), "invalid_argument");
        ok = true;
    }
    catch(exception& ex) {
        FAIL("wrong_add", ex.what(), "invalid_argument");
    }
    if (!ok) 
        FAIL("wrong_add", "none", "invalid_argument");
}

void true_compare_test() {
    Matrix mt1(2, 2);
    mt1[0][0] = 1;
    mt1[0][1] = 2;
    mt1[1][0] = 3;
    mt1[1][1] = 4;
    Matrix mt2(2, 2);
    mt2[0][0] = 1;
    mt2[0][1] = 2;
    mt2[1][0] = 3;
    mt2[1][1] = 4;      
    if (mt1==mt2) 
        OK("true_comparation", "true", "true")
    else
        FAIL("true_comparation", "false", "true")
}

void false_compare_test() {
    Matrix mt1(2, 2);
    mt1[0][0] = 1;
    mt1[0][1] = 2;
    mt1[1][0] = 3;
    mt1[1][1] = 4;
    Matrix mt2(2, 2);
    mt2[0][0] = 1;
    mt2[0][1] = 2;
    mt2[1][0] = 3;
    mt2[1][1] = 5;      
    if (mt1!=mt2) 
        OK("false_comparation", "false", "false")
    else
        FAIL("false_comparation", "true", "false")
    Matrix mt3(2, 1);
    mt3[0][0] = 1;
    mt3[0][0] = 3;
    if (mt1!=mt3) 
        OK("false_comparation", "false", "false")
    else
        FAIL("false_comparation", "true", "false")
}

int main() {
    rows_columns_test();
    null_rows_test();
    get_real_elem_test();
    get_fake_elem_test();
    mul_test();
    right_sum_test();
    wrong_sum_test();
    true_compare_test();
    false_compare_test();
}
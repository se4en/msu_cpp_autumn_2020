#include "parser.h"

#define FAIL(test, result, right_result) std::cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl; 
#define OK(test, result, right_result) std::cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl;

static int dig_counter = 0;

void my_dig_call(const std::string& token) {
    dig_counter += std::stoi(token);
}

void digit_callback_test() {
    Parser parser;
    std::string text("123 abc 4/5 -4 12 ab");
    parser.set_digit_token_callback(my_dig_call);
    parser.parse(text);

    if (dig_counter==135)
        OK("digit_callback", dig_counter, "135")
    else
        FAIL("digit_callback", dig_counter, "135")
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

static std::string word_sum = "";

void my_word_call(const std::string& token) {
    word_sum += token;
}

void word_callback_test() {
    Parser parser;
    std::string text("123 ab0c 4/5 d-4 12");
    parser.set_word_token_callback(my_word_call);
    parser.parse(text);

    if (word_sum=="ab0c4/5d-4")
        OK("word_callback", word_sum, "ab0c4/5d-4")
    else
        FAIL("word_callback", word_sum, "ab0c4/5d-4")
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

static int start_counter = 0;

void my_start_call() {
    start_counter += 5;
}

void st_dig_call(const std::string& token) {
    if (start_counter!=5) 
        start_counter += 100;
}

void st_end_call() {
    if (start_counter!=5) 
        start_counter += 10;
}

void start_callback_test() {
    Parser parser;
    std::string text("123 3 12 90");
    parser.set_start_callback(my_start_call);
    parser.set_digit_token_callback(st_dig_call);
    parser.set_end_callback(st_end_call);
    parser.parse(text);

    if (start_counter==5)
        OK("start_callback", start_counter, "5")
    else
        FAIL("start_callback", start_counter, "5")
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

static int end_counter = 0;

void nd_start_call() {
    if (end_counter!=0) 
        end_counter += 10;
}

void nd_dig_call(const std::string& token) {
    if (end_counter!=0) 
        end_counter += 100;
}

void my_end_call() {
    end_counter += 5;
}

void end_callback_test() {
    Parser parser;
    std::string text("123 3 12 90");
    parser.set_start_callback(nd_start_call);
    parser.set_digit_token_callback(nd_dig_call);
    parser.set_end_callback(my_end_call);
    parser.parse(text);

    if (end_counter==5)
        OK("end_callback", end_counter, "05")
    else
        FAIL("end_callback", end_counter, "05")
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

static int db_counter = 0;

void db_dig_call(const std::string& token) {
    db_counter += std::stoi(token);
}

void double_parse_test() {
    Parser parser;
    std::string text_1("10 abc -4 12ab");
    std::string text_2("bc 4- .3 5 12ab");
    parser.set_digit_token_callback(db_dig_call);
    parser.parse(text_1);
    parser.parse(text_2);

    if (db_counter==15)
        OK("double_parse", db_counter, 15)
    else
        FAIL("double_parse", db_counter, 15)
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() {
    digit_callback_test();
    word_callback_test();
    start_callback_test();
    end_callback_test();
    double_parse_test();
}
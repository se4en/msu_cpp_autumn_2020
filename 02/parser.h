#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <cctype>
#include <functional>

typedef std::function<void(const std::string &)> token_callback_func_ptr;
typedef std::function<void()> callback_func_ptr;

class Parser {
    uint64_t cur_pos, text_lenght;
    callback_func_ptr start_callback,
                            end_callback;
    token_callback_func_ptr digit_token_callback,
                            word_token_callback;

    void base_start_callback(const std::string &);
    void base_digit_token_callback(const std::string &);
    void base_word_token_callback(const std::string &);
    void base_end_callback(const std::string &);

    std::string read_next_token(const std::string &text);
    bool isdigit(std::string token);
public: 
    Parser();
    void parse(const std::string &text);

    void set_start_callback(callback_func_ptr new_callback);
    void set_digit_token_callback(token_callback_func_ptr new_callback);
    void set_word_token_callback(token_callback_func_ptr new_callback);
    void set_end_callback(callback_func_ptr new_callback);
};

#endif
#include "parser.h"

std::string Parser::read_next_token(const std::string &text) {
    int i = 0;
    // skip spaces
    for (; isspace(text[this->cur_pos + i]) & (this->cur_pos + i < this->text_lenght); i++) {}
    // read new token
    for (; !isspace(text[this->cur_pos + i]) & (this->cur_pos + i < this->text_lenght); i++) {}
    std::string result = text.substr(this->cur_pos, i);
    // step
    this->cur_pos += (i+1);
    return result;      
}

bool Parser::isdigit(std::string token) {
    for (uint64_t i=0; i<token.length(); i++)
        if (token[i] < '0' || token[i] > '9')
            return false;
    return true;
}

Parser::Parser() : cur_pos(0), text_lenght(0) {
    start_callback = [] {};
    end_callback = [] {};     
    digit_token_callback = [](const std::string&) {};
    word_token_callback = [](const std::string&) {};  
}

void Parser::parse(const std::string &text) {
    text_lenght = text.length();
    start_callback();
    while (cur_pos < text_lenght) {
        std::string token = read_next_token(text);
        isdigit(token) ? digit_token_callback(token) : word_token_callback(token);
    }
    end_callback();
    cur_pos = 0;
    text_lenght = 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Parser::set_start_callback(callback_func_ptr new_callback) {
    start_callback = new_callback;
}

void Parser::set_digit_token_callback(token_callback_func_ptr new_callback) {
    digit_token_callback = new_callback;
}

void Parser::set_word_token_callback(token_callback_func_ptr new_callback) {
    word_token_callback = new_callback;
}

void Parser::set_end_callback(callback_func_ptr new_callback) {
    end_callback = new_callback;
}

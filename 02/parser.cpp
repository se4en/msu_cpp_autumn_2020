#include "parser.h"

//typedef std::function<void(const std::string &)> callback_func_ptr;
//void base_start_callback(const std::string &) {}
//callback_func_ptr start_callback = base_start_callback;

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
        for (int i=0; i<token.length(); i++)
            if (token[i] < '0' || token[i] > '9')
                return false;
        return true;
    }

Parser::Parser() : 
        cur_pos(0), text_lenght(0),
        start_callback(nullptr),
        digit_token_callback(nullptr),
        word_token_callback(nullptr),
        end_callback(nullptr) {
            start_callback = base_start_callback;
        }

void Parser::parse(const std::string &text) {
    text_lenght = text.length();
    start_callback();
    while (cur_pos < text_lenght) {
        std::string token = read_next_token(text);
        //isdigit(token) ? digit_token_callback(token) : word_token_callback(token);
    }
    //end_callback();
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

int main() {
    Parser parser;
    std::string text("123 abc -4 12ab");
    parser.parse(text);
}
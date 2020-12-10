#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>
#include <string>
#include <sstream>

class Bad_index : public std::exception {
    std::string description_;
    const char* file_name_;
    int line_;
public:
    Bad_index(const std::string& desc, const char* file_name, int line) :
        description_(desc), file_name_(file_name), line_(line) {};
    const char* what();
};

class Bad_bracket : public std::exception {
    std::string description_;
    const char* file_name_;
    int line_;
    char bracket_;
public:
    Bad_bracket(const std::string& desc, const char* file_name, int line, char bracket) :
        description_(desc), file_name_(file_name), line_(line), bracket_(bracket) {};
    const char* what();
};

//========================================================================-------------------------------------------------------------------------------------------------------------------------

uint8_t get_index(std::string& text, std::string::const_iterator& it) {
    uint8_t result = 0;
    // if no digit in {}
    if (it!=text.end() && *it=='}')
        throw Bad_index("in get_index()", __FILE__, __LINE__);
    // read index betwean {}
    while (it!=text.end() && (*it>='0' && *it<='9'))
        result = 10*result + (*it - '0');
    // if didnt met }
    if (it!=text.end() || *it!='}')
        throw Bad_bracket("in get_index()", __FILE__, __LINE__, '{');
    return result;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename First>
std::stringstream get_argument(const uint8_t ind, const First& first) {
    std::stringstream result;
    result << first;
    return result;  
}

template <typename First, typename... Rest>
std::stringstream get_argument(const uint8_t ind, const First& first, const Rest&... rest) {
    if (ind==0) {
        std::stringstream result;
        result << first;
        return result;
    }
    else
        return get_argument(ind-1, rest...); 
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename... Args>
std::string format(const std::string text, const Args&... args) {
    std::string result;
    uint8_t cur_arg_index = 0;
    uint8_t num_args = sizeof...(Args);
    std::string::const_iterator it = text.begin();
    while (it!=text.end()) {
        if (*it!='{') {
            if (*it=='}')
                throw BadBracket("in format()", __FILE__, __LINE__, '}');
            result += *it;
            ++it;
        }
        else { 
            ++it;
            cur_arg_index = 0;
            if (it!=text.end() && *it=='}')
                throw BadIndex("in format()", __FILE__, __LINE__);
            // read index betwean {}
            for (;it!=text.end() && (*it>='0' && *it<='9'); ++it)
                cur_arg_index = 10*cur_arg_index + (*it - '0');
            // if didnt met }
            if (it==text.end() || *it!='}')
                throw BadBracket("in format()", __FILE__, __LINE__, '{');
            if (cur_arg_index>=num_args)
                throw BadIndex("in format()", __FILE__, __LINE__);
            // write argument
            std::stringstream str_out = get_argument(cur_arg_index ,args...);
            result += str_out.str();      
            ++it;
        }
    }
    return result;
}

#endif
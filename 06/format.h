#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>
#include <string>
#include <sstream>

class My_exception {
    std::string description_;
    int position_;
public:
    My_exception(const std::string& desc, int position) :
        description_(desc), position_(position) {};
    std::string what();
};

std::string My_exception::what() {
    return description_ + " at " + std::to_string(position_) + " element.";
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Bad_index : public My_exception {
public:
    Bad_index(const std::string& desc, int position) :
        My_exception(desc, position) {};
};

class Bad_bracket : public My_exception {
public:
    Bad_bracket(const std::string& desc, int position) :
        My_exception(desc, position) {};
};

//==================================================================================================================================================================================================

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
    uint8_t used_params = 0; // store last serial number of used parameters
    std::string::const_iterator it = text.begin();
    while (it!=text.end()) {
        if (*it!='{') {
            if (*it=='}')
                throw Bad_bracket("find '}', expected not '}'", it - text.begin());
            result += *it;
            ++it;
        } 
        // if met '{' 
        else { 
            ++it;
            cur_arg_index = 0;
            // if no index between '{' and '}'
            if (it!=text.end() && *it=='}')
                throw Bad_index("expected '}', find not '}'", it - text.begin());
            // read index between {}
            for (;it!=text.end() && (*it>='0' && *it<='9'); ++it)
                cur_arg_index = 10*cur_arg_index + (*it - '0');
            // if didnt met }
            if (it==text.end() || *it!='}')
                throw Bad_bracket("expected '}', find not '}'", it - text.begin());
            if (cur_arg_index>=num_args)
                throw Bad_index("wrong index", it - text.begin());
            // write argument
            std::stringstream str_out = get_argument(cur_arg_index ,args...);
            if (cur_arg_index==used_params+1)
                ++used_params;
            result += str_out.str();      
            ++it;
        }
    }
    if (used_params!=num_args-1)
        throw Bad_index("too much parameters", it - text.begin());
    return result;
}

#endif
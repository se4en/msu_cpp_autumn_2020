#include "format.h"

const char* Bad_index::what() {
    return (description_ + "\nin file " + file_name_ + " in line " + line_).c_str() ;
}

const char* Bad_bracket::what() {
    return description_.c_str();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*                     it doesnt work

uint8_t get_index(std::string& text, std::string::const_iterator& it) {
    uint8_t result = 0;
    // if no digit in {}
    if (it!=text.end() && *it=='}')
        throw BadIndex("in get_index()", __FILE__, __LINE__);
    // read index betwean {}
    while (it!=text.end() && (*it>='0' && *it<='9'))
        result = 10*result + (*it - '0');
    // if didnt met }
    if (it!=text.end() || *it!='}')
        throw BadBracket("in get_index()", __FILE__, __LINE__);
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
                throw BadBracket("in format()", __FILE__, __LINE__);
            if (cur_arg_index>=num_args)
                throw BadIndex("in format()", __FILE__, __LINE__);
            // write argument
            std::stringstream str_out = get_argument(cur_arg_index ,args...);
            result += str_out.str();      
            ++it;
        }
    }
    return result;
}*/
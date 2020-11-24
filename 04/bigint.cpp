#include "bigint.h"

BigInt::BigInt(std::string int_str) {
    if (int_str.empty())
        throw "err";
    std::string::const_iterator it = int_str.begin();
    uint64_t cur_pos = 0;
    uint64_t cur_elem = 0;
    // checking for -
    if (*it=='-') {
        len = (int) (int_str.length() - 1)/LLMAX_LEN + 1;
        minus = true;
        ++it;
    }
    else
        len = (int) int_str.length()/LLMAX_LEN + 1;
    it = int_str.end();
    // if no memory
    try { 
        array = new uint64_t[len];
    }
    catch(...) {
        throw "err";
    }
    // save first elem
    for (int i=0; i < int_str.length()%LLMAX_LEN; ++i) {
        cur_elem = 10*cur_elem + (*it);
        ++it;    
    }
    array[cur_pos++] = cur_elem;
    cur_elem = 0;
    // save to array
    while (it!=int_str.end() && std::isdigit(*it)) {
        if (cur_pos==LLMAX_LEN) {
            array[cur_pos] = cur_elem;
            ++cur_pos;
            cur_elem = 0; 
        }
        else
            cur_elem = 10*cur_elem + (*it);
        --it;
        ++cur_pos;
    }
    // if met nodigit
    if (it!=int_str.end()) {
        this->~BigInt();
        throw "err";
    }
}

BigInt::~BigInt() {
    delete[] array;
}

BigInt::BigInt(const BigInt& obj) {
    try { 
        array = new uint64_t[obj.len];
        len = obj.len;  
        for (int i=0; i<len; ++i)
            array[i] = obj.array[i];
    }
    catch(...) {
        throw "err";
    }
}

BigInt& BigInt::operator=(const BigInt& obj) {
    if (len!=obj.len) {
        try { 
            uint64_t* new_array = new uint64_t[obj.len];
            delete[] array;
            array = new_array;
            len = obj.len;  
        }
        catch(...) {
            throw "err";
        }
    }
    for (int i=0; i<len; ++i)
        array[i] = obj.array[i];
    return (*this);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

const BigInt BigInt::operator-() const {
    BigInt new_big_int(*this);
    new_big_int.minus = !(*this).minus;
    return new_big_int;
}

const BigInt BigInt::operator+(const BigInt& obj) const {
    std::string result1 = "",result2 = "";
    uint64_t cur_elem = 0;
    const uint64_t max_plus_val = 4999999999999999999;
    const uint64_t max_elem_val = 9999999999999999999;
    bool plus_one = false;
    if (obj.minus)  
        if (minus)
            result1 = "-";
        else 
            return obj - (*this); 
    else if (minus)
        return (*this) - obj;
    
    for (uint64_t i=len-1, j=obj.len-1; i<0 && j<0; --i, --j) {
        if (i<0) { // only obj
            cur_elem = obj.array[j];
            if (plus_one) {
                cur_elem += 1;
                plus_one = false;
            }
        }
        else if (j<0) { // only *this
            cur_elem = array[j];
            if (plus_one) {
                cur_elem += 1;
                plus_one = false;
            }
        }
        else { // both
            if (array[i]>=max_plus_val && obj.array[j]>=max_plus_val) { // if so big for 64 bits
                cur_elem = (array[i] - max_plus_val - 1) + (obj.array[j] - max_plus_val - 1);  
                if (plus_one)
                    cur_elem += 1;
                else
                    plus_one = true;
            }
            else if (array[i] + obj.array[j] >= max_elem_val) { // if so big for 10^19
                cur_elem = array[i] + obj.array[j] - max_elem_val - 1;
                if (plus_one)
                    cur_elem += 1;
                else
                    plus_one = true;
            }
            else {
                cur_elem = array[i] + obj.array[j];
            }
        }
        // add to string
        for (; cur_elem>0; cur_elem /= 10)
            result2 = std::to_string(cur_elem%10) + result2;
    }
    return BigInt(result1 + result2);
}

const BigInt BigInt::operator-(const BigInt& obj) const {

}

const BigInt BigInt::operator*(const BigInt& obj) const {

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool operator<(const BigInt& obj) const;
bool operator<=(const BigInt& obj) const;
bool operator>(const BigInt& obj) const;
bool operator>=(const BigInt& obj) const;
bool operator==(const BigInt& obj) const;
bool operator!=(const BigInt& obj) const;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const BigInt& obj) {
    return os;
}
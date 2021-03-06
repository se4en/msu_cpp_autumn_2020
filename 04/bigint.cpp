#include "bigint.h"

Big_int::Big_int() {
    len = 0;
    array = nullptr;
    minus = false;
}

Big_int::Big_int(const std::string& int_str) {
    // 1234567 stored as 67, 45, 23, 1 
    if (int_str.empty())
        throw "Empty string!";
    std::string::const_iterator it = int_str.begin();
    uint64_t cur_pos = 0;
    uint32_t cur_elem = 0;

    // checking for -
    if ((*it)=='-') {
        len = (int) (int_str.length() - 1)/BASE + 1;
        minus = true;
        ++it;
    }
    else {
        len = (int) int_str.length()/BASE + 1;
        minus = false;
    }

    try {
        array = new uint32_t[len];
    }
    catch(const std::bad_alloc& err) {
        std::cout << "Bad construction - no memmory!\n";
        return;
    }

    cur_pos = len-1;
    // save first elem
    int first_elem_end = minus ? (int_str.length()-1)%BASE : int_str.length()%BASE;
    for (int i=0; i < first_elem_end; ++i) {
        cur_elem = 10*cur_elem + (*it) - '0';
        ++it;    
    }
    array[cur_pos--] = cur_elem;    
    cur_elem = 0;
    
    // save to array
    int _cntr = 0;
    while (it!=int_str.end() && std::isdigit(*it)) {
        if (_cntr==BASE || cur_elem>=int(pow(10, BASE-1))) {
            array[cur_pos--] = cur_elem;
            cur_elem = (*it) - '0'; 
            _cntr = 1;
        }
        else {
            cur_elem = 10*cur_elem + (*it) - '0';
            _cntr++;
        }
        ++it;
    }
    if (cur_pos>=0)
        array[cur_pos] = cur_elem;
    // if met no digit
    if (it!=int_str.end()) {
        this->~Big_int();
        throw "String is not digit!";
    }
}

Big_int::Big_int(const Big_int& obj) {
    try {
        array = new uint32_t[obj.len];
    }
    catch(const std::bad_alloc& err) {
        std::cout << "Bad construction - no memmory!\n";
        return;
    }
    len = obj.len; 
    minus = obj.minus; 

    for (uint32_t i=0; i<len; ++i)
        array[i] = obj.array[i];
}

Big_int::Big_int(Big_int && obj) {
    minus = obj.minus;
    len = obj.len;
    array = obj.array;

    obj.minus = false;
    obj.len = 0;
    obj.array = nullptr;
}

Big_int& Big_int::operator=(const Big_int& obj) {
    if (len!=obj.len) {
        try {
            uint32_t* new_array = new uint32_t[obj.len];
            delete[] array;
            array = new_array;
        }
        catch(const std::bad_alloc& err) {
            std::cout << "Bad construction - no memmory!\n";
        }
        
        len = obj.len;  
        minus = obj.minus;
    }
    for (uint32_t i=0; i<len; ++i)
        array[i] = obj.array[i];
    return (*this);
}

Big_int& Big_int::operator=(Big_int && obj) {
    delete [] array;
    minus = obj.minus;
    len = obj.len;
    array = obj.array;

    obj.minus = false;
    obj.len = 0;
    obj.array = nullptr;

    return (*this);
}

Big_int::~Big_int() {
    delete[] array;
}

// delete non-significant zeros
void Big_int::_resize() {
    uint64_t t = len - 1, ctr = 0;
    while(t>0 && !array[t--])
        ++ctr;
    if (ctr) {
        try {
            uint32_t* new_array = new uint32_t[len - ctr];
            len -= ctr;
            for (uint64_t i=0; i<len; ++i)
                new_array[i] = array[i];
            delete[] array;
            array = new_array;
        }
        catch(const std::bad_alloc& err) {
            std::cout << "Cant resize - no memmory!\n";
            return;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Big_int Big_int::operator-() const {
    Big_int new_big_int(*this);
    new_big_int.minus = !(*this).minus;
    return new_big_int;
}

Big_int Big_int::operator+(const Big_int& obj) const {
    if (!minus && !obj.minus) {
        bool plus_one = false;
        Big_int result;
        result.minus = false;
        result.len = std::max(len, obj.len);
        try {
            result.array = new uint32_t[result.len];
        }
        catch(const std::bad_alloc& err) {
            std::cout << "Cant add - no memmory!\n";
            return Big_int("0");
        }
        for (uint64_t t=0; t<result.len; ++t)
            result.array[t] = 0;
        uint64_t i = 0;

        for (; i<std::min(len, obj.len); ++i) {
            result.array[i] = array[i] + obj.array[i];
            if (plus_one) {
                result.array[i]++;
                plus_one = false;
            }
            if (result.array[i]>=int(pow(10, BASE))) {
                result.array[i]-=int(pow(10, BASE));
                plus_one = true;
            }
        }

        for (; i<len; ++i) {
            result.array[i] = array[i];
            if (plus_one) {
                result.array[i]++;
                plus_one = false;
                if (result.array[i]>=int(pow(10, BASE))) {
                    result.array[i]-=int(pow(10, BASE));
                    plus_one = true;
                }
            }
        }
        for (; i<obj.len; ++i) {
            result.array[i] = obj.array[i];
            if (plus_one) {
                result.array[i]++;
                plus_one = false;
                if (result.array[i]>=int(pow(10, BASE))) {
                    result.array[i]-=int(pow(10, BASE));
                    plus_one = true;
                }
            }
        }
        
        result._resize();
        return result;
    }
    else if (minus && obj.minus) {
        return -((-(*this)) + (-obj));
    }
    else if (minus && !obj.minus) {
        return -(obj - (-(*this)));
    }
    else { // if (!minus && obj.minus) 
        return (*this) - (-obj);
    }
}

Big_int Big_int::operator-(const Big_int& obj) const {
    if (!minus && !obj.minus) {
        if ((*this)<obj) 
            return -(obj - (*this));

        bool minus_one = false;
        Big_int result;
        result.minus = false;
        result.len = std::max(len, obj.len);
        try {
            result.array = new uint32_t[result.len];
        }
        catch(const std::bad_alloc& err) {
            std::cout << "Cant subtract - no memmory!\n";
            return Big_int("0");
        }
        for (uint64_t t=0; t<result.len; ++t)
            result.array[t] = 0;
        uint64_t i = 0;

        for (; i<obj.len; ++i) {
            if (array[i] - (minus_one ? 1 : 0) < obj.array[i]) {
                minus_one = true;
            }   
            else {
                result.array[i] = array[i] - (minus_one ? 1 : 0) - obj.array[i];
                minus_one = false;
            }
        }

        for (; i<len; ++i) {
            if (array[i] - (minus_one ? 1 : 0) < 0) {
                result.array[i] = std::pow(10, BASE) + array[i] - (minus_one ? 1 : 0);
                minus_one = true;
            }   
            else {
                result.array[i] = array[i] - (minus_one ? 1 : 0);
                minus_one = false;
            }
        }

        result._resize();
        return result;
    }
    else if (minus && obj.minus) {
        return (-obj) - (-(*this));
    }
    else if (minus && !obj.minus) {
        return -(obj + (-(*this)));
    }
    else { // if (!minus && obj.minus) 
        return (*this) + (-obj);
    }
}

Big_int Big_int::operator*(const Big_int& obj) const {
    if (minus==obj.minus) {
        bool plus_one = false;
        Big_int result;
        result.minus = false;
        result.len = len + obj.len;
        try {
            result.array = new uint32_t[result.len];
        }
        catch(const std::bad_alloc& err) {
            std::cout << "Cant multiply - no memmory!\n";
            return Big_int("0");
        }
        for (uint64_t t=0; t<result.len; ++t)
            result.array[t] = 0;
        uint64_t i = 0, j = 0;

        for (; i<obj.len; ++i) {
            for (j=0; j<len; ++j) {
                uint64_t mul_res =(uint64_t) obj.array[i]*array[j];

                if (!mul_res) {
                    result.array[j + i] = mul_res;
                }
                uint64_t k = 0; 
                for (; mul_res; ++k) {
                    result.array[j + i + k] += (mul_res%uint32_t(std::pow(10, BASE)) + (plus_one ? 1: 0));
                    mul_res /= std::pow(10, BASE);
                    plus_one = false;
                    if (result.array[j + i + k]>=std::pow(10, BASE)) {
                        result.array[j + i + k]-=std::pow(10, BASE);
                        plus_one = true;
                    }
                }
                if (plus_one) {
                    result.array[j + i + k]++;
                    plus_one = false;
                }
            }
        }

        result._resize();
        return result;
    }
    else {
        return -((-(*this))*obj);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Big_int::operator==(const Big_int& obj) const {
    if (len!=obj.len || minus!=obj.minus)
        return false;
    else {
        for (uint64_t i=0; i<len; ++i) {
            if (array[i]!=obj.array[i])
                return false;
        }
        return true;
    }
}

bool Big_int::operator!=(const Big_int& obj) const {
    return !((*this)==obj);
}

bool Big_int::operator<(const Big_int& obj) const {
    if (minus!=obj.minus)
        return minus;
    if (len==obj.len) {
        for (uint64_t i=len; i>0; --i) {
            if (array[i]!=obj.array[i])
                return array[i]*minus<obj.array[i]*obj.minus;
        }
    }
    int l_min = minus ? -1 : 1;
    int r_min = obj.minus ? -1 : 1;
    return len*l_min<obj.len*r_min;
}

bool Big_int::operator>=(const Big_int& obj) const {
    return !((*this)<obj);
}

bool Big_int::operator>(const Big_int& obj) const {
    if (minus!=obj.minus)
        return !minus;
    if (len==obj.len) {
        for (uint64_t i=len; i>0; --i) {
            if (array[i]!=obj.array[i])
                return array[i]*minus>obj.array[i]*obj.minus;
        }
    }
    return len*minus<obj.len*obj.minus;
}

bool Big_int::operator<=(const Big_int& obj) const {
    return !((*this)>obj);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const Big_int& obj) {
    if (obj.minus)
        os << "-";
    os << obj.array[obj.len-1];

    for (int i=obj.len-2; i>=0; --i) {
        //os << " ";
        int j=pow(10, obj.BASE-1);
        if (obj.array[i]==0)
            os << "000000000";
        else {
            for (; obj.array[i]/j==0; j/=10) {
                os << "0";
                if (j<10) 
                    break;
            }
            os << obj.array[i];
        }
        
    }
    return os;
}
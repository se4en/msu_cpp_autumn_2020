#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <cmath>
#include <exception>
	

class Big_int {
    bool minus;
    static const uint32_t BASE = 9; // 999999999
    uint32_t* array; 
    uint32_t len;

    void _resize();
public:
    Big_int();
    Big_int(const std::string& int_str);
    Big_int(const Big_int& obj);
    Big_int(Big_int && obj);
    Big_int& operator=(const Big_int& obj);
    Big_int& operator=(Big_int && obj);
    ~Big_int();

    Big_int operator-() const;
    Big_int operator+(const Big_int& obj) const;
    Big_int operator-(const Big_int& obj) const;
    Big_int operator*(const Big_int& obj) const;

    bool operator<(const Big_int& obj) const;
    bool operator<=(const Big_int& obj) const;
    bool operator>(const Big_int& obj) const;
    bool operator>=(const Big_int& obj) const;
    bool operator==(const Big_int& obj) const;
    bool operator!=(const Big_int& obj) const;

    friend std::ostream& operator<<(std::ostream& os, const Big_int& obj);
};

#endif
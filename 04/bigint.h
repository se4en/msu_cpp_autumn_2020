#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <cmath>


class Big_int {
    bool minus;
    // элементы массива - двузначные числа
    uint32_t BASE = 9; // 900000000
    uint32_t* array; 
    uint32_t len;

    void _resize();
public:
    Big_int();
    Big_int(std::string int_str);
    Big_int(const Big_int& obj);
    Big_int& operator=(const Big_int& obj);
    ~Big_int();

    const Big_int operator-() const;
    const Big_int operator+(const Big_int& obj) const;
    const Big_int operator-(const Big_int& obj) const;
    const Big_int operator*(const Big_int& obj) const;

    bool operator<(const Big_int& obj) const;
    bool operator<=(const Big_int& obj) const;
    bool operator>(const Big_int& obj) const;
    bool operator>=(const Big_int& obj) const;
    bool operator==(const Big_int& obj) const;
    bool operator!=(const Big_int& obj) const;

    friend std::ostream& operator<<(std::ostream& os, const Big_int& obj);
};

#endif 
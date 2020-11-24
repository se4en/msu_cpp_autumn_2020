#include <iostream>
#include <limits.h>

class BigInt {
    bool minus;
    uint64_t* array;
    const uint8_t LLMAX_LEN = 19;
    uint64_t len;
public:
    BigInt(std::string int_str);
    ~BigInt();

    BigInt(const BigInt& obj);
    BigInt& operator=(const BigInt& obj);

    const BigInt operator-() const;
    const BigInt operator+(const BigInt& obj) const;
    const BigInt operator-(const BigInt& obj) const;
    const BigInt operator*(const BigInt& obj) const;

    bool operator<(const BigInt& obj) const;
    bool operator<=(const BigInt& obj) const;
    bool operator>(const BigInt& obj) const;
    bool operator>=(const BigInt& obj) const;
    bool operator==(const BigInt& obj) const;
    bool operator!=(const BigInt& obj) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& obj);
};
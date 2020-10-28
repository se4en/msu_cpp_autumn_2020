#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>

class Matrix_proxy{
    int* row_ptr;
    uint32_t row_len;
public:
    Matrix_proxy(int* ptr, uint32_t len);
    int operator[](uint32_t index) const;
    int& operator[](uint32_t index);
};

class Matrix {
    uint32_t n_rows;
    uint32_t m_columns;
    int* data;
public:
    Matrix(uint32_t n_rows, uint32_t m_columns);
    Matrix(const Matrix &obj);
    ~Matrix();

    int get_rows() const;
    int get_columns() const;
    Matrix& operator=(const Matrix &obj) ;
    Matrix_proxy operator[](uint32_t index);
    const Matrix_proxy operator[](uint32_t index) const;
    Matrix& operator*=(int digit);
    Matrix operator+(Matrix obj) const;
    bool operator==(const Matrix obj) const;
    bool operator!=(const Matrix obj) const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& obj);
};

#endif
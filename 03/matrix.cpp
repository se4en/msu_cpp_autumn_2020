#include "matrix.h"

/**
 * Base constuctor
 */
Matrix_proxy::Matrix_proxy(int* ptr, uint32_t len) {
    row_ptr = ptr;
    row_len = len;
}

/**
 * Return element from row
 */
int Matrix_proxy::operator[](uint32_t index) const {
    if (index>=row_len)
        throw std::out_of_range("ERROR: index must be less than row_len");
    return row_ptr[index];
}

/**
 * Return element from row
 */
int& Matrix_proxy::operator[](uint32_t index) {
    if (index>=row_len)
        throw std::out_of_range("ERROR: index must be less than row_len");
    return row_ptr[index];
}

//========================================================================================================================================================

/**
 * Base constructor
 */
Matrix::Matrix(uint32_t n_rows, uint32_t m_columns) {
    if (n_rows*m_columns==0)
        throw std::invalid_argument("ERROR: matrix must have at least 1 row and 1 column");
    this->n_rows = n_rows;
    this->m_columns = m_columns;
    data = new int[n_rows*m_columns];
}

/**
 * Сopy constructor
 */
Matrix::Matrix(const Matrix &matr) {
    n_rows = matr.n_rows;
    m_columns = matr.m_columns;
    data = new int[n_rows*m_columns];
    for (uint32_t i=0; i<n_rows*m_columns; ++i)
        data[i] = matr.data[i];
}

Matrix::~Matrix() {
    delete[] data;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------

int Matrix::get_rows() const {
    return n_rows;
}

int Matrix::get_columns() const {
    return m_columns;
}

Matrix& Matrix::operator=(const Matrix &matr) {
    if (n_rows==matr.n_rows && m_columns==matr.m_columns)
        for (uint32_t i=0; i<n_rows*m_columns; ++i)
            data[i] = matr.data[i];
    else {
        delete[] data;
        n_rows = matr.n_rows;
        m_columns = matr.m_columns;
        data = new int[n_rows*m_columns];
        for (uint32_t i=0; i<n_rows*m_columns; ++i)
            data[i] = matr.data[i];
    }
    return *this;
}

/**
 * Return row from matrix
 */
Matrix_proxy Matrix::operator[](uint32_t index) {
    if (index>=n_rows)
        throw std::out_of_range("ERROR: index must be less than count of rows");
    return Matrix_proxy(data+index*m_columns, m_columns);      
}

/**
 * Return row from matrix
 */
const Matrix_proxy Matrix::operator[](uint32_t index) const {
    if (index>=n_rows)
        throw std::out_of_range("ERROR: index must be less than count of rows");
    return Matrix_proxy(data+index*m_columns, m_columns);      
}

Matrix& Matrix::operator*=(int digit) {
    for (uint32_t i=0; i<n_rows*m_columns; ++i)
        data[i] *= digit;
    return *this;
}

Matrix Matrix::operator+(Matrix obj) const {
    if (n_rows!=obj.n_rows || m_columns!=obj.m_columns)
        throw std::invalid_argument("ERROR: matrices must be of the same dimension");
    Matrix new_obj(obj.n_rows, obj.m_columns);
    for (uint32_t i=0; i<obj.n_rows; ++i)
        for (uint32_t j=0; j<obj.m_columns; ++j)
            new_obj[i][j] = (*this)[i][j] + obj[i][j];
    return new_obj;
}

bool Matrix::operator==(const Matrix obj) const {
    if (n_rows!=obj.n_rows || m_columns!=obj.m_columns)
        return false;
    for (uint32_t i=0; i<obj.n_rows*obj.m_columns; ++i) 
        if ((*this).data[i]!=obj.data[i])
            return false;
    return true;
}

bool Matrix::operator!=(const Matrix obj) const {
    if (n_rows!=obj.n_rows || m_columns!=obj.m_columns)
        return true;
    for (uint32_t i=0; i<obj.n_rows; ++i)
        for (uint32_t j=0; j<obj.m_columns; ++j)
            if ((*this)[i][j]!=obj[i][j])
                return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Matrix& obj) {
    for (int i=0; i<obj.get_rows(); ++i) {
        for (int j=0; j<obj.get_columns(); ++j)
            os << std::setw(4) << obj[i][j];
        os << std::endl;
    }   
    return os;
}
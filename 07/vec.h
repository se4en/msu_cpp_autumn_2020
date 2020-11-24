#ifndef VEC_H
#define VEC_H

#include <stdint.h>
//#include "raiter.h"

#define REALL_SIZE 16

template <class T>
class vector {
    T* data;
    uint32_t size;
    uint32_t capacity;
public:
    vector(); // +
    vector(const vector<T>& other); // +

    T& operator[](uint32_t index); // +
    void vector<T>::reserve(uint32_t capacity); // +
    void push_back(const T& value); //  +
    void pop_back(); // +
    template<typename... Args>
    void emplace_back(Args&&... args); // +
    bool empty(); // +
    uint32_t size(); // +
    void clear(); // +

    raIterator begin();
    raIterator rbegin();
    end();
    rend();
    resize();
    capacity();
};

#endif
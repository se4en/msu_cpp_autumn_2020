#ifndef VECTOR_H
#define VECTOR_H

#include "iterator.h"
#include "allocator.h"
#include <utility>

#define REALL_SIZE 16

template <class T>
class vector {
    T* data_;
    uint32_t size_;
    uint32_t capacity_;
    allocator<T> al;
public:
    vector(); // +
    vector(const vector<T>& other); // +

    T& operator[](uint32_t index); // +
    void reserve(uint32_t capacity); // +
    void push_back(const T& value); //  +
    void pop_back(); // +
    template<typename... Args>
    void emplace_back(Args&&... args); // +
    bool empty(); // +
    uint32_t size(); // +
    uint32_t capacity(); // +
    void clear(); // +
    void resize(uint32_t new_size); // +

    iterator<T>& begin() const; // +
    iterator<T>& end() const; // +
    
    reverse_iterator<T>& rbegin() const; // +
    reverse_iterator<T>& rend() const; // +
};

#endif
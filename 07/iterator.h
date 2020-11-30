#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdint.h>

template <class T>
class iterator {
    T* data;
    uint32_t index;
public:
    iterator(T* ptr, uint32_t index);

    iterator& operator--();
    iterator& operator++();
    T& operator*() const;

    friend bool operator==(iterator& left, iterator& right);
    friend bool operator!=(iterator& left, iterator& right);
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T>
class reverse_iterator {
    T* data;
    uint32_t index;
public:
    reverse_iterator(T* ptr, uint32_t index);

    reverse_iterator& operator--();
    reverse_iterator& operator++();
    T& operator*() const;

    friend bool operator==(reverse_iterator& left, reverse_iterator& right);
    friend bool operator!=(reverse_iterator& left, reverse_iterator& right);
};

#endif
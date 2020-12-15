#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdint.h>

template<class T>
class iterator;

template<class S>
bool operator==(iterator<S>&, iterator<S>&);

template<class S>
bool operator!=(iterator<S>&, iterator<S>&);

template <class T>
class iterator {
    T* data;
    uint32_t index;
public:
    iterator(T* ptr, uint32_t index);

    iterator operator--();
    iterator<T> operator++();
    T& operator*() const;

    friend bool operator==<T>(iterator<T>& left, iterator<T>& right);
    friend bool operator!=<T>(iterator<T>& left, iterator<T>& right);
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
class reverse_iterator;

template<class S>
bool operator==(reverse_iterator<S>&, reverse_iterator<S>&);

template<class S>
bool operator!=(reverse_iterator<S>&, reverse_iterator<S>&);

template <class T>
class reverse_iterator {
    T* data;
    uint32_t index;
public:
    reverse_iterator(T* ptr, uint32_t index);

    reverse_iterator& operator--();
    reverse_iterator& operator++();
    T& operator*() const;

    friend bool operator==<T>(reverse_iterator& left, reverse_iterator& right);
    friend bool operator!=<T>(reverse_iterator& left, reverse_iterator& right);
};

//============================================================================================================================================================

template<class T>
iterator<T>::iterator(T* ptr, uint32_t ind) {
    data = ptr;
    index = ind;
}

template <class T>
iterator<T> iterator<T>::operator--() {
    --index; 
    return *this;
}

template <class T>
iterator<T> iterator<T>::operator++() {
    ++index; 
    return *this;
}

template <class T>
T& iterator<T>::operator*() const {
    return data[index];
}

template<class T>
bool operator==(iterator<T>& left, iterator<T>& right) {
    return (left.data==right.data) && (left.index==right.index);
}

template<class T>
bool operator!=(iterator<T>& left, iterator<T>& right) {
    return !operator==(left, right);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
reverse_iterator<T>::reverse_iterator(T* ptr, uint32_t ind) {
    data = ptr;
    index = ind;
}

template <class T>
reverse_iterator<T>& reverse_iterator<T>::operator--() {
    ++index; 
    return *this;
}

template <class T>
reverse_iterator<T>& reverse_iterator<T>::operator++() {
    --index; 
    return *this;
}

template <class T>
T& reverse_iterator<T>::operator*() const {
    return data[index];
}

template<class T>
bool operator==(reverse_iterator<T>& left, reverse_iterator<T>& right) {
    return (left.data==right.data) && (left.index==right.index);
}

template<class T>
bool operator!=(reverse_iterator<T>& left, reverse_iterator<T>& right) {
    return !operator==(left, right);
}

#endif
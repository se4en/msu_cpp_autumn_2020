#include "iterator.h"

template<class T>
iterator<T>::iterator(T* ptr, uint32_t ind) {
    data = ptr;
    index = ind;
}

template <class T>
iterator<T>& iterator<T>::operator--() {
    --index; 
    return *this;
}

template <class T>
iterator<T>& iterator<T>::operator++() {
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
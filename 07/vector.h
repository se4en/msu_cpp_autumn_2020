#ifndef VECTOR_H
#define VECTOR_H

#include "iterator.h"
#include "allocator.h"
#include <utility>
#include <stdexcept>

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
    vector(vector<T>&& other); 
    vector<T>& operator=(const vector<T>& other);
    vector<T>& operator=(vector<T>&& other);
    ~vector();

    T& operator[](uint32_t index); // +
    const T& operator[](uint32_t index) const;
    void reserve(uint32_t capacity);
    void push_back(const T& value); //  +
    void push_back(T&& value);
    void pop_back(); // +
    template<typename... Args>
    void emplace_back(Args&&... args); // +
    bool empty() const; // +
    uint32_t size() const; // +
    uint32_t capacity() const; // +
    void clear(); // +
    void resize(uint32_t new_size); // +

    iterator<T> begin() const; // +
    iterator<T> end() const; // +
    
    reverse_iterator<T> rbegin() const; // +
    reverse_iterator<T> rend() const; // +
};

//=================================================================================================================================================================

template<class T>
vector<T>::vector() {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    al = allocator<T>(); 
}

template<class T>
vector<T>::vector(const vector<T>& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = al.allocate(size_);
    for (uint32_t i = 0; i < size_; ++i)
        al.construct(data_ + i, other.data_[i]);   
}

template<class T>
vector<T>::vector(vector<T>&& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    al = other.al;
    data_ = other.data_;
    other.capacity_ = 0;
    other.size_ = 0;
    other.al = allocator<T>();
    other.data = nullptr;
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
    try {
        T* buffer = al.allocate(size_); 
        al.deallocate(data_);
        data_ = buffer;
        size_ = other.size_;
        capacity_ = other.capacity_;
        for (uint32_t i = 0; i < size_; ++i)
            al.construct(data_ + i, other.data_[i]);   
    }
    catch (const std::bad_alloc& err) {
        std::cout << "Copy error - no free memmory!" << std::endl;
    }
    return (*this);
}

template<class T>
vector<T>& vector<T>::operator=(vector<T>&& other) {
    if (this == &other)
        return (*this);
    capacity_ = other.capacity_;
    size_ = other.size_;
    al.deallocate(data_);
    data_ = other.data_;
    al = other.al;
    other.capacity_ = 0;
    other.size_ = 0;
    other.al = allocator<T>();
    other.data = nullptr;
    return (*this);
}

template<class T>
vector<T>::~vector() {
    for (uint32_t i = 0; i < size_; ++i)
        al.destroy(data_ + i);
    if (data_!=nullptr)
        al.deallocate(data_);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
T& vector<T>::operator[](uint32_t index) {
    if (index>=size_)
        throw std::out_of_range("ERROR: index must be less than size");
    return data_[index];
}

template<class T>
const T& vector<T>::operator[](uint32_t index) const {
    if (index>=size_)
        throw std::out_of_range("ERROR: index must be less than size");
    return data_[index];
}

template<class T>
void vector<T>::reserve(uint32_t capacity) {
    if (capacity_<capacity) {
        T* buffer = al.allocate(capacity);
        if (buffer) {
            for (uint32_t i=0; i<size_; ++i) {
                al.construct(buffer + i, std::move(data_[i])); 
                al.destroy(data_ + i);
            }
            al.deallocate(data_); 
            capacity_ = capacity;
            data_ = buffer;
        }        
    }
}

template<class T>
void vector<T>::push_back(const T& value) {
    if (size_==capacity_)
        reserve(capacity_ + REALL_SIZE);
    al.construct(data_ + size_, value);
    size_++;
}

template<class T>
void vector<T>::push_back(T&& value) {
    if (size_==capacity_)
        reserve(capacity_ + REALL_SIZE);
    al.construct(data_ + size_, std::move(value));
    size_++;
}

template<class T>
void vector<T>::pop_back() {
    al.destroy(data_ + size_);
    --size_;
}

template<class T>
template<class... Args>
void vector<T>::emplace_back(Args&&... args) {
    if (size_==capacity_)
        reserve(capacity_ + REALL_SIZE);
    al.construct(data_ + size_, T(std::forward<Args>(args)...)); 
    size_++;
}

template<class T>
bool vector<T>::empty() const {
    return size_==0;
}

template<class T>
uint32_t vector<T>::size() const {
    return size_;
}

template<class T>
uint32_t vector<T>::capacity() const {
    return capacity_;
}

template<class T>
void vector<T>::clear() {
    for (int i=size_; i>0; --i)
        al.destroy(data_ + i - 1);
    al.deallocate(data_); 
    data_ = nullptr;
    size_ = 0;
}

template<class T>
void vector<T>::resize(uint32_t new_size) {
    if (new_size<size_) {
        for (uint32_t i=size_; i>new_size; --i)
            al.destroy(data_ + i - 1);
    }
    else {
        reserve(new_size);
        for (uint32_t i=size_; i<new_size; ++i)
            al.construct(data_ + i, T());
    }
    size_ = new_size;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
iterator<T> vector<T>::begin() const {
    return iterator<T>(data_, 0);
}

template<class T>
iterator<T> vector<T>::end() const {
    return iterator<T>(data_, size_);
}

template<class T>
reverse_iterator<T> vector<T>::rbegin() const {
    return reverse_iterator<T>(data_, size_ - 1);
}

template<class T>
reverse_iterator<T> vector<T>::rend() const {
    return reverse_iterator<T>(data_, -1);
}

#endif
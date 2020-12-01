#include "vector.h"

template<class T>
vector<T>::vector()
{
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    al = allocator<T>(); 
}

template<class T>
vector<T>::vector(const vector<T>& other)
{
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = al.allocate(size_);
    // data = new T[size];
    for (int i = 0; i < size_; ++i)
        al.construct(data_ + i, other.data_[i]); //data[i] = other.data[i];  
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
T& vector<T>::operator[](uint32_t index)
{
    return data_[index];
}

template<class T>
void vector<T>::reserve(uint32_t capacity)
{
    if (capacity_!=capacity) 
    {
        T* buffer = al.allocate(capacity); // new T[capacity];
        if (buffer)
        {
            for (int i=0; i<size_; ++i) {
                al.construct(buffer + i, data_[i]); // buffer[i] = data[i];
                al.destroy(data_ + i);
            }
            al.deallocate(data_); // delete[] data;
            capacity_ = capacity;
            data_ = buffer;
        }        
    }
}

template<class T>
void vector<T>::push_back(const T& value)
{
    if (size_==capacity_)
        reserve(capacity_ + REALL_SIZE);
    size_++;
    al.construct(data_ + size_, value);
}


template<class T>
void vector<T>::pop_back()
{
    al.destruct(data_ + size_);
    --size_;
}

template<class T>
template<class... Args>
void vector<T>::emplace_back(Args&&... args)
{
    if (size_==capacity_)
        reserve(capacity_ + REALL_SIZE);
    size_++;
    al.construct(data_ + size_, std::move(T(std::forward<Args>(args)...))); // data[++size] = std::move(T(std::forward<Args>(args)...));
}

template<class T>
bool vector<T>::empty()
{
    return size_==0;
}

template<class T>
uint32_t vector<T>::size()
{
    return size_;
}

template<class T>
uint32_t vector<T>::capacity()
{
    return capacity_;
}

template<class T>
void vector<T>::clear()
{
    for (int i=size_; i>0; --i)
        al.destroy(data_ + i - 1);
    al.deallocate(data_); //delete[] data;
    data_ = nullptr;
    size_ = 0;
}

template<class T>
void vector<T>::resize(uint32_t new_size) {
    if (new_size<size_) {
        for (int i=size_; i>new_size; --i)
            al.destroy(data_ + i - 1);
    }
    else {
        reserve(new_size);
        for (int i=size_; i<new_size; ++i)
            al.construct(data_ + i, T());
    }
    size_ = new_size;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
iterator<T>& vector<T>::begin() const {
    return iterator(data_, 0);
}

template<class T>
iterator<T>& vector<T>::end() const {
    return iterator(data_, size_ + 1);
}

template<class T>
reverse_iterator<T>& vector<T>::rbegin() const {
    return reverse_iterator(data_, size_);
}

template<class T>
reverse_iterator<T>& vector<T>::rend() const {
    return reverse_iterator(data_, -1);
}
/*
CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: clean allocator.o iterator.o vector.o tests.o

allocator.o: 
	$(CC) $(FLAGS) allocator.cpp -c

iterator.o: 
	$(CC) $(FLAGS) iterator.cpp -c

vector.o: 
	$(CC) $(FLAGS) vector.cpp -c

tests.o: allocator.o iterator.o vector.o
	$(CC) $(FLAGS) tests.cpp -c
	$(CC) $(FLAGS) allocator.o iterator.o vector.o tests.o -o test

test: clean tests.o
	./test

valgrind: clean tests.o
	valgrind ./test

clean:
	rm -f *.o
	rm -f test
*/
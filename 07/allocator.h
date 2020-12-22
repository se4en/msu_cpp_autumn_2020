#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdint.h>
#include <iostream>

#define MAX_PTRS 16 

template <class T>
class allocator {
    T* ptrs[MAX_PTRS];
    uint32_t ptrs_count;
public:
    allocator();
    allocator(const allocator<T>& other);
    ~allocator();
    
    T* allocate(uint32_t size);
    void deallocate(T* ptr);

    void construct(T* ptr, const T& value);
    void destroy(T* ptr);
};

//========================================================================================================================================================

template<class T>
allocator<T>::allocator() {
    for (uint32_t i=0; i<MAX_PTRS; ++i)
        ptrs[i] = nullptr;
    //ptrs_count = 0;
}

template<class T>
allocator<T>::allocator(const allocator<T>& other) {
    ~allocator();
    for (uint32_t i=0; i<ptrs_count; ++i)
        ptrs[i] = other.ptrs[i];
}

template<class T>
allocator<T>::~allocator() {
    for (uint32_t i=0; i<MAX_PTRS; ++i) 
        if (ptrs[i]!=nullptr)
            delete[] ptrs[i];
}

template <class T>
T* allocator<T>::allocate(uint32_t size) {
    uint32_t i=0;
    for (;i<MAX_PTRS && ptrs[i]!=nullptr; ++i) {}
    if (i==MAX_PTRS)
        throw std::bad_alloc();
    ptrs[i] = new T[size];
    ptrs_count++;
    return ptrs[i];
}

template<class T>
void allocator<T>::deallocate(T* ptr) {
    for (uint32_t i=0; i<MAX_PTRS; ++i)
        if (ptrs[i]==ptr) {
            delete[] ptrs[i];
            ptrs[i] = nullptr;
            break;
        }
}

template<class T>
void allocator<T>::construct(T* ptr, const T& value) {
    new((void*)ptr) T(value);
}

template<class T>
void allocator<T>::destroy(T* ptr) {
    ((T*)ptr)->~T();
}

#endif

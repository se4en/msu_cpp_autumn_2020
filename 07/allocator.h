#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdint.h>
#include <iostream>

#define PTRS_STEP 4

template <class T>
class allocator {
    T** ptrs;
    uint32_t ptrs_count;
public:
    allocator();
    allocator(const allocator<T>& other);
    ~allocator();
    
    T* allocate(uint32_t size);
    void deallocate(T* ptr) const;

    void construct(T* ptr, const T& value);
    void destroy(T* ptr);
};

//======================================================================================

template<class T>
allocator<T>::allocator() {
    ptrs = new T*[PTRS_STEP];
    for (uint32_t i=0; i<PTRS_STEP; ++i)
        ptrs[i] = nullptr;
    ptrs_count = PTRS_STEP;
}

template<class T>
allocator<T>::allocator(const allocator<T>& other) {
    ~allocator();
    allocate(other.ptrs_count);
    for (uint32_t i=0; i<ptrs_count; ++i)
        ptrs[i] = other.ptrs[i];
}

template<class T>
allocator<T>::~allocator() {
    for (uint32_t i=0; i<ptrs_count; ++i)
        if (ptrs[i]!=nullptr)
            delete[] ptrs[i];
    delete[] ptrs;
}

template <class T>
T* allocator<T>::allocate(uint32_t size) {
    uint32_t i=0;
    for (; i<ptrs_count && ptrs[i]!=nullptr; ++i) {}
    if (i==ptrs_count) { // need more ptrs
        T** new_ptrs = new T*[ptrs_count + PTRS_STEP];
        uint32_t j=0;
        for (; j<ptrs_count; ++j)
            new_ptrs[j] = ptrs[j];
        for (; j<ptrs_count + PTRS_STEP; ++j)
            new_ptrs[j] = nullptr;
        delete[] ptrs;
        ptrs = new_ptrs;
        ptrs_count += PTRS_STEP;
    }
    ptrs[i] = new T[size];
    return ptrs[i];
}

template<class T>
void allocator<T>::deallocate(T* ptr) const {
    for (uint32_t i=0; i<ptrs_count; ++i)
        if (ptrs[i]==ptr) {
            delete[] ptrs[i];
            ptrs[i] = nullptr;
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

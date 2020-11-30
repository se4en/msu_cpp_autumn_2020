#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdint.h>

template <class T>
class allocator {
    T* cur_ptr;
    uint32_t cur_size;
public:
    allocator();
    allocator(const allocator<T>& other);
    
    T* allocate(uint32_t size) const;
    void deallocate(T* ptr) const;

    void construct(T* ptr, T& value);
    void destroy(T* ptr);
};

#endif
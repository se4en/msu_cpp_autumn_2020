#include "allocator.h"

template<class T>
allocator<T>::allocator()
{
    cur_ptr = nullptr;
    cur_size = 0;
}

template<class T>
allocator<T>::allocator(const allocator<T>& other)
{
    deallocate();
    allocate(other.cur_size);
    for (int i=0; i<cur_size; ++i)
        cur_ptr[i] = other.cur_ptr[i];
}

template <class T>
T* allocator<T>::allocate(uint32_t size) const
{
    if (cur_size!=0)
        deallocate();
    if (size==0)
        return nullptr;
    cur_ptr = new T[size];
    return cur_ptr;
}

template<class T>
void allocator<T>::deallocate(T* ptr) const
{
    delete[] ptr;
}

template<class T>
void allocator<T>::construct(T* ptr, T& value) 
{
    ((T*)ptr)->T(value);
}

template<class T>
void allocator<T>::destroy(T* ptr)
{
    ((T*)ptr)->~T();
}
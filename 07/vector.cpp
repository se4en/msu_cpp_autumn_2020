#include "vector.h"

template<class T>
vector<T>::vector()
{
    data = nullptr;
    size = 0;
    capacity = 0;
    al = allocator(); 
}

template<class T>
vector<T>::vector(const vector<T>& other)
{
    size = other.size;
    capacity = other.capacity;
    data = al.allocate(size);
    // data = new T[size];
    for (int i = 0; i < my_size; ++i)
        al.construct(data + i, other.data[i]); //data[i] = other.data[i];  
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
T& vector<T>::operator[](uint32_t index)
{
    return data[index];
}

template<class T>
void vector<T>::reserve(uint32_t capacity)
{
    if (this->capacity!=capacity) 
    {
        T* buffer = al.allocate(capacity); // new T[capacity];
        if (buffer)
        {
            for (int i=0; i<size; ++i) {
                al.construct(buffer + i, data[i]); // buffer[i] = data[i];
                al.destroy(data + i);
            }
            al.deallocate(data); // delete[] data;
            this->capacity = capacity;
            data = buffer;
        }        
    }
}

template<class T>
void push_back(const T& value)
{
    if (size==capacity)
        this->reserve(capacity + REALL_SIZE);
    size ++;
    al.construct(data + size, value);
}


template<class T>
void pop_back()
{
    al.destruct(data + size);
    --size;
}

template<class T>
template<class... Args>
void vector<T>::emplace_back(Args&&... args)
{
    if (size==capacity)
        this->reserve(capacity + REALL_SIZE);
    size++:
    al.construct(data + size, std::move(T(std::forward<Args>(args)...))); // data[++size] = std::move(T(std::forward<Args>(args)...));
}

template<class T>
bool vector<T>::empty()
{
    return size==0;
}

template<class T>
uint32_t vector<T>::size()
{
    return size;
}

template<class T>
uint32_t vector<T>::capacity()
{
    return capacity;
}

template<class T>
void vector<T>::clear()
{
    for (int i=size; i>0; --i)
        al.destroy(data + i - 1);
    al.deallocate(data); //delete[] data;
    data = nullptr;
    size = 0;
}

template<class T>
void vector<T>::resize(uint32_t new_size) {
    if (new_size<size) {
        for (int i=size; i>new_size; --i)
            al.destroy(data + i - 1);
    }
    else {
        reserve(new_size);
        for (int i=size; i<new_size; ++i)
            al.construct(data + i, T());
    }
    size = new_size;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T>
iterator<T>& vector<T>::begin() const {
    return iterator(data, 0);
}

template<class T>
iterator<T>& vector<T>::end() const {
    return iterator(data, size+1);
}

template<class T>
reverse_iterator<T>& vector<T>::rbegin() const {
    return reverse_iterator(data, size);
}

template<class T>
reverse_iterator<T>& vector<T>::rend() const {
    return reverse_iterator(data, -1);
}
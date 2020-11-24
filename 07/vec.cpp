#include <vec.h>

template<class T>
vector<T>::vector()
{
    data = nullptr;
    size = 0;
    capacity = 0;
}

template<class T>
vector<T>::vector(const vector<T>& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new T[size];  
    for (int i = 0; i < my_size; ++i)
        data[i] = other.data[i];  
}

//-------------------------------------------------------------------------------

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
        T* buffer = new T[capacity];
        if (buffer)
        {
            for (int i=0; i<size; ++i)
                buffer[i] = data[i];
            delete[] data;
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
    data[size++] = value;
}


template<class T>
void pop_back()
{
    --size;
}

template<class T>
template<class... Args>
void vector<T>::emplace_back(Args&&... args)
{
    if (size==capacity)
        this->reserve(capacity + REALL_SIZE);
    data[++size] = std::move(T(std::forward<Args>(args)...));
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
void vector<T>::clear()
{
    delete[] data;
    data = nullptr;
    size = 0;
}

//-----------------------------------------------

template<class T>
raIterator vector<T>::begin()
{
    // .....
}

#include "allocator.h"

Allocator::Allocator() {
    base = nullptr;
    offset = nullptr;
    max_size = 0;
    free_size = 0;
}

Allocator::~Allocator() {
    if (base!=nullptr)
        delete[] base;
}

void Allocator::makeAllocator(size_t max_size) {
    try {
        this->max_size = max_size;
        free_size = max_size;
        if (base!=nullptr)
            delete[] base;
        base = new char[max_size];
        offset = base;  
    }
    catch(bad_alloc) {
        this->max_size = 0;
        free_size = 0;
        base = nullptr;
        offset = nullptr;
    }
}

char* Allocator::alloc(size_t size) {
    if ((free_size < size) || (size < 0)) {
        return nullptr;
    }
    else {
        free_size -= size;
        char* result = offset;
        offset += size*sizeof(char);
        return result;
    }
}

void Allocator::reset() {
    free_size = max_size;
    offset = base;
}
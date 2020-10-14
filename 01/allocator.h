#include <iostream>

using namespace std;

class Allocator {
    char* base;
    char* offset;
    size_t max_size;
    size_t free_size;
public:
    Allocator();
    ~Allocator();

    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
};
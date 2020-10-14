#include "allocator.h"

#define FAIL(test, result, right_result) cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << endl; 
#define OK(test, result, right_result) cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << endl;

void default_work_test() {
    Allocator alc;
    alc.makeAllocator(64);
    char* ptr = alc.alloc(50);
    if (ptr!=nullptr) 
        OK("default_work", static_cast<const void*>(ptr), "not nullptr")
    else
        FAIL("default_work", static_cast<const void*>(ptr), "not nullptr")
}

void big_alloc_test() {
    Allocator alc;
    alc.makeAllocator(256);
    char* ptr = alc.alloc(512);
    if (ptr==nullptr) 
        OK("big_alloc", static_cast<const void*>(ptr), "nullptr")
    else
        FAIL("big_alloc", static_cast<const void*>(ptr), "nullptr")
}

void reset_test() {
    Allocator alc;
    alc.makeAllocator(256);
    char* ptr_1 = alc.alloc(64);
    alc.reset();
    char* ptr_2 = alc.alloc(64);
    if (ptr_1==ptr_2) 
        OK("reset", static_cast<const void*>(ptr_2), static_cast<const void*>(ptr_1))
    else
        FAIL("reset", static_cast<const void*>(ptr_2), static_cast<const void*>(ptr_1))
}

void negative_allocator_test() {
    Allocator alc;
    alc.makeAllocator(-10);
    char* ptr = alc.alloc(5);
    if (ptr==nullptr) 
        OK("negative_allocator", static_cast<const void*>(ptr), "nullptr")
    else
        FAIL("negative_allocator", static_cast<const void*>(ptr), "nullptr")
}

void negative_alloc_test() {
    Allocator alc;
    alc.makeAllocator(60);
    char* ptr = alc.alloc(-5);
    if (ptr==nullptr) 
        OK("negative_alloc", static_cast<const void*>(ptr), "nullptr")
    else
        FAIL("negative_alloc", static_cast<const void*>(ptr), "nullptr")
}

int main() {
    default_work_test();
    big_alloc_test();
    reset_test();
    negative_allocator_test();
    negative_alloc_test();
    return 0;
}
#include "thread_pool.h"

struct A {};

void foo(const A&) {return;}

int boo(const A&) {return 10;}

int main() {
 
    Thread_pool pool(4);


    auto task1 = pool.exec(boo, A());
    std::cout << task1.get() << std::endl;

    auto task2 = pool.exec([]() { return 1; });
    task2.get();
    
    //pool.~Thread_pool();
}
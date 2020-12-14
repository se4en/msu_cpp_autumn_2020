#include "thread_pool.h"

#define FAIL(test, result, right_result) std::cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl; 
#define OK(test, result, right_result) std::cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl;


int sum(int a, int b) { return a+b; }
int diff(int a, int b) { return a-b; }

void base_work_test() {
    Thread_pool pool(4);

    auto task1 = pool.exec(sum, 3, 2);
    auto task2 = pool.exec(diff, 3, 2);
    auto res_1 = task1.get(); 
    auto res_2 = task2.get();

    if (res_1==5 && res_2==1)
        OK("base work", res_1 << res_2, "51")
    else
        FAIL("base work", res_1 << res_2, "51")
}

void multithread_test() {
    Thread_pool pool(4);

    auto task1 = pool.exec(sum, 3, 2);
    auto task2 = pool.exec(diff, 3, 2);
    auto res_1 = task1.get(); 
    auto res_2 = task2.get();

    if (res_1==5 && res_2==1)
        OK("base work", res_1 << res_2, "51")
    else
        FAIL("base work", res_1 << res_2, "51")

}

int main() {
    base_work_test();
}
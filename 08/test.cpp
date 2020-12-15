#include "thread_pool.h"
#include <unistd.h>
#include <stdio.h> 
#include <time.h> 

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

void queue_test() {
    time_t start, end;

    Thread_pool pool(2);
    time(&start);
    auto task1 = pool.exec([]() { sleep(2); return 1; });
    auto task2 = pool.exec([]() { sleep(2); return 1; });
    auto task3 = pool.exec([]() { sleep(2); return 1; });
    task1.get(); 
    task2.get();
    task3.get();
    time(&end);

    double seconds = difftime(end, start); 
    if (seconds > 3.5)
        OK("queue work", seconds, "~4")
    else
        FAIL("queue work", seconds, "~4")
}

void queue_2_test() {
    time_t start, end;

    Thread_pool pool(2);
    time(&start);
    auto task1 = pool.exec([]() { sleep(2); return 1; });
    auto task2 = pool.exec([]() { sleep(2); return 1; });
    auto task3 = pool.exec([]() { sleep(2); return 1; });
    auto task4 = pool.exec([]() { sleep(2); return 1; });
    auto task5 = pool.exec([]() { sleep(2); return 1; });
    task1.get(); task2.get(); task3.get(); task4.get(); task5.get();
    time(&end);

    double seconds = difftime(end, start); 
    if (seconds > 5.5)
        OK("queue 2", seconds, "~6")
    else
        FAIL("queue 2", seconds, "~6")
}

void many_threads_test() {
    Thread_pool pool(1000);
    auto task1 = pool.exec([]() { sleep(2); return 1; });
    auto task2 = pool.exec([]() { sleep(2); return 1; });

    uint16_t result = pool.get_size();
    if (result < 33)
        OK("many threads", result, "<33")
    else
        FAIL("many threads", result, "<33")
}

int main() {
    base_work_test();
    queue_test();
    queue_2_test();
    many_threads_test();
}
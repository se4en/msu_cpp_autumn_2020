#include "thread_pool.h"

/*
CC=g++
FLAGS=-std=c++17 -Wall -pedantic -pthread

all: clean thread_pool.o test.o

thread_pool.o: 
	$(CC) $(FLAGS) thread_pool.cpp -c

test.o: 
	$(CC) $(FLAGS) test.cpp -c
	$(CC) $(FLAGS) thread_pool.o test.o -o test

test: clean test.o
	./test

clean:
	rm -f *.o
	rm -f test
*/


/*
void Thread_pool::plug_function() {
    while(1) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(tasks_mutex);
            condition.wait(lock, [this] {return !tasks.empty();});
            auto task = std::move(tasks.front());
            tasks.pop();  
        }
        task();
    }
}
*/

Thread_pool::Thread_pool(size_t pool_size) {
    for(size_t i=0; i<pool_size; ++i)
        pool.emplace_back( // it doesnt work with member function (
            [this] {
                while(1) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(tasks_mutex);
                        condition.wait(lock, [this] {return !tasks.empty();});
                        auto task = std::move(tasks.front());
                        tasks.pop();  
                    }
                    task();
                }
            }
        );
}

Thread_pool::~Thread_pool() {
    {
        std::unique_lock<std::mutex> lock(tasks_mutex);
    }
    std::vector<std::thread>::iterator it = pool.begin();
    for(; it!=pool.end(); ++it)
        (*it).join();
}

template <class Func, class... Args>
auto Thread_pool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    // 
    using return_type = typename std::result_of<Func(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>> (
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
    );

    std::future<return_type> result = task->get_future();
    {
        std::unique_lock<std::mutex> lock(tasks_mutex);
        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one();
    return result;
}

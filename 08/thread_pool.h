#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <future>
#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <condition_variable>
#include <iostream>

class Thread_pool {
    std::vector<std::thread> pool;
    std::queue< std::function<void()>> tasks;

    bool stop;
    std::mutex tasks_mutex;
    std::condition_variable condition;

    // void plug_function();
public:
    explicit Thread_pool(size_t pool_size);
    ~Thread_pool();

    template<class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};

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
    stop = false;
    for(size_t i=0; i<pool_size; ++i)
        pool.emplace_back( // it doesnt work with member function
            [this] {
                while(1) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(tasks_mutex);
                        condition.wait(lock, [this] {return stop || !tasks.empty();});
                        if (stop && tasks.empty()) 
                            return;
                        task = std::move(tasks.front());
                        tasks.pop();  
                    }
                    task();
                }
            }
        );
}

Thread_pool::~Thread_pool() {
    {
        stop = true;
        std::unique_lock<std::mutex> lock(tasks_mutex);
    }
    /* it doesnt work
    std::vector<std::thread>::iterator it = pool.begin();
    for(; it!=pool.end(); ++it) {
        std::cout << "join" << std::endl;
        (*it).join();
    }
    */
    condition.notify_all();
    for(std::thread &worker: pool)
        worker.join();    
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



#endif
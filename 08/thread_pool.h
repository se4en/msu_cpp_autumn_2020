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
    std::queue<std::function<void()>> tasks;
    uint16_t size;

    bool stop;
    std::mutex tasks_mutex;
    std::condition_variable condition; // needed unique_lock
public:
    explicit Thread_pool(size_t pool_size);
    ~Thread_pool();

    uint16_t get_size();

    template<class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};

Thread_pool::Thread_pool(size_t pool_size) {
    stop = false;
    size = std::thread::hardware_concurrency();
    if (pool_size<=size)
        size = pool_size;    
    for(size_t i=0; i<size; ++i)
        pool.emplace_back( // doesnt work with member function
            [this] {
                while(1) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(tasks_mutex);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
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
    stop = true;
    
    condition.notify_all();
    for(std::thread &worker: pool)
        worker.join(); 
}

uint16_t Thread_pool::get_size() {
    return size;
}

template <class Func, class... Args>
auto Thread_pool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    // need to result
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

#ifndef MGL_THREAD_POOL_HPP
#define MGL_THREAD_POOL_HPP

#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <queue>
#include <functional>
#include <condition_variable>

class MGL_ThreadPool {
    // Hardware thread count : unsigned int n = std::thread::hardware_concurrency();
    public:
        MGL_ThreadPool(int num_threads = std::thread::hardware_concurrency());
        ~MGL_ThreadPool();
        void executeConcurrentTask(std::function<void()> task);
        const int & getPoolSize();
        int awaitAllTaskAndThreadCompletion(int timeout_ms);
    private:
        const int num_threads_;
        std::vector<std::thread> thread_pool_;
        std::vector<bool> free_threads_;
        std::mutex task_queue_mutex_;
        std::condition_variable cv_;
        std::queue<std::function<void()>> task_queue_;
        bool quit_ = false;
};

#endif
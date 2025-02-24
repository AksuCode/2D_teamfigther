#include "../include/mgl_thread_pool.hpp"

MGL_ThreadPool::MGL_ThreadPool(int num_threads) : num_threads_(num_threads) {
    for (int i = 0; i < num_threads_; i++) {
        free_threads_.push_back(true);
        thread_pool_.emplace_back([i, this] {
            const int thread_number = i;
            while(true) {
                std::function<void()> task;

                // Curly braces are essential because they create a new scope. unique_lock frees the mutex when out of its scope.
                // Took 2 hours of debugging. Never even thought that braces could matter in such a way. FUCK
                {
                    std::unique_lock lk(task_queue_mutex_);
                    cv_.wait(lk, [this]{return !task_queue_.empty() || quit_;});

                    if (quit_ && task_queue_.empty()) {
                        return;
                    }

                    free_threads_[thread_number] = false;

                    task = std::move(task_queue_.front());
                    task_queue_.pop();
                } // Unlocked here

                task();

                free_threads_[thread_number] = true;
            }
        });
    }
}

MGL_ThreadPool::~MGL_ThreadPool() {

    // Curly braces are essential because they create a new scope. unique_lock frees the mutex when out of its scope.
    // Took 2 hours of debugging. Never even thought that braces could matter in such a way. FUCK
    {
        std::unique_lock lk(task_queue_mutex_);
        quit_ = true;
    } // Unlocked here

    cv_.notify_all();

    for (auto it = thread_pool_.begin(); it != thread_pool_.end(); it++) {
        (*it).join();
    }
}

void MGL_ThreadPool::executeConcurrentTask(std::function<void()> task) {
    {
        std::unique_lock lk(task_queue_mutex_);
        task_queue_.emplace(std::move(task));
    }
    cv_.notify_one();
}

const int & MGL_ThreadPool::getPoolSize() {
    return num_threads_;
}

// Might take too much CPU due to busy waiting. Should be switched to something better.
int MGL_ThreadPool::awaitAllTaskAndThreadCompletion(int timeout_ms) {
    auto timeout_duration = std::chrono::milliseconds(timeout_ms);
    std::chrono::time_point begin_tp = std::chrono::steady_clock::now();

    while (!(task_queue_.empty() && std::all_of(free_threads_.begin(), free_threads_.end(), [](bool b) { return b; }))) {
        if ((std::chrono::steady_clock::now() - begin_tp) >= timeout_duration) {return -1;}
        std::this_thread::yield();
    }

    return 0;
}
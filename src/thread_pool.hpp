#pragma once

#include <functional>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>

class ThreadPool {
    // An atomic all idling threads use
    std::atomic<bool> running;

    // While std::thread is not copy-able, the std::vector STL container
    // allows for movable elements instead. keep this in mind when a bug happens
    std::vector<std::thread> threads;

    // Queues are better suited for the job here, since first-requested-jobs
    // should have higher priority than the last one, this allows sequential
    // completion of tasks
    std::queue<std::function<void()>> jobs;

    // Our mutex for preventing race conditions on the queue above
    std::mutex job_mutex;
public:
    ThreadPool();
    ~ThreadPool();
    void add_job(std::function<void()> job);
    void thread_loop(void);

    template<typename I, typename F>
    static void for_each(I first, I last, F func) {
        const size_t n_threads = (size_t)std::thread::hardware_concurrency();
        if(!std::distance<I>(first, last))
            return;

        const size_t iterators_per_thread = std::distance<I>(first, last) / n_threads;
        
        for(; first != last; first++) {
            func(*first);
        }
    }
};
#pragma once

#ifndef SRC_THREADPOOL_HPP
#define SRC_THREADPOOL_HPP

#include <functional>
#include <future>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

#include "./SafeQueue.hpp"

class ThreadPool {
 public:
  ThreadPool() : m_threads_(std::vector<std::thread>(std::thread::hardware_concurrency())), m_shutdown_(false) {}
  ThreadPool(const int n_threads) : m_threads_(std::vector<std::thread>(n_threads)), m_shutdown_(false) {}

  ThreadPool(const ThreadPool &) = delete;
  ThreadPool &operator=(const ThreadPool &) = delete;

  ThreadPool(ThreadPool &&) = delete;
  ThreadPool &operator=(ThreadPool &&) = delete;

  // Destructor or shutdown just select one is Ok
  ~ThreadPool() {
    m_shutdown_ = true;
    m_conditional_lock_.notify_all();

    for (int i = 0; i < m_threads_.size(); ++i) {
      if (m_threads_[i].joinable()) {
        m_threads_[i].join();
      }
    }
  }

  // Inits thread pool
  void Init() {
    for (int i = 0; i < m_threads_.size(); ++i) {
      m_threads_[i] = std::thread(ThreadWorker(this, i));
    }
  }

  // Waits until threads finish their current task and shutdowns the pool
  void Shutdown() {
    m_shutdown_ = true;
    m_conditional_lock_.notify_all();

    for (int i = 0; i < m_threads_.size(); ++i) {
      if (m_threads_[i].joinable()) {
        m_threads_[i].join();
      }
    }
  }

  // Submit a function to be executed asynchronously by the pool
  template <typename F, typename... Args>
  auto Submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))> {
    using return_type = std::invoke_result<F, Args...>::type;

    // Create a function with bounded parameters ready to execute
    std::function<return_type()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

    // Encapsulate it into a shared ptr in order to be able to copy construct / assign
    auto task_ptr = std::make_shared<std::packaged_task<return_type()>>(func);

    // // Create a function with bounded parameters ready to execute
    // std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

    // // Encapsulate it into a shared ptr in order to be able to copy construct / assign
    // auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

    // Wrap packaged task into void function
    std::function<void()> wrapper_func = [task_ptr]() { (*task_ptr)(); };

    // Enqueue generic wrapper function
    m_queue_.Enqueue(wrapper_func);

    // Wake up one thread if its waiting
    m_conditional_lock_.notify_one();

    // Return future from promise
    return task_ptr->get_future();
  }

 private:
  class ThreadWorker {
   private:
    int m_id_;
    ThreadPool *m_pool_;

   public:
    ThreadWorker(ThreadPool *pool, const int id) : m_pool_(pool), m_id_(id) {}

    void operator()() {
      std::function<void()> func;
      bool dequeued;
      while (!m_pool_->m_shutdown_) {
        {
          std::unique_lock<std::mutex> lock(m_pool_->m_conditional_mutex_);
          if (m_pool_->m_queue_.Empty()) {
            m_pool_->m_conditional_lock_.wait(lock);
          }
          dequeued = m_pool_->m_queue_.Dequeue(func);
        }
        if (dequeued) {
          func();
        }
      }
    }
  };

  bool m_shutdown_;
  std::vector<std::thread> m_threads_;        // store threads
  SafeQueue<std::function<void()>> m_queue_;  // store task

  std::mutex m_conditional_mutex_;
  std::condition_variable m_conditional_lock_;
};

#endif /* !SRC_THREADPOOL_HPP */

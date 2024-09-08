#pragma once

#ifndef SRC_SAFEQUEUE_HPP
#define SRC_SAFEQUEUE_HPP

#include <mutex>
#include <queue>

// Thread safe implementation of a Queue using an std::queue
template <typename T>
class SafeQueue {
 public:
  SafeQueue() = default;
  ~SafeQueue() = default;

  SafeQueue(const SafeQueue &other) = delete;
  SafeQueue &operator=(const SafeQueue &other) = delete;

  SafeQueue(SafeQueue &&other) = delete;
  SafeQueue &operator=(SafeQueue &&other) = delete;

  bool Empty() {
    std::unique_lock<std::mutex> lock(m_mutex_);
    return m_queue_.empty();
  }

  int Size() {
    std::unique_lock<std::mutex> lock(m_mutex_);
    return m_queue_.size();
  }

  void Enqueue(T &value) {
    std::unique_lock<std::mutex> lock(m_mutex_);
    m_queue_.emplace(value);
  }

  void Enqueue(T &&value) {
    std::unique_lock<std::mutex> lock(m_mutex_);
    m_queue_.emplace(std::move(value));
  }

  bool Dequeue(T &value) {
    std::unique_lock<std::mutex> lock(m_mutex_);

    if (m_queue_.empty()) {
      return false;
    }
    value = std::move(m_queue_.front());

    m_queue_.pop();
    return true;
  }

 private:
  std::queue<T> m_queue_;
  std::mutex m_mutex_;
};

#endif /* !SRC_SAFEQUEUE_HPP */

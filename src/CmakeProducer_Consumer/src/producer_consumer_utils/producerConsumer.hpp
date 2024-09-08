#pragma once
#ifndef SRC_PRODUCERCONSUMER_HPP
#define SRC_PRODUCERCONSUMER_HPP

#include <mutex>
#include <queue>
#include <vector>
#include <thread>
#include <atomic>
#include <iostream>
#include <condition_variable>

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
    std::unique_lock<std::mutex> locker(m_mutex_);
    return m_queue_.empty();
  }

  int Size() {
    std::unique_lock<std::mutex> locker(m_mutex_);
    return m_queue_.size();
  }

  void Push(T &val) {
    std::unique_lock<std::mutex> locker(m_mutex_);
    m_queue_.emplace(val);
  }

  void Push(T &&val) {
    std::unique_lock<std::mutex> locker(m_mutex_);
    m_queue_.emplace(std::move(val));
  }

  bool Pop(T &val) {
    std::unique_lock<std::mutex> locker(m_mutex_);
    if (m_queue_.empty()) {
      return false;
    } else {
      val = std::move(m_queue_.front());
      m_queue_.pop();
      return true;
    }
  }

 private:
  std::mutex m_mutex_;
  std::queue<T> m_queue_;
};

/*
** 1、队列已满，生产者停止生产商品-->生产者 wait 条件变量
** 2、队列为空，消费者无商品可取-->消费者 wait 条件变量
** 3、队列不满但非空，生产者正常生产商品，消费者正常取商品
*/

template <typename T>
class ProducerConsumer {
 public:
  ProducerConsumer() : m_queue_max_size_(20), m_producer_threads_(2), m_consumer_threads_(2), m_running_status_(true) {
    Initalize();
  }
  ProducerConsumer(int queue_max_size, int producer_num, int consumer_num)
      : m_queue_max_size_(queue_max_size),
        m_producer_threads_(producer_num),
        m_consumer_threads_(consumer_num),
        m_running_status_(true) {
    Initalize();
  }

  ~ProducerConsumer() {
    m_running_status_ = false;
    m_queue_not_full_.notify_all();
    m_queue_not_empty_.notify_all();

    for (auto &thread : m_producer_threads_) {
      if (thread.joinable()) {
        thread.join();
      }
    }

    for (auto &thread : m_consumer_threads_) {
      if (thread.joinable()) {
        thread.join();
      }
    }
  }

 private:
  int m_queue_max_size_;
  SafeQueue<T> m_queue_;

  std::condition_variable m_queue_not_full_;
  std::condition_variable m_queue_not_empty_;

  std::vector<std::thread> m_producer_threads_;
  std::vector<std::thread> m_consumer_threads_;

  std::mutex m_mutex_;
  std::atomic<bool> m_running_status_;

  void Initalize() {
    for (size_t i = 0; i < m_producer_threads_.size(); ++i) {
      m_producer_threads_[i] = std::thread(&ProducerConsumer::Producer, this);
    }

    for (size_t i = 0; i < m_consumer_threads_.size(); ++i) {
      m_consumer_threads_[i] = std::thread(&ProducerConsumer::Consumer, this);
    }
  }

  bool IsFull() {
    if (m_queue_.Size() >= m_queue_max_size_) {
      return true;
    }

    return false;
  }

  void Producer() {
    while (m_running_status_) {
      std::unique_lock<std::mutex> locker(m_mutex_);
      if (IsFull()) {
        std::cout << "Queue is full, waitting for m_queue_not_full" << std::endl;
        m_queue_not_full_.wait(locker);
      }

      if (!IsFull()) {
        T val = 3;
        m_queue_.Push(val);
        m_queue_not_empty_.notify_one();
      }
    }
  }

  void Consumer() {
    while (m_running_status_) {
      std::unique_lock<std::mutex> locker(m_mutex_);
      if (m_queue_.Empty()) {
        std::cout << "Queue is empty, waitting for m_queue_not_empty" << std::endl;
        m_queue_not_empty_.wait(locker);
      }

      if (!m_queue_.Empty()) {
        T val;
        bool result = m_queue_.Pop(val);
        val++;
        std::cout << "result: " << val << std::endl;

        m_queue_not_full_.notify_one();
      }
    }
  }
};

#endif  // SRC_PRODUCERCONSUMER_HPP

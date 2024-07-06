/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 读写锁
 * @version 0.1
 * @date 2024-03-18
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * 读写锁是一种并发编程中的同步机制，它允许多个线程同时读取共享资源，但只允许一个线程写入共享资源。
 * 使用读写锁的主要优点是可以提高并发性能和吞吐量，因为读取操作是非常频繁的，而写入操作相对较少。
 * 如果多个线程同时进行读取操作，读写锁可以避免互斥锁的串行执行，提高并发性能。
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>

std::mutex mtx;

class ThreadSafeCounter {
 public:
  ThreadSafeCounter() = default;

  /// @brief 多个线程/读者能同时度计数器的值
  /// @return
  size_t get() const {
    // 读者, 获取共享锁, 使用shared_lock
    std::shared_lock<std::shared_mutex> lck(mutex_);
    return value_;
  }

  /// @brief 只有一个线程/写者能充值/写计数器的值
  /// @return
  size_t increment() {
    // 写者, 获取独占锁, 使用unique_lock
    std::unique_lock<std::shared_mutex> lck(mutex_);
    value_++;
    return value_;
  }

  /// @brief 只有一个线程/写者能重置/写计数器的值
  void reset() {
    // 写者, 获取独占锁, 使用unique_lock
    std::unique_lock<std::shared_mutex> lck(mutex_);
    value_ = 0;
  }

 private:
  mutable std::shared_mutex mutex_;
  size_t value_ = 0;
};

ThreadSafeCounter counter;

void reader(int id) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::unique_lock<std::mutex> ulck(mtx);
  std::cout << "reader #" << id << " get value " << counter.get() << "\n";
}

void writer(int id) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::unique_lock<std::mutex> ulck(mtx);
  std::cout << "writer #" << id << " write value " << counter.increment() << std::endl;
}

int main(int argc, char *argv[]) {
  std::thread rth[10];
  std::thread wth[10];
  for (int i = 0; i < 4; i++) {
    rth[i] = std::thread(reader, i + 1);
  }
  for (int i = 0; i < 6; i++) {
    wth[i] = std::thread(writer, i + 1);
  }

  for (int i = 0; i < 4; i++) {
    rth[i].join();
  }
  for (int i = 0; i < 6; i++) {
    wth[i].join();
  }

  return 0;
}
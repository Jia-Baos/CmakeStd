/**
 * @file message_queue.hpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 消息队列的实现
 * @version 0.1
 * @date 2024-03-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class MessageQueue {
 public:
  /// @brief 推入消息
  /// @param msg 消息对象
  void Push(const T &msg) {
    std::unique_lock<std::mutex> lck(m_mtx_);
    m_queue_.push(msg);
    m_cv_.notify_one();
  }

  /// @brief 轮询消息
  /// @param msg 消息对象
  /// @return 是否接收到消息
  bool Poll(T &msg) {
    std::unique_lock<std::mutex> lck(m_mtx_);
    if (m_queue_.size()) {
      msg = m_queue_.front();
      m_queue_.pop();
      return true;
    }
    return false;
  }

  /// @brief 等待消息
  /// @param msg 消息对象
  void Wait(T &msg) {
    std::unique_lock<std::mutex> lck(m_mtx_);
    while (!m_queue_.size()) {
      m_cv_.wait(lck);
    }

    msg = m_queue_.front();
    m_queue_.pop();
  }

  /// @brief 队列长度
  /// @return 队列长度
  size_t Size() {
    std::unique_lock<std::mutex> lck(m_mtx_);
    return m_queue_.size();
  }

 private:
  std::mutex m_mtx_;              // 互斥量
  std::queue<T> m_queue_;         // 消息队列
  std::condition_variable m_cv_;  // 条件变量
};

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
  void push(const T &msg) {
    std::unique_lock<std::mutex> lck(m_mtx);
    m_queue.push(msg);
    m_cv.notify_one();
  }

  /// @brief 轮询消息
  /// @param msg 消息对象
  /// @return 是否接收到消息
  bool poll(T &msg) {
    std::unique_lock<std::mutex> lck(m_mtx);
    if (m_queue.size()) {
      msg = m_queue.front();
      m_queue.pop();
      return true;
    }
    return false;
  }

  /// @brief 等待消息
  /// @param msg 消息对象
  void wait(T &msg) {
    std::unique_lock<std::mutex> lck(m_mtx);
    while (!m_queue.size()) {
      m_cv.wait(lck);
    }

    msg = m_queue.front();
    m_queue.pop();
  }

  /// @brief 队列长度
  /// @return 队列长度
  size_t size() {
    std::unique_lock<std::mutex> lck(m_mtx);
    return m_queue.size();
  }

 private:
  std::mutex m_mtx;              // 互斥量
  std::queue<T> m_queue;         // 消息队列
  std::condition_variable m_cv;  // 条件变量
};
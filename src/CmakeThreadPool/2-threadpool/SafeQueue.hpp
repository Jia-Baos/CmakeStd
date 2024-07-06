#pragma once

#ifndef SRC_SAFEQUEUE_HPP
#define SRC_SAFEQUEUE_HPP

#include <mutex>
#include <queue>

// Thread safe implementation of a Queue using an std::queue
template <typename T>
class SafeQueue
{
public:
    SafeQueue() = default;
    ~SafeQueue() = default;

    SafeQueue(const SafeQueue &other) = delete;
    SafeQueue &operator=(const SafeQueue &other) = delete;

    SafeQueue(SafeQueue &&other) = delete;
    SafeQueue &operator=(SafeQueue &&other) = delete;

    bool empty()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    int size()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    void enqueue(T &value)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.emplace(value);
    }

    void enqueue(T &&value)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.emplace(std::move(value));
    }

    bool dequeue(T &value)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        if (m_queue.empty())
        {
            return false;
        }
        value = std::move(m_queue.front());

        m_queue.pop();
        return true;
    }

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
};

#endif /* !SRC_SAFEQUEUE_HPP */

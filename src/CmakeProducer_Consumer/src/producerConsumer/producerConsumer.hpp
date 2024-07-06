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
        std::unique_lock<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }

    int size()
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        return m_queue.size();
    }

    void push(T &val)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_queue.emplace(val);
    }

    void push(T &&val)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_queue.emplace(std::move(val));
    }

    bool pop(T &val)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        if (m_queue.empty())
        {
            return false;
        }
        else
        {
            val = std::move(m_queue.front());
            m_queue.pop();
            return true;
        }
    }

private:
    std::mutex m_mutex;
    std::queue<T> m_queue;
};

/*
** 1、队列已满，生产者停止生产商品-->生产者 wait 条件变量
** 2、队列为空，消费者无商品可取-->消费者 wait 条件变量
** 3、队列不满但非空，生产者正常生产商品，消费者正常取商品
*/

template <typename T>
class ProducerConsumer
{
public:
    ProducerConsumer() : m_queue_max_size(20), m_producer_threads(2), m_consumer_threads(2), m_running_status(true)
    {
        initalize();
    }
    ProducerConsumer(int queue_max_size, int producer_num, int consumer_num) : m_queue_max_size(queue_max_size), m_producer_threads(producer_num), m_consumer_threads(consumer_num), m_running_status(true)
    {
        initalize();
    }

    ~ProducerConsumer()
    {
        m_running_status = false;
        m_queue_not_full.notify_all();
        m_queue_not_empty.notify_all();

        for (auto &thread : m_producer_threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }

        for (auto &thread : m_consumer_threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }

private:
    int m_queue_max_size;
    SafeQueue<T> m_queue;

    std::condition_variable m_queue_not_full;
    std::condition_variable m_queue_not_empty;

    std::vector<std::thread> m_producer_threads;
    std::vector<std::thread> m_consumer_threads;

    std::mutex m_mutex;
    std::atomic<bool> m_running_status;

    void initalize()
    {
        for (size_t i = 0; i < m_producer_threads.size(); ++i)
        {
            m_producer_threads[i] = std::thread(&ProducerConsumer::producer, this);
        }

        for (size_t i = 0; i < m_consumer_threads.size(); ++i)
        {
            m_consumer_threads[i] = std::thread(&ProducerConsumer::consumer, this);
        }
    }

    bool isFull()
    {
        if (m_queue.size() >= m_queue_max_size)
        {
            return true;
        }

        return false;
    }

    void producer()
    {
        while (m_running_status)
        {
            std::unique_lock<std::mutex> locker(m_mutex);
            if (isFull())
            {
                std::cout << "Queue is full, waitting for m_queue_not_full" << std::endl;
                m_queue_not_full.wait(locker);
            }

            if (!isFull())
            {
                T val = 3;
                m_queue.push(val);
                m_queue_not_empty.notify_one();
            }
        }
    }

    void consumer()
    {
        while (m_running_status)
        {
            std::unique_lock<std::mutex> locker(m_mutex);
            if (m_queue.empty())
            {
                std::cout << "Queue is empty, waitting for m_queue_not_empty" << std::endl;
                m_queue_not_empty.wait(locker);
            }

            if (!m_queue.empty())
            {
                T val;
                bool result = m_queue.pop(val);
                val++;
                std::cout << "result: " << val << std::endl;

                m_queue_not_full.notify_one();
            }
        }
    }
};

#endif // SRC_PRODUCERCONSUMER_HPP
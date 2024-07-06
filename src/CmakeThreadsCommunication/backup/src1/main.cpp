/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief ͨ通过条件变量进行线程间的通信，cond.notify_all()
 * @version 0.1
 * @date 2024-03-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <stdio.h>
#include <thread>
#include <deque>
#include <mutex>
#include <vector>
#include <condition_variable>
using namespace std;

std::mutex mtx;
std::condition_variable cv;
std::vector<int> vec;
int productNum = 5;

void Producer()
{
    for (int i = 1; i <= productNum; ++i)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (!vec.empty())
        {
            cv.wait(lock); // vec 不为空时阻塞当前线程
        }
        vec.push_back(i);
        std::cout << "Producer生产产品：" << i << std::endl;
        cv.notify_all(); // 释放线程锁
    }
}
void Consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx); // vec 为空时等待线程锁。其他线程锁释放时，当前线程继续执行
        while (vec.empty())
        {
            cv.wait(lock);
        }
        int data = vec.back();
        vec.pop_back();
        std::cout << "Consumer消费产品：" << data << std::endl;
        cv.notify_all();
    }
}
int main(int argc, const char *argv[])
{
    std::thread t1(Producer);
    std::thread t2(Consumer);
    t2.join();
    t1.join();
    return 0;

    // Producer生产产品: 1
    // Consumer消费产品: 1
    // Producer生产产品: 2
    // Consumer消费产品: 2
    // Producer生产产品: 3
    // Consumer消费产品: 3
    // Producer生产产品: 4
    // Consumer消费产品: 4
    // Producer生产产品: 5
    // Consumer消费产品: 5
}

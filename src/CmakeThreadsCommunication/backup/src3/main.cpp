/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 通过标志位来通知线程间的通信
 * @version 0.1
 * @date 2024-03-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <stdio.h>
#include <vector>
#include <numeric>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

int res = 0;                  // 保存结果的全局变量
std::mutex mu;                // 互斥锁全局变量
std::condition_variable cond; // 全局条件变量
void accumulate(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
    int sum = std::accumulate(first, last, 0); // 标准库求和函数
    std::cout << sum << std::endl;
    std::unique_lock<std::mutex> locker(mu);
    std::cout << "执行了" << res << "次" << std::endl;
    res = sum;
    locker.unlock();
    cond.notify_one(); // 向一个等待线程发出条件已满足通知
}
int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    std::thread work_thread(accumulate, numbers.begin(), numbers.end());
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, []()
              { return res; }); // 如果条件变量被唤醒，检查结果是否被改变，为真则直接返回，为假则继续等待
    std::cout << "wait被卡住" << std::endl;
    std::cout << "result=" << res << std::endl;
    locker.unlock();
    work_thread.join();
    return 0;

    // 21
    // 执行了0次
    // wait被卡住
    // result=21
}

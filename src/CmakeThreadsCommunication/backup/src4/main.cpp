/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief ͨ通过std::future来进行线程间的通信
 * @version 0.1
 * @date 2024-03-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <vector>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>
void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum); // 将结果存入，并让共享状态变为就绪以提醒future
}
int main()
{
    // 演示用promise<int>在线程间传递结果
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    std::thread work_thread(accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));
    accumulate_future.wait(); // 等待结果
    std::cout << "result=" << accumulate_future.get() << std::endl;
    work_thread.join();
    return 0;

    // result=21
}

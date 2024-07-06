/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 通过std::future来进行线程间的通信，使用async传递结果
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

int accumulate(std::vector<int>::iterator first,
               std::vector<int>::iterator last)
{
    int sum = std::accumulate(first, last, 0);
    return sum;
}
int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    auto accumulate_future = std::async(std::launch::async, accumulate, numbers.begin(), numbers.end());
    std::cout << "result=" << accumulate_future.get() << std::endl;
    return 0;

    // result=21
}

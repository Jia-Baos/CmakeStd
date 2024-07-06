/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 使用async传递被调用线程返回结果
 * @version 0.1
 * @date 2024-03-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>

int accumulate(std::vector<int>::iterator first,
               std::vector<int>::iterator last)
{
    int sum = std::accumulate(first, last, 0);
    return sum;
}

int main(int argc, char *argv[])
{
    // 演示用 async 在线程间传递结果
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    // auto可以自动推断变量的类型
    auto accumulate_future = std::async(std::launch::async, accumulate, numbers.begin(), numbers.end());
    std::cout << "result = " << accumulate_future.get() << '\n';

    return 0;
}
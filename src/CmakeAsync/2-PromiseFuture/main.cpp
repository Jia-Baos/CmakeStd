/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 使用promise传递被调用线程返回结果，通过共享状态变化通知调用线程已获得结果
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

void Accumulate(std::vector<int>::iterator first, std::vector<int>::iterator last,
                std::promise<int> accumulate_promise) {
  int sum = std::accumulate(first, last, 0);
  accumulate_promise.set_value(sum);  // 将结果存入，并让共享状态变为就绪以提醒future
}

int main(int argc, char *argv[]) {
  // 演示用 promise<int> 在线程间传递结果
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
  std::promise<int> accumulate_promise;
  std::future<int> accumulate_future = accumulate_promise.get_future();
  std::thread work_thread(Accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));
  accumulate_future.wait();  // 等待结果
  std::cout << "result = " << accumulate_future.get() << std::endl;
  work_thread.join();  // 阻塞等待线程执行完成

  return 0;
}

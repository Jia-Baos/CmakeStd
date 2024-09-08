/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 使用packaged_task传递被调用线程返回结果，通过共享状态变化通知调用线程已获得结果
 * @version 0.1
 * @date 2024-03-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <numeric>

int Accumulate(std::vector<int>::iterator first, std::vector<int>::iterator last) {
  int sum = std::accumulate(first, last, 0);
  return sum;
}

int main(int argc, char *argv[]) {
  // 演示用 packaged_task 在线程间传递结果
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
  std::packaged_task<int(std::vector<int>::iterator, std::vector<int>::iterator)> accumulate_task(Accumulate);
  std::future<int> accumulate_future = accumulate_task.get_future();
  std::thread work_thread(std::move(accumulate_task), numbers.begin(), numbers.end());
  accumulate_future.wait();  // 等待结果
  std::cout << "result = " << accumulate_future.get() << std::endl;
  work_thread.join();  // 阻塞等待线程执行完成

  return 0;
}

/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 使用全局变量传递被调用线程返回结果，使用条件变量通知调用线程已获得结果
 * @version 0.1
 * @date 2024-03-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>
#include <numeric>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int res = 0;                 // 保存结果的全局变量
std::mutex mtx;              // 互斥锁全局变量
std::condition_variable cv;  // 全局条件变量

void Accumulate(std::vector<int>::iterator first, std::vector<int>::iterator last) {
  int sum = std::accumulate(first, last, 0);
  std::unique_lock<std::mutex> locker(mtx);
  res = sum;
  locker.unlock();
  cv.notify_one();  // 向一个等待线程发出“条件已满足”的通知
}

int main(int argc, char *argv[]) {
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
  std::thread work_thread(Accumulate, numbers.begin(), numbers.end());

  std::unique_lock<std::mutex> locker(mtx);
  // 如果条件变量被唤醒，检查结果是否被改变，为真则直接返回，为假则继续等待
  cv.wait(locker, []() { return res; });
  std::cout << "result = " << res << std::endl;
  locker.unlock();
  work_thread.join();  // 阻塞等待线程执行完成

  return 0;
}

/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 原子操作
 * @version 0.1
 * @date 2024-03-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

int cnt;
std::atomic_int acnt;

void func() {
  for (size_t i = 0; i < 10000; ++i) {
    ++cnt;
    ++acnt;
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::jthread> pool;
  for (size_t i = 0; i < 10; ++i) {
    pool.emplace_back(func);
  }

  std::cout << "The atomic counter is " << acnt << std::endl;
  std::cout << "The non-atomic counter is " << cnt << std::endl;

  return 0;
}

/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 通过共享变量实现线程间通信
 * @version 0.1
 * @date 2024-03-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;         // 全局互斥锁
int flag_shared = 0;    // 共享变量
int flag_privated = 0;  // 私有变量

void task1() {
  mtx.lock();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  ++flag_shared;
  std::cout << "flag_shared: " << flag_shared << ", task1" << std::endl;
  mtx.unlock();
}

void task2() {
  while (true) {
    // 尝试获得锁，成功则修改 flag_shared
    if (mtx.try_lock()) {
      ++flag_shared;
      std::cout << "flag_shared: " << flag_shared << ", task2" << std::endl;
      mtx.unlock();
      return;
    } else {
      ++flag_privated;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "flag_privated: " << flag_privated << ", task2" << std::endl;
    }
  }
}

int main(int argc, char *argv[]) {
  std::thread([]() { task1(); }).join();
  std::thread([]() { task2(); }).join();

  return 0;
}

/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 通过加锁保证线程安全
 * @version 0.1
 * @date 2024-03-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // 全局互斥锁
volatile int tickets = 100;

void sellTickets(std::string name) {
  while (tickets > 0) {
    // 获取互斥锁
    mtx.lock();
    if (tickets > 0) {
      std::cout << name << " is selling tickets, " << tickets - 1 << " tickets reserved" << std::endl;
      --tickets;
    }

    // 释放互斥锁
    mtx.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main(int argc, const char *argv[]) {
  std::thread t1(sellTickets, "seller1");
  std::thread t2(sellTickets, "seller2");
  std::thread t3(sellTickets, "seller3");
  t1.join();
  t2.join();
  t3.join();
  return 0;
}
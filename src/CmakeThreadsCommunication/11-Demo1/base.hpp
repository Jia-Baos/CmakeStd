/**
 * @file base.hpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief
 * @version 0.1
 * @date 2024-03-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma
#ifndef BASE_HPP
#define BASE_HPP

#include <vector>
#include <atomic>
#include <thread>
#include <chrono>
#include <windows.h>

class Base {
 public:
  Base() = default;
  ~Base() = default;

  void run() {
    std::thread([this]() {
      // 等待获取线程
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));
      while (true) {
        if (!this->getStatus(1000)) {
          std::cout << "the val is too little" << std::endl;
          this->flag_ = false;
          continue;
        } else {
          this->flag_ = true;
        }
        std::cout << "flag status: " << std::boolalpha << this->flag_ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
    }).detach();

    std::thread([this]() { this->printStatus(); }).join();
  }

  bool getStatus(int val) {
    if (val < 100) {
      return false;
    }
    return true;
  }

  void printStatus() {
    while (true) {
      if (!this->flag_) {
        std::cout << "status is not ready" << std::endl;
        Sleep(100);
        continue;
      }
      while (true) {
        for (size_t i = 0; i < 3; ++i) {
          std::cout << "status is ready" << std::endl;
        }
        break;
      }
      Sleep(100);
    }
  }

 private:
  std::atomic<bool> flag_ = false;
};

#endif  // !BASE_HPP
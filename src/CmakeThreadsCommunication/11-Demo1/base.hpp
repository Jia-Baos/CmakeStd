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

#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>

class Base {
 public:
  Base() = default;
  ~Base() = default;

  void Run() {
    std::thread([this]() {
      // 等待获取线程
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));
      while (true) {
        if (!this->GetStatus(1000)) {
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

    std::thread([this]() { this->PrintStatus(); }).join();
  }

  bool GetStatus(int val) {
    if (val < 100) {
      return false;
    }
    return true;
  }

  void PrintStatus() {
    while (true) {
      if (!this->flag_) {
        std::cout << "status is not ready" << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        continue;
      }
      while (true) {
        for (size_t i = 0; i < 3; ++i) {
          std::cout << "status is ready" << std::endl;
        }
        break;
      }
      std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
  }

 private:
  std::atomic<bool> flag_ = false;
};

#endif  // !BASE_HPP

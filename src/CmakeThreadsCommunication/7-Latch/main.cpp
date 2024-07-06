/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 闩（latch）
 * @version 0.1
 * @date 2024-03-18
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * latch 类是一种 std::ptrdiff_t 类型的向下计数器，它能用于同步线程。
 * 在创建时初始化计数器的值。线程可能在闩上阻塞直至计数器减少到零。
 * 没有可能增加或重置计数器，这使得latch 成为一种单次使用的屏障。
 */

#include <functional>
#include <iostream>
#include <latch>
#include <string>
#include <thread>

struct Job {
  const std::string name;
  std::string product{"未工作"};
  std::thread acton{};
};

int main(int argc, char *argv[]) {
  // 初始化 Job 数组
  Job jobs[]{{"Annika"}, {"Buru"}, {"Chuck"}};

  std::latch work_done{std::size(jobs)};
  std::latch start_clean_up{1};

  auto work = [&](Job &my_job) {
    my_job.product = my_job.name + " worked";   // 第一个任务
    work_done.count_down();                     // 以不阻塞的方式减少计数器
    start_clean_up.wait();                      // 阻塞直至计数器抵达零
    my_job.product = my_job.name + " cleaned";  // 第二个任务
  };

  std::cout << "Work is starting... ";
  for (auto &job : jobs) {
    // 执行jobs中的action
    job.acton = std::thread{work, std::ref(job)};
  }

  work_done.wait();  // 阻塞主线程，jobs中的"worked"执行完之后work_done失效，之后jobs中的action被阻塞
  std::cout << "done: " << std::endl;
  for (auto &job : jobs) {
    std::cout << "  " << job.product << std::endl;
  }

  std::cout << "Workers are cleaning up... ";
  start_clean_up.count_down();  // jobs中的action开始执行"cleaned"
  for (auto &job : jobs) {
    // 等待jobs中action全部结束
    job.acton.join();
  }

  std::cout << "Done: " << std::endl;
  for (auto &job : jobs) {
    std::cout << "  " << job.product << std::endl;
  }
}

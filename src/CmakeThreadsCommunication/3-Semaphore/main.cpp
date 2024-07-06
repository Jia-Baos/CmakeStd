/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 通过信号量唤醒线程
 * @version 0.1
 * @date 2024-03-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>

std::counting_semaphore csem(0);
std::binary_semaphore bsem(0);

// semaphore acquire = condition_variable wait
// semaphore release = condition_variable notify
void task(int idx) {
  std::cout << "task " << idx << ": ready to receive signal" << std::endl;
  csem.acquire();  // 若内部计数器大于 ​0​ 则尝试将它减少 1；否则阻塞直至它大于 ​0​
                   // 且能成功减少内部计数器
  std::cout << "task " << idx << ": has received signal" << std::endl;
}

int main(int argc, const char *argv[]) {
  std::thread t1(task, 1);
  std::thread t2(task, 2);
  std::thread t3(task, 3);
  std::thread t4(task, 4);
  std::thread t5(task, 5);

  std::cout << "main: ready to signal, release" << std::endl;
  csem.release(3);  // 发出信号后，速度最快的三个线程得到信号并执行任务，之后由于内部计数器为0，剩余task继续阻塞
  std::cout << "main: signal end" << std::endl;

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();

  return 0;
}
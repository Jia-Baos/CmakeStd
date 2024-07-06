/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 通过promise和future实现线程间通信
 * @version 0.1
 * @date 2024-03-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void connect1(std::promise<bool> &flag) {
  std::this_thread::sleep_for(std::chrono::seconds(1));

  flag.set_value(true);
  // std::cout << "Set the flag to true " << std::endl;
}

void connect2(std::future<bool> &flag) {
  std::cout << "Status of valid(): " << flag.valid() << ", before get()" << std::endl;

  auto flag_tmp = flag.get();

  std::cout << "Status of valid(): " << flag.valid() << ", after get()" << std::endl;
}

int main(int argc, char *argv[]) {
  // 声明一个std::promise对象pr1，其保存的值类型为int
  std::promise<bool> pr1;
  // 声明一个std::future对象fu1，并通过std::promise的get_future()函数与pr1绑定
  std::future<bool> fu1 = pr1.get_future();

  // 创建一个线程t1，将函数Thread_Fun1及对象pr1放在线程里面执行
  std::thread t1(connect1, std::ref(pr1));
  // 创建一个线程t2，将函数Thread_Fun2及对象fu1放在线程里面执行
  std::thread t2(connect2, std::ref(fu1));

  // 阻塞至线程结束
  t1.detach();
  t2.join();

  return 0;
}

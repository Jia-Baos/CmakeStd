/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 屏障（barrier），MinGW13.2下无法执行（不支持or实现有问题），MSVC则OK
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * 类模板 std::barrier 提供一种线程协调机制，阻塞已知大小的线程组直至该组中的所有线程到达该屏障。不同于
 * std::latch，屏障是可重用的：一旦到达的线程组被除阻，即可重用同一屏障。与
 * std::latch不同，会在线程除阻前执行一个可能为空的可调用对象。
 *
 * 屏障对象的生存期由一个或多个屏障阶段组成。每个阶段定义一个阻塞线程的阶段同步点。线程可以抵达屏障，但通过调用 arrive
 * 来推迟它在阶段同步点上的等待。这样的线程可以随后再通过调用 wait 在阶段同步点上阻塞。
 *
 * 屏障阶段由以下步骤组成：
 *    1. 每次调用 arrive 或 arrive_and_drop 减少期待计数。
 *    2. 期待计数抵达零时，运行阶段完成步骤，即调用 CompletionFunction，并除阻所有在阶段同步点上阻塞的线程。
 *      完成步骤的结束强先发生于所有从完成步骤所除阻的调用的返回。在期待计数抵达零后，一个线程会在其调用
 *      arrive、arrive_and_drop 或 wait 的过程中执行完成步骤恰好一次， 但如果没有线程调用 wait
 *       则是否执行完成步骤为实现定义。
 *    3. 完成步骤结束时，重置期待计数为构造中指定的值，它可能为 arrive_and_drop 调用所调整，自此开始下一阶段。
 * barrier 除了析构函数外的成员函数的并发调用不会引入数据竞争。
 */

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <barrier>
#include <syncstream>

int main(int argc, char* argv[]) {
  std::cout << __cplusplus << std::endl;
  const auto workers = {"Anil", "Busara", "Carl"};

  auto on_completion = []() noexcept {
    // locking not needed here
    static auto phase =
        "... done\n"
        "Cleaning up...\n";
    std::cout << phase;
    phase = "... done\n";
  };

  std::barrier sync_point(std::ssize(workers), on_completion);

  auto work = [&](std::string name) {
    std::string product = "  " + name + " worked\n";
    std::osyncstream(std::cout) << product;  // ok, op<< call is atomic
    sync_point.arrive_and_wait();

    product = "  " + name + " cleaned\n";
    std::osyncstream(std::cout) << product;
    sync_point.arrive_and_wait();
  };

  std::cout << "Starting...\n";
  std::vector<std::jthread> threads;
  threads.reserve(std::size(workers));
  for (auto const& worker : workers) {
    threads.emplace_back(work, worker);
  }
}

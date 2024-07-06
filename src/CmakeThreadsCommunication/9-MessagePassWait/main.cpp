/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 消息队列示例，等待消息
 * @version 0.1
 * @date 2024-03-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <thread>
#include "./message_queue.hpp"

class MyMessage {
 public:
  int type;
  void *param1;
  void *param2;
};

int main(int argc, char *argv[]) {
  // 初始化消息队列
  MessageQueue<MyMessage> mq;
  // 启动线程
  std::thread t1([&]() {
    MyMessage msg;
    while (true) {
      // 等待队列的消息
      mq.wait(msg);
      printf("receive message type:%d\n", msg.type);
      if (msg.type == 1001) {
        break;
      }
    }
    printf("thread exited\n");
  });

  // 发送消息给线程
  MyMessage msg;
  printf("send number message to thread.1001 exit\n");
  while (true) {
    scanf("%d", &msg.type);
    mq.push(msg);
    if (msg.type == 1001) break;
  }
  t1.join();
  return 0;
}
/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief Event测试，尚有bug
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./event.hpp"

int main(int argc, char *argv[]) {
  TestClass testObj;

  std::cout << "---------------first begin---------------" << std::endl;
  testObj.execute();
  testObj.stop();
  std::cout << "---------------after delete---------------" << std::endl;
  testObj.execute();

  return 0;
}
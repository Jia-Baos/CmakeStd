#include <iostream>
#ifdef _WIN64
#include <windows.h>
#elif _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif
#include "../MiniCircle/MiniCircle.hpp"

int main(int argc, char *argv[]) {
  std::cout << "hello world" << std::endl;

  MyVector p1(2.0, 2.0);
  MyVector v1(1.0, 1.0);
  MyVector p2(2.0, -2.0);
  MyVector v2(1.0, -1.0);
  MyVector p3(0.0, 0.0);

  double value;
  Circle circle;
  std::pair<double, double> result;
  std::pair<MyVector, MyVector> combination;

  // 加法测试
  result = p1 + p2;
  std::cout << "(2.0,2.0) + (2.0,-2.0): " << result.my_x << " " << result.my_y << std::endl;

  // 减法测试
  result = p1 - p2;
  std::cout << "(2.0,2.0) - (2.0,-2.0): " << result.my_x << " " << result.my_y << std::endl;

  // 叉乘测试
  value = p1 * p2;
  std::cout << "(2.0,2.0) * (2.0,-2.0): " << value << std::endl;

  // 数乘测试
  result = p1 * 1.0;
  std::cout << "(2.0,2.0) * 1.0: " << result.my_x << " " << result.my_y << std::endl;

  // 除法测试
  result = p1 / 1.0;
  std::cout << "(2.0,2.0) / 1.0: " << result.my_x << " " << result.my_y << std::endl;

  // Judge函数测试
  value = Judge(2.0, 3.0);
  std::cout << "2.0, 3.0 (-1 means not int circle): " << value << std::endl;

  // 向量旋转测试
  result = Rotate(v1, PI / 2);
  std::cout << "(1.0,1.0) rotate PI/2: " << result.my_x << " " << result.my_y << std::endl;

  // 两点之间距离测试
  value = Distance(p1, p2);
  std::cout << "(2.0,2.0) (2.0,-2.0) Distance: " << value << std::endl;

  // 两直线之间交点测试
  result = Intersection(p1, v1, p2, v2);
  std::cout << "p1(2.0,2.0), v1(1.0,1.0), p2(2.0,-2.0), v2(1.0,-1.0) Cross Point: " << result.my_x << " " << result.my_y
            << std::endl;

  // 两点之间中垂线测试
  combination = MidPerpendicular(p1, p2);
  std::cout << "p1(2.0,2.0), p2(2.0,-2.0) Mid Perpendicular: " << "Point: " << combination.my_x.my_x << " "
            << combination.my_x.my_y << " Vec: " << combination.my_y.my_x << " " << combination.my_y.my_y << std::endl;

  // 三点外接圆测试
  circle = MiniCircle(p1, p2, p3);
  std::cout << "p1(2.0,2.0), p2(2.0,-2.0), p3(0.0,0.0) Mini Circle: " << "Point: " << circle.center.my_x << " "
            << circle.center.my_y << " Radius: " << circle.radius << std::endl;

  Sleep(1000);

  return 0;
}

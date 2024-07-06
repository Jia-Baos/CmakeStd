#include "../src/MiniCircle/MiniCircle.hpp"
#include "gtest/gtest.h"

MyVector p1(2.0, 2.0);
MyVector v1(1.0, 1.0);
MyVector p2(2.0, -2.0);
MyVector v2(1.0, -1.0);
MyVector p3(0.0, 0.0);

double value;
Circle circle;
std::pair<double, double> result;
std::pair<MyVector, MyVector> combination;

TEST(test_mini_circle, test1) {
  // 加法测试
  result = p1 + p2;
  ASSERT_EQ(result, MyVector(4.0, 0.0));
}

TEST(test_mini_circle, test2) {
  // 减法测试
  result = p1 - p2;
  ASSERT_EQ(result, MyVector(0.0, 4.0));
}

TEST(test_mini_circle, test3) {
  // 叉乘测试
  value = p1 * p2;
  ASSERT_EQ(value, -8.0);
}

TEST(test_mini_circle, test4) {
  // 数乘测试
  result = p1 * 1.0;
  ASSERT_EQ(result, MyVector(2.0, 2.0));
}

TEST(test_mini_circle, test5) {
  // 除法测试
  result = p1 / 1.0;
  ASSERT_EQ(result, MyVector(2.0, 2.0));
}

TEST(test_mini_circle, test6) {
  // Judge函数测试
  value = Judge(2.0, 3.0);
  ASSERT_EQ(value, -1);
}

TEST(test_mini_circle, test7) {
  // 向量旋转测试
  result = Rotate(v1, PI / 2);
  ASSERT_EQ(result, MyVector(1.0, -1.0));
}

TEST(test_mini_circle, test8) {
  // 两点之间距离测试
  value = Distance(p1, p2);
  ASSERT_EQ(value, 4.0);
}

TEST(test_mini_circle, test9) {
  // 两直线之间交点测试
  result = Intersection(p1, v1, p2, v2);
  ASSERT_EQ(result, MyVector(0.0, 0.0));
}

TEST(test_mini_circle, test10) {
  // 两点之间中垂线测试
  combination = MidPerpendicular(p1, p2);
  ASSERT_EQ(combination.my_x, MyVector(2.0, 0.0));
  ASSERT_EQ(combination.my_y, MyVector(-4.0, 0.0));
}

TEST(test_mini_circle, test11) {
  // 三点外接圆测试
  circle = MiniCircle(p1, p2, p3);
  ASSERT_EQ(circle.center, MyVector(2.0, 0.0));
  ASSERT_EQ(circle.radius, 2.0);
}
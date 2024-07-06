#pragma once
#ifndef MINICIRCLE_HPP
#define MINICIRCLE_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

const int N = 100010;
const double eps = 1e-6;
const double PI = 3.1415926;

#define my_x first
#define my_y second
using MyVector = std::pair<double, double>;

/* 此处符号重载必须inline */
// 重载+号运算符
inline MyVector operator+(const MyVector &p1, const MyVector &p2) { return {p1.my_x + p2.my_x, p1.my_y + p2.my_y}; }

// 重载-号运算符
inline MyVector operator-(const MyVector &p1, const MyVector &p2) { return {p1.my_x - p2.my_x, p1.my_y - p2.my_y}; }

// 叉乘
inline double operator*(const MyVector &p1, const MyVector &p2) { return {p1.my_x * p2.my_y - p1.my_y * p2.my_x}; }

// 数乘
inline MyVector operator*(const MyVector &p1, const double a) { return {p1.my_x * a, p1.my_y * a}; }

// 除法
inline MyVector operator/(const MyVector &p1, const double a) { return {p1.my_x / a, p1.my_y / a}; }

struct Circle {
  MyVector center;
  double radius;
  Circle() : center(std::pair<double, double>(0.0, 0.0)), radius(0) {}
  Circle(const std::pair<double, double> &center, const double radius) : center(center), radius(radius) {}
};

// 判断半径大小
int Judge(const double a, const double b);

// 向量旋转，a表示顺时针旋转的弧度值
MyVector Rotate(const MyVector &p1, const double a);

// 求两点之间距离
double Distance(const MyVector &p1, const MyVector &p2);

// 求两直线的交点
MyVector Intersection(const MyVector &p1, const MyVector &v1, const MyVector &p2, const MyVector &v2);

// 求两点之间连线的中垂线
std::pair<MyVector, MyVector> MidPerpendicular(const MyVector &p1, const MyVector &p2);

// 已知三点求外接圆
Circle MiniCircle(MyVector p1, MyVector p2, MyVector p3);

// 最小覆盖圆
Circle MinimumCoveringCircle(const std::vector<MyVector> &points, const int npoints);

#endif  // !MINICIRCLE_HPP

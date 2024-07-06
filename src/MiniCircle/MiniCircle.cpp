#include "./MiniCircle.hpp"

// 判断半径大小
int Judge(const double a, const double b) {
  if (std::abs(a - b) < eps) {
    return 0;
  }
  if (a < b) {
    return -1;
  }
  return 1;
}

// 向量旋转，a表示顺时针旋转的弧度值
MyVector Rotate(const MyVector &p1, const double a) {
  return {p1.my_x * cos(a) + p1.my_y * sin(a), -p1.my_x * sin(a) + p1.my_y * cos(a)};
}

// 求两点之间距离
double Distance(const MyVector &p1, const MyVector &p2) {
  const double dx = p1.my_x - p2.my_x;
  const double dy = p1.my_y - p2.my_y;
  return std::sqrt(dx * dx + dy * dy);
}

// 求两直线的交点
MyVector Intersection(const MyVector &p1, const MyVector &v1, const MyVector &p2, const MyVector &v2) {
  MyVector result;
  if (v1 * v2 != 0) {
    const MyVector temp = p1 - p2;
    const double ratio = (v2 * temp) / (v1 * v2);
    result = p1 + v1 * ratio;
  }
  return result;
}

// 求两点之间连线的中垂线
std::pair<MyVector, MyVector> MidPerpendicular(const MyVector &p1, const MyVector &p2) {
  const MyVector mid = (p1 + p2) / 2;
  // 垂直时再利用旋转求解会降低精度
  // const MyVector rotate = Rotate(p1 - p2, PI / 2);
  const MyVector rotate = {-p1.my_y + p2.my_y, p1.my_x - p2.my_x};
  return {mid, rotate};
}

// 已知三点求外接圆
Circle MiniCircle(MyVector p1, MyVector p2, MyVector p3) {
  auto m1 = MidPerpendicular(p1, p2);
  auto m2 = MidPerpendicular(p1, p3);
  MyVector center_point = Intersection(m1.my_x, m1.my_y, m2.my_x, m2.my_y);
  double radius = Distance(center_point, p1);
  return {center_point, radius};
}

Circle MinimumCoveringCircle(const std::vector<MyVector> &points, const int npoints) {
  // 初始化圆，圆心为points[0]，半径为0
  Circle circle(points[0], 0.0);
  for (int i = 1; i < npoints; i++) {
    if (Judge(circle.radius, Distance(circle.center, points[i])) == -1) {
      // 如果points[i]在圆的外部，重新指定圆心的位置
      circle = {points[i], 0};
      for (int j = 0; j < i; j++) {
        if (Judge(circle.radius, Distance(circle.center, points[j])) == -1) {
          // 如果points[j]在圆的外部，利用points[i]，points[j]生成一个最小圆
          circle = {(points[i] + points[j]) / 2, Distance(points[i], points[j]) / 2};
          for (int k = 0; k < j; k++) {
            // 如果points[k]在圆的外部，利用points[i]，points[j]，points[k]生成一个最小圆
            if (Judge(circle.radius, Distance(circle.center, points[k])) == -1) {
              circle = MiniCircle(points[i], points[j], points[k]);
            }
          }
        }
      }
    }
  }
  return circle;
}
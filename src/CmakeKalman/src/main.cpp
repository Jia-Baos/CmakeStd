#include <fstream>
#include <iostream>

#include "./kalman_utils/kalman.hpp"
#define N 1000
#define T 0.01

double Func(double &x);
double data_x[N], data_y[N];

double Func(double &x) {
  double res = 5 * x * x;
  return res;
}

float Sample(float x0, float v0, float acc, float t) { return x0 + v0 * t + 1 / 2 * acc * t * t; }

float GetRand() { return 0.5 * rand() / RAND_MAX - 0.25; }

int main() {
  std::ofstream fout;
  fout.open("data.txt");
  float t;
  for (int i = 0; i < N; i++) {
    /*data_x[i] = i*T*10;
    data_y[i] = func(data_x[i]);*/
    t = i * T;
    data_x[i] = Sample(0, -4, 0, t) + GetRand();
    data_y[i] = Sample(0, 6.5, 0, t) + GetRand();
  }
  int state_size = 6;
  int meas_size = 2;
  int control_size = 0;
  KalmanFilter kf(state_size, meas_size, control_size);

  // 初始化状态转移矩阵
  Eigen::MatrixXd a(state_size, state_size);
  a << 1, 0, T, 0, 1 / 2 * T * T, 0, 0, 1, 0, T, 0, 1 / 2 * T * T, 0, 0, 1, 0, T, 0, 0, 0, 0, 1, 0, T, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 1;
  // cout << A;

  // 初始化控制输入矩阵
  Eigen::MatrixXd b(0, 0);

  // 初始化状态观测矩阵
  Eigen::MatrixXd h(meas_size, state_size);
  h << 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0;
  // cout << H;

  // 初始化当前状态、控制输入、当前观测结果
  Eigen::VectorXd x(state_size);
  Eigen::VectorXd u(0);
  Eigen::VectorXd z(meas_size);
  z.setZero();

  // 初始化过程噪声和测量噪声
  Eigen::MatrixXd q(state_size, state_size);
  q.setIdentity() * 0.001;
  Eigen::MatrixXd r(meas_size, meas_size);
  r.setIdentity() * 0.01;

  // 初始化协方差矩阵
  Eigen::MatrixXd p(state_size, state_size);
  p.setIdentity();

  // 初始化当前预测结果
  Eigen::VectorXd res(state_size);

  for (int i = 0; i < N; i++) {
    // cout << "state_" << i << ":\n";
    if (i == 0) {
      x << data_x[i], data_y[i], 0, 0, 0, 0;
      kf.Init(x, p, r, q);
    }
    res << kf.Predict(a);
    z << data_x[i], data_y[i];
    kf.Update(h, z);
    fout << data_x[i] << " " << res[0] << " " << data_y[i] << " " << res[1] << " " << res[2] << " " << res[3] << " "
         << res[4] << " " << res[5] << std::endl;
  }
  fout.close();
  std::cout << "Done, use python script to draw the figure...." << std::endl;
  return 0;
}

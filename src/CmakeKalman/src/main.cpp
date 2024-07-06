#include "./kalman/kalman.hpp"
#include <fstream>
#include <iostream>

#define N 1000
#define T 0.01

double func(double &x);
double data_x[N], data_y[N];

double func(double &x) {
  double res = 5 * x * x;
  return res;
}

float sample(float x0, float v0, float acc, float t) {
  return x0 + v0 * t + 1 / 2 * acc * t * t;
}

float GetRand() { return 0.5 * rand() / RAND_MAX - 0.25; }

int main() {
  std::ofstream fout;
  fout.open("data.txt");
  float t;
  for (int i = 0; i < N; i++) {
    /*data_x[i] = i*T*10;
    data_y[i] = func(data_x[i]);*/
    t = i * T;
    data_x[i] = sample(0, -4, 0, t) + GetRand();
    data_y[i] = sample(0, 6.5, 0, t) + GetRand();
  }
  int stateSize = 6;
  int measSize = 2;
  int controlSize = 0;
  KalmanFilter kf(stateSize, measSize, controlSize);

  // 初始化状态转移矩阵
  Eigen::MatrixXd A(stateSize, stateSize);
  A << 1, 0, T, 0, 1 / 2 * T * T, 0, 0, 1, 0, T, 0, 1 / 2 * T * T, 0, 0, 1, 0,
      T, 0, 0, 0, 0, 1, 0, T, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1;
  // cout << A;

  // 初始化控制输入矩阵
  Eigen::MatrixXd B(0, 0);

  // 初始化状态观测矩阵
  Eigen::MatrixXd H(measSize, stateSize);
  H << 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0;
  // cout << H;

  // 初始化当前状态、控制输入、当前观测结果
  Eigen::VectorXd x(stateSize);
  Eigen::VectorXd u(0);
  Eigen::VectorXd z(measSize);
  z.setZero();

  // 初始化过程噪声和测量噪声
  Eigen::MatrixXd Q(stateSize, stateSize);
  Q.setIdentity() * 0.001;
  Eigen::MatrixXd R(measSize, measSize);
  R.setIdentity() * 0.01;

  //  初始化协方差矩阵
  Eigen::MatrixXd P(stateSize, stateSize);
  P.setIdentity();

  // 初始化当前预测结果
  Eigen::VectorXd res(stateSize);

  for (int i = 0; i < N; i++) {
    // cout << "state_" << i << ":\n";
    if (i == 0) {
      x << data_x[i], data_y[i], 0, 0, 0, 0;
      kf.init(x, P, R, Q);
    }
    res << kf.predict(A);
    z << data_x[i], data_y[i];
    kf.update(H, z);
    fout << data_x[i] << " " << res[0] << " " << data_y[i] << " " << res[1]
         << " " << res[2] << " " << res[3] << " " << res[4] << " " << res[5]
         << std::endl;
  }
  fout.close();
  std::cout << "Done, use python script to draw the figure...." << std::endl;
  return 0;
}

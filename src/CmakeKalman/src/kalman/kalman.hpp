//
// Created by fx50j on 2024/1/25.
//

#pragma
#ifndef KALMAN_HPP
#define  KALMAN_HPP

#include <Eigen/Dense>
#include <iostream>

class KalmanFilter {
private:
  int stateSize; // state variable's dimenssion
  int measSize;  // measurement variable's dimession
  int uSize;     // control variables's dimenssion

  Eigen::MatrixXd A; // 状态转移矩阵
  Eigen::VectorXd x; // 系统状态矩阵
  Eigen::MatrixXd B; // 控制输入矩阵
  Eigen::VectorXd u; // 控制输入
  Eigen::VectorXd z; // 系统状态矩阵的观测结果
  Eigen::MatrixXd H; // 状态观测矩阵
  Eigen::MatrixXd Q; // process noise covariance
  Eigen::MatrixXd R; // measurement noise covariance
  Eigen::MatrixXd P; // coveriance
public:
  KalmanFilter(int stateSize_, int measSize_, int uSize_);
  ~KalmanFilter() {}
  void init(Eigen::VectorXd &x_, Eigen::MatrixXd &P_, Eigen::MatrixXd &R_,
            Eigen::MatrixXd &Q_);
  Eigen::VectorXd predict(Eigen::MatrixXd &A_);
  Eigen::VectorXd predict(Eigen::MatrixXd &A_, Eigen::MatrixXd &B_,
                          Eigen::VectorXd &u_);
  void update(Eigen::MatrixXd &H_, Eigen::VectorXd z_meas);
};

#endif //  KALMAN_HPP

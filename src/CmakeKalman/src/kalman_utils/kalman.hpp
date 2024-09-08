//
// Created by fx50j on 2024/1/25.
//

#pragma once
#ifndef KALMAN_HPP
#define KALMAN_HPP

#include <iostream>
#include <Eigen/Dense>

class KalmanFilter {
 private:
  int state_size_;  // state variable's dimenssion
  int meas_size_;   // measurement variable's dimession
  int u_size_;      // control variables's dimenssion

  Eigen::MatrixXd a_;  // 状态转移矩阵
  Eigen::VectorXd x_;  // 系统状态矩阵
  Eigen::MatrixXd b_;  // 控制输入矩阵
  Eigen::VectorXd u_;  // 控制输入
  Eigen::VectorXd z_;  // 系统状态矩阵的观测结果
  Eigen::MatrixXd h_;  // 状态观测矩阵
  Eigen::MatrixXd q_;  // process noise covariance
  Eigen::MatrixXd r_;  // measurement noise covariance
  Eigen::MatrixXd p_;  // coveriance
 public:
  KalmanFilter(int state_size, int meas_size, int u_size);
  ~KalmanFilter() {}
  void Init(Eigen::VectorXd &x_, Eigen::MatrixXd &P_, Eigen::MatrixXd &R_, Eigen::MatrixXd &Q_);
  Eigen::VectorXd Predict(Eigen::MatrixXd &A_);
  Eigen::VectorXd Predict(Eigen::MatrixXd &A_, Eigen::MatrixXd &B_, Eigen::VectorXd &u_);
  void Update(Eigen::MatrixXd &H_, Eigen::VectorXd z_meas);
};

#endif  // KALMAN_HPP

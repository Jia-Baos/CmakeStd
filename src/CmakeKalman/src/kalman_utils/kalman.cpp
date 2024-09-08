//
// Created by fx50j on 2024/1/25.
//

#include "./kalman.hpp"

KalmanFilter::KalmanFilter(int state_size, int meas_size, int u_size)
    : state_size_(state_size), meas_size_(meas_size), u_size_(u_size) {
  if (state_size == 0 || state_size == 0) {
    std::cout << "Error, State size and measurement size must bigger than 0\n";
  }

  x_.resize(state_size_);
  x_.setZero();

  a_.resize(state_size_, state_size_);
  a_.setIdentity();

  u_.resize(u_size_);
  u_.transpose();
  u_.setZero();

  b_.resize(state_size_, u_size_);
  b_.setZero();

  p_.resize(state_size_, state_size_);
  p_.setIdentity();

  h_.resize(meas_size_, state_size_);
  h_.setZero();

  z_.resize(meas_size_);
  z_.setZero();

  q_.resize(state_size_, state_size_);
  q_.setZero();

  r_.resize(meas_size_, meas_size_);
  r_.setZero();
}

void KalmanFilter::Init(Eigen::VectorXd &x, Eigen::MatrixXd &p, Eigen::MatrixXd &r, Eigen::MatrixXd &q) {
  x_ = x;
  p_ = p;
  r_ = r;
  q_ = q;
}
Eigen::VectorXd KalmanFilter::Predict(Eigen::MatrixXd &a, Eigen::MatrixXd &b, Eigen::VectorXd &u) {
  a_ = a;
  b_ = b;
  u_ = u;
  x_ = a_ * x_ + b_ * u_;
  Eigen::MatrixXd a_t = a_.transpose();
  p_ = a_ * p_ * a_t + q_;
  return x_;
}

Eigen::VectorXd KalmanFilter::Predict(Eigen::MatrixXd &a) {
  a_ = a;
  x_ = a_ * x_;
  Eigen::MatrixXd a_t = a_.transpose();
  p_ = a_ * p_ * a_t + q_;
  //	cout << "P-=" << P<< endl;
  return x_;
}

void KalmanFilter::Update(Eigen::MatrixXd &h, Eigen::VectorXd z_meas) {
  h_ = h;
  Eigen::MatrixXd temp1, temp2, ht;
  ht = h_.transpose();
  temp1 = h_ * p_ * ht + r_;
  temp2 = temp1.inverse();  //(H*P*H'+R)^(-1)
  Eigen::MatrixXd k = p_ * ht * temp2;
  z_ = h_ * x_;
  x_ = x_ + k * (z_meas - z_);
  Eigen::MatrixXd i = Eigen::MatrixXd::Identity(state_size_, state_size_);
  p_ = (i - k * h_) * p_;
  //	cout << "P=" << P << endl;
}

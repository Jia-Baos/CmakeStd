#pragma once

#ifndef SRC_RECEIVER_HPP
#define SRC_RECEIVER_HPP

#include <string>

class Receiver {
 public:
  Receiver();
  virtual ~Receiver();
  virtual void RecvMessage(std::string message) = 0;
};

#endif  // SRC_RECEIVER_HPP

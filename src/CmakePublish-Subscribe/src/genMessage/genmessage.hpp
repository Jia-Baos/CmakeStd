#pragma once

#ifndef SRC_GENMESSAGE_HPP
#define SRC_GENMESSAGE_HPP
#include "../Notifier/notifier.hpp"

class GenMessage : public Notifier {
 public:
  GenMessage();
  virtual ~GenMessage();
  void ThrowMessage(std::string message);
};

#endif  // SRC_GENMESSAGE_HPP

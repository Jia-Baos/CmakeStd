#pragma once

#ifndef SRC_NOTIFIER_HPP
#define SRC_NOTIFIER_HPP

#include <string>
#include <vector>
#include "../Receiver/receiver.hpp"

class Notifier {
 public:
  Notifier();
  virtual ~Notifier();

  void LoadReceiver(Receiver *pRecv);
  void SendToAllRecv(std::string message);

 private:
  std::vector<Receiver *> observer_list_;
};

#endif  // SRC_NOTIFIER_HPP

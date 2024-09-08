#pragma

#ifndef SRC_GETMESSAGE_HPP
#define SRC_GETMESSAGE_HPP

#include "../Receiver/receiver.hpp"

class GetMessage : public Receiver {
 public:
  GetMessage();
  virtual ~GetMessage();

  virtual void RecvMessage(std::string message);
};

#endif  // SRC_GETMESSAGE_HPP

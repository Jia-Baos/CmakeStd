#include "./notifier.hpp"

Notifier::Notifier() {}

Notifier::~Notifier() {}

void Notifier::LoadReceiver(Receiver *pRecv) { observer_list_.push_back(pRecv); }

void Notifier::SendToAllRecv(std::string message) {
  for (auto it : observer_list_) {
    (*it).RecvMessage(message);
  }
}

#include "./notifier.hpp"

notifier::notifier() {}

notifier::~notifier() {}

void notifier::loadReceiver(receiver *pRecv)
{
    observer_list_.push_back(pRecv);
}

void notifier::sendToAllRecv(std::string message)
{
    for (auto it : observer_list_)
    {
        (*it).recvMessage(message);
    }
}
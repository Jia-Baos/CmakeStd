#pragma once

#ifndef SRC_NOTIFIER_HPP
#define SRC_NOTIFIER_HPP

#include <vector>
#include <string>
#include "../Receiver/receiver.hpp"

class notifier
{
public:
    notifier();
    virtual ~notifier();

    void loadReceiver(receiver *pRecv);
    void sendToAllRecv(std::string message);

private:
    std::vector<receiver *> observer_list_;
};

#endif // SRC_NOTIFIER_HPP
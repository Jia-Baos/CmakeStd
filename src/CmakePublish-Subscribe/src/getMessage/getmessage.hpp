#pragma

#ifndef SRC_GETMESSAGE_HPP
#define SRC_GETMESSAGE_HPP

#include "../Receiver/receiver.hpp"

class getMessage : public receiver
{
public:
    getMessage();
    virtual ~getMessage();

    virtual void recvMessage(std::string message);
};

#endif // SRC_GETMESSAGE_HPP
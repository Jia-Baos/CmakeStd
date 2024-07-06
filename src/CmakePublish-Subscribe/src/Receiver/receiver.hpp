#pragma once

#ifndef SRC_RECEIVER_HPP
#define SRC_RECEIVER_HPP

#include <iostream>
#include <vector>
#include <string>

class receiver
{
public:
    receiver();
    virtual ~receiver();
    virtual void recvMessage(std::string message) = 0;
};

#endif // SRC_RECEIVER_HPP
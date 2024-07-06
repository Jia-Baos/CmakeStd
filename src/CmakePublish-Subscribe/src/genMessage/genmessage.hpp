#pragma once

#ifndef SRC_GENMESSAGE_HPP
#define SRC_GENMESSAGE_HPP
#include "../Notifier/notifier.hpp"

class genMessage : public notifier
{
public:
    genMessage();
    virtual ~genMessage();
    void throwMessage(std::string message);
};

#endif // SRC_GENMESSAGE_HPP
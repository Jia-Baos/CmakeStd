#include "./genmessage.hpp"

genMessage::genMessage() {}

genMessage::~genMessage() {}

void genMessage::throwMessage(std::string message)
{
    sendToAllRecv(message);
}
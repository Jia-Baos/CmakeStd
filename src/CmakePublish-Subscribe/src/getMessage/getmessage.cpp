#include "./getmessage.hpp"

getMessage::getMessage() {}

getMessage::~getMessage() {}

void getMessage::recvMessage(std::string message)
{
    std::cout << "one receiver receive: " << message << std::endl;
}
#include "./getmessage.hpp"

#include <iostream>

GetMessage::GetMessage() {}

GetMessage::~GetMessage() {}

void GetMessage::RecvMessage(std::string message) { std::cout << "one receiver receive: " << message << std::endl; }

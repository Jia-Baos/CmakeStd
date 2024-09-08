#include "./genmessage.hpp"

GenMessage::GenMessage() {}

GenMessage::~GenMessage() {}

void GenMessage::ThrowMessage(std::string message) { SendToAllRecv(message); }

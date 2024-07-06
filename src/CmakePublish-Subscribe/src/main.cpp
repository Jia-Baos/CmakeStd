#include <iostream>
#include "./genMessage/genmessage.hpp"
#include "./getMessage/getmessage.hpp"

int main(int argc, char *argv[])
{

    genMessage notifier;
    getMessage receiver1;
    getMessage receiver2;

    notifier.loadReceiver(&receiver1);
    notifier.loadReceiver(&receiver2);

    notifier.sendToAllRecv("here it is");

    return 0;
}

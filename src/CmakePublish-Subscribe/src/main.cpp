#include "./genMessage/genmessage.hpp"
#include "./getMessage/getmessage.hpp"

int main(int argc, char *argv[]) {
  GenMessage notifier;
  GetMessage receiver1;
  GetMessage receiver2;

  notifier.LoadReceiver(&receiver1);
  notifier.LoadReceiver(&receiver2);

  notifier.SendToAllRecv("here it is");

  return 0;
}

#include <iostream>
#include "./producer_consumer_utils/producerConsumer.hpp"

int main(int argc, char *argv[]) {
  std::cout << "Hello world..." << std::endl;

  ProducerConsumer<int> procuder_consumer(6, 6, 6);
  while (true) {
  }
}

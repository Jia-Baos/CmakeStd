#include <iostream>
#include "./producerConsumer/producerConsumer.hpp"

int main(int argc, char *argv[])
{

    std::cout << "Hello world..." << std::endl;

    ProducerConsumer<int> procuderConsumer(100, 6, 6);
    while (true)
    {
    }
}

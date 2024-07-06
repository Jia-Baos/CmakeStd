#include <iostream>
#include <format>
#include <string>
#include "./task.hpp"
#include "./scheduler.hpp"

coro::task printNumber(std::string prefix, int val)
{
    for (size_t i = 0; i < val; ++i)
    {
        std::cout << std::format("{}: {}", prefix, i) << std::endl;
        co_await std::suspend_always{};
    }
}

int main(int argc, char *argv[])
{
    auto task1 = printNumber("A", 5);
    auto task2 = printNumber("B", 3);
    auto task3 = printNumber("C", 1);

    coro::scheduler sche;
    sche.schedule(task1);
    sche.schedule(task2);
    sche.schedule(task3);

    sche.run();

    return 0;
}
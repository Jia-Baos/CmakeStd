#include <format>
#include <iostream>
#include "./task.hpp"

coro::task printNumbers(int val)
{
    for (size_t i = 0; i < val; ++i)
    {
        std::cout << std::format("val: {}", i) << std::endl;
        co_await std::suspend_always{};
    }

    co_return val * 2;
}

int main(int argc, char *argv[])
{
    auto res = printNumbers(5);

    while (res.resume())
    {
        std::cout << "main()" << std::endl;
    }

    std::cout << std::format("return val: {}", res.get_result()) << std::endl;

    res.destory();

    return 0;
}
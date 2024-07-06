#include <iostream>
#include <format>
#include "./task.hpp"
#include "./scheduler.hpp"

coro::scheduler::task_t addNum(int a, int b)
{
    co_await std::suspend_always{};
    co_return a + b;
}

coro::scheduler::task_t printResult()
{
    int res = co_await addNum(2, 4);
    std::cout << std::format("result: {}", res) << std::endl;
}

coro::task<double> factorial(int val)
{
    co_await std::suspend_always{};

    if (val <= 1)
    {
        co_return 1;
    }

    co_return val *(co_await factorial(val - 1));
}

coro::scheduler::task_t printTask(auto t)
{
    auto res = co_await t;
    std::cout << std::format("result: {}", res) << std::endl;
}

int main(int argc, char *argv[])
{

    coro::scheduler sche;
    //  sche.schedule(printResult());

    auto t1 = printTask(addNum(2, 4));
    sche.schedule(t1);

    auto t2 = printTask(factorial(5));
    sche.schedule(t2);

    sche.run();

    return 0;
}
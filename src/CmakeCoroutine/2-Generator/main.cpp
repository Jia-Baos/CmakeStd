#include <format>
#include <iostream>
#include "./task.hpp"

coro::generator<int> getNumbers(int val)
{
    for (size_t i = 0; i < val; ++i)
    {
        co_yield i;
    }
}

int main(int argc, char *argv[])
{
    auto res = getNumbers(5);

    while (res.resume())
    {
        std::cout << res.get_result() << std::endl;
    }

    // for (decltype(res)::iterator it = res.begin(); it != res.end(); ++it)
    // {
    //     std::cout << *it << std::endl;
    // }

    // for (auto it : res)
    // {
    //     std::cout << it << std::endl;
    // }

    res.destory();

    std::cout << "done" << std::endl;

    return 0;
}
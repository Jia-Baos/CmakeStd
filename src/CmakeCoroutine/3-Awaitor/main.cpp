#include <iostream>
#include <coroutine>
#include <stdexcept>
#include <thread>
#include <format>

auto switch_to_new_thread(std::jthread &out)
{
    struct awaitable
    {
        std::jthread *p_out;

        bool await_ready()
        {
            std::cout << "await_ready()" << std::endl;
            return false;
        }

        void await_suspend(std::coroutine_handle<> h)
        {
            std::jthread &out = *p_out;
            if (out.joinable())
            {
                throw std::runtime_error("Output jthread parameter not empty");
            }
            out = std::jthread([h]
                               { h.resume(); });
            // Potential undefined behavior: accessing potentially destroyed *this
            // std::cout << "New thread ID: " << p_out->get_id() << '\n';
            std::cout << "new thread ID: " << out.get_id() << std::endl;
        }

        // void await_resume()
        // {
        //     std::cout << "await_resume()" << std::endl;
        // }

        int await_resume()
        {
            std::cout << "await_resume()" << std::endl;
            return 100;
        }
    };

    return awaitable{&out};
}

struct task
{
    struct promise_type
    {
        task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

task resuming_on_new_thread(std::jthread &out)
{
    std::cout << "coro begin, thread ID: " << std::this_thread::get_id() << std::endl;

    // co_await switch_to_new_thread(out);
    int res = co_await switch_to_new_thread(out);
    std::cout << std::format("awaitor return val: {}", res) << std::endl;

    // awaiter destroyed here
    std::cout << "coro resume, thread ID: " << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::jthread out;

    resuming_on_new_thread(out);

    return 0;
}
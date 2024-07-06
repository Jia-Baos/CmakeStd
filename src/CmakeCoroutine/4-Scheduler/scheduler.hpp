#pragma once

#ifndef SRC_SCHEDULER_HPP
#define SRC_SCHEDULER_HPP

#include <coroutine>
#include <exception>
#include <queue>

namespace coro
{
    class scheduler
    {
    public:
        void schedule(const coro::task &t)
        {
            ready_queue.emplace(t.get_handle());
        }

        void run()
        {
            while (ready_queue.size())
            {
                auto hdl = ready_queue.front();
                ready_queue.pop();
                hdl.resume();

                if (!hdl.done())
                {
                    ready_queue.emplace(hdl);
                }
            }
        }

    private:
        std::queue<coro::task::handle_t> ready_queue;
    };
}

#endif /* !SRC_SCHEDULER_HPP */
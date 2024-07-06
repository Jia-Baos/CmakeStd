#pragma once

#ifndef SRC_TASK_HPP
#define SRC_TASK_HPP

#include <coroutine>
#include <exception>

namespace coro
{
    class task
    {
    public:
        struct promise_type
        {
            auto get_return_object()
            {
                return task(std::coroutine_handle<promise_type>::from_promise(*this));
            }

            auto initial_suspend() noexcept
            {
                return std::suspend_always{};
            }

            auto final_suspend() noexcept
            {
                return std::suspend_always{};
            }

            // void return_void() noexcept {}

            void return_value(int val) noexcept
            {
                return_val = val;
            }

            void unhandled_exception()
            {
                std::terminate();
            }

            int return_val;
        };

        explicit task(std::coroutine_handle<promise_type> hdl) : m_hdl(hdl) {}

        bool resume()
        {
            if (!m_hdl || m_hdl.done())
            {
                return false;
            }
            m_hdl.resume();
            return !m_hdl.done();
        }

        int get_result()
        {
            return m_hdl.promise().return_val;
        }

        void destory() { m_hdl.destroy(); }

    private:
        std::coroutine_handle<promise_type> m_hdl;
    };
}

#endif /* !SRC_TASK_HPP */
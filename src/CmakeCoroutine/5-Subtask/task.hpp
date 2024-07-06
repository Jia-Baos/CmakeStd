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
        struct promise_type;
        using handle_t = std::coroutine_handle<promise_type>;

        struct promise_type
        {
            struct final_awaitor
            {
                bool await_ready() noexcept
                {
                    return false;
                }

                std::coroutine_handle<> await_suspend(auto self) noexcept
                {
                    if (self.promise().prev)
                    {
                        return self.promise().prev;
                    }

                    return std::noop_coroutine();
                }

                void await_resume() noexcept {}
            };

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
                return final_awaitor{};
            }

            void return_value(int val) noexcept
            {
                return_val = val;
            }

            void unhandled_exception()
            {
                std::terminate();
            }

            int return_val;
            handle_t prev;
            handle_t next;
        };

        explicit task(std::coroutine_handle<promise_type> hdl) : m_hdl(hdl) {}

        struct awaitor
        {
            bool await_ready() noexcept
            {
                return false;
            }

            std::coroutine_handle<> await_suspend(handle_t parent) noexcept
            {
                parent.promise().next = self;
                self.promise().prev = parent;
                return self;
            }

            int await_resume() noexcept
            {
                self.promise().prev.promise().next = nullptr;
                int result = self.promise().return_val;
                self.destroy();
                return result;
            }

            handle_t self;
        };

        auto operator co_await()
        {
            return awaitor{m_hdl};
        }

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

        handle_t get_handle() const
        {
            return m_hdl;
        }

        void destory()
        {
            m_hdl.destroy();
        }

    private:
        std::coroutine_handle<promise_type> m_hdl;
    };

    task::handle_t get_innermost_coro(task::handle_t h)
    {
        while (h.promise().next)
        {
            h = h.promise().next;
        }

        return h;
    }
}

#endif /* !SRC_TASK_HPP */
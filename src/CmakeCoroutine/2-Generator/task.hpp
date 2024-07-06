#pragma once

#ifndef SRC_TASK_HPP
#define SRC_TASK_HPP

#include <iostream>
#include <coroutine>
#include <exception>

namespace coro
{
    template <typename T>
    class generator
    {
    public:
        struct promise_type
        {
            auto get_return_object()
            {
                return generator(std::coroutine_handle<promise_type>::from_promise(*this));
            }

            auto initial_suspend() noexcept
            {
                return std::suspend_always{};
            }

            auto final_suspend() noexcept
            {
                return std::suspend_always{};
            }

            void return_void() noexcept {}

            void unhandled_exception()
            {
                std::terminate();
            }

            auto yield_value(T val)
            {
                m_val = val;
                return std::suspend_always{};
            }

            T m_val;
        };

        explicit generator(std::coroutine_handle<promise_type> hdl) : m_hdl(hdl) {}

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
            return m_hdl.promise().m_val;
        }

        struct iterator
        {
            generator *g = nullptr;

            T operator*()
            {
                return g->m_hdl.promise().m_val;
            }

            iterator &operator++()
            {
                if (g->m_hdl && !g->m_hdl.done())
                {
                    g->m_hdl.resume();
                    if (g->m_hdl.done())
                    {
                        g = nullptr;
                    }
                }
                return *this;
            }

            bool operator==(const iterator &other) const
            {
                return g == other.g;
            }
        };

        iterator begin()
        {
            if (m_hdl && !m_hdl.done())
            {
                return ++iterator{this};
            }

            return {};
        }

        iterator end()
        {
            return {};
        }

        void destory()
        {
            m_hdl.destroy();
        }

    private:
        std::coroutine_handle<promise_type> m_hdl;
    };
}

#endif /* !SRC_TASK_HPP */
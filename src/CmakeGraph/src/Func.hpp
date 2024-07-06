#ifndef FUNC_H
#define FUNC_H

#include <string>
#include <exception>

class MyException
{
public:
    MyException(const std::string &err_msg, int id) : m_errmsg(err_msg), m_id(id) {}

    virtual std::string what() const
    {
        std::string msg = "MyException: ";
        msg += m_errmsg;
        msg += ", ";
        msg += std::to_string(m_id);

        return msg;
    }

protected:
    std::string m_errmsg;
    int m_id;
};

#endif // !FUNC_H
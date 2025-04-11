#include <iostream>
#include <memory>

// 抽象接口类
template <typename R, typename... Args>
class ICallable {
public:
    virtual R invoke(Args &&...args) = 0;
    virtual ~ICallable() {}
};

// 桥接类
template <typename T, typename R, typename... Args>
class CallableImpl : public ICallable<R, Args...> {
private:
    T callable;

public:
    CallableImpl(T &&c) : callable(std::move(c)) {}
    R invoke(Args &&...args) override
    {
        return callable(std::forward<Args>(args)...);
    }
};

// 函数签名
template <typename Signature>
class MyFunction;

// 具体实现
template <typename R, typename... Args>
class MyFunction<R(Args...)> {
private:
    std::unique_ptr<ICallable<R, Args...>> funPtr;

public:
    template <typename T>
    MyFunction(T &&callable)
    {
        funPtr = std::make_unique<CallableImpl<T, R, Args...>>(std::forward<T>(callable));
    }

    R operator()(Args... args) const
    {
        return funPtr->invoke(std::forward<Args>(args)...);
    }
};

void display()
{
    std::cout << "hello world" << std::endl;
}

int add(int a, int b)
{
    return a + b;
}

int main(int argc, char *argv[])
{
    MyFunction<void()> f1 = [] { std::cout << "hello world" << std::endl; };
    MyFunction<void()> f2 = display;
    MyFunction<int(int, int)> f3 = [](int a, int b) { return a + b; };
    MyFunction<int(int, int)> f4 = add;

    f1();
    f2();
    std::cout << f3(1, 2) << std::endl;
    std::cout << f4(1, 2) << std::endl;

    return 0;
}

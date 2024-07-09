# 文档

## vscode中cmake插件的文档

[cmake插件链接](https://vector-of-bool.github.io/docs/vscode-cmake-tools/index.html)

## 扫描电脑上所有编译器

点击vscode左下角的工具包设置（cmake配置下），之后再跳出的框中点击扫描工具包，之后就获取电脑上所有的编译工具。

## 说明

这个一个关于C++20协程的仓库，里面存放一些自己学习的Demo


## C++20 协程关键字

```C++
co_await 表达式 // ——用于暂停执行，直到恢复
co_yield 表达式 // ——用于暂停执行并返回一个值
co_return 语句  // ——用于完成执行并返回一个值
``` 

```C++
co_await awaitable

awaitable
    awaitor
        await_ready()   // 是否让出控制权
        await_suspend(handle)   // 如果让出控制权，把控制权交给谁
        await_wait()    // 控制权返回时做什么
    operator coawait()
```

```C++
co_yield expr
    往 promise 中写值
    等价于 co_await promise.yield_value(expr)
```

```C++
co_return expr
    结束 conroutine
    
    如果 expr 为空，或者为 void，并且 promise 定义了 return_void()，则调用 return_void()
    
    如果 expr 不为空，且 promise 定义了 return_value(value)，则调用 return_value(expr)

    return_void()和return_value()只能定义其中一个
```

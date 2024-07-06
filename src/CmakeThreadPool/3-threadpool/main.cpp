#include <bits/stdc++.h>
#include "./ThreadPool.hpp"

// Simple function that adds multiplies two numbers and returns the result
int multiply(const int a, const int b)
{
    const int res = a * b;
    return res;
}

int main(int argc, char *argv[])
{
    // Create pool with 3 threads
    ThreadPool pool(3);

    // Initialize pool
    pool.init();

    /// The type of future is given by the return type of the function
    std::future<int> future = pool.submit(multiply, 2, 3);
    // auto future = pool.submit(multiply, 2, 3);

    const int result = future.get();
    std::cout << result << std::endl;

    // Shutdown the pool, releasing all threads
    pool.shutdown();

    return 0;
}
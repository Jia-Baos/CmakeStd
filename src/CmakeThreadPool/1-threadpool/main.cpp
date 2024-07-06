#include <bits/stdc++.h>
#include "./ThreadPool.hpp"

// Simple function that adds multiplies two numbers and prints the result
void multiply(const int a, const int b)
{
    const int res = a * b;
    std::cout << "res in thread is: " << res << std::endl;
}

int main(int argc, char *argv[])
{
    // Create pool with 3 threads
    ThreadPool pool(3);

    // Initialize pool
    pool.init();

    auto future = pool.submit(multiply, 2, 3);

    // Shutdown the pool, releasing all threads
    pool.shutdown();

    return 0;
}
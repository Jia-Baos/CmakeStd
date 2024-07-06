#include <bits/stdc++.h>
#include "./ThreadPool.hpp"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);
auto rnd = std::bind(dist, mt);

void simulate_hard_computation()
{
    // Blocks execution of the current thread for at least the specified sleep_duration
    std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

// Simple function that adds multiplies two numbers and prints the result
void multiply(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << "multiply: " << a << " * " << b << " = " << res << std::endl;
}

// Same as before but now we have an output parameter
void multiply_output(int &out, const int a, const int b)
{
    simulate_hard_computation();
    out = a * b;
    std::cout << "multiply_ref: " << a << " * " << b << " = " << out << std::endl;
}

// Same as before but now we have an output parameter
int multiply_return(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << "multiply_return: " << a << " * " << b << " = " << res << std::endl;
    return res;
}

int main(int argc, char *argv[])
{
    // Create pool with default threads
    ThreadPool pool{};

    // Initialize pool
    pool.init();

    // Print the threads can be used in hardware
    std::cout << "num of threads: " << std::thread::hardware_concurrency() << std::endl;

    // Submit (partial) multiplication table
    std::vector<std::future<void>> res_vec(18);
    for (int i = 1; i < 3; ++i)
    {
        for (int j = 1; j < 10; ++j)
        {
            res_vec[9 * (i - 1) + j - 1] = pool.submit(multiply, i, j);
        }
    }
    for (auto &res : res_vec)
    {
        res.get();
    }

    // // Submit function with output parameter passed by ref
    // int output_ref;
    // auto future1 = pool.submit(multiply_output, std::ref(output_ref), 5, 6);

    // // Wait for multiplication output to finish
    // future1.get();
    // std::cout << "Last operation result is equals to " << output_ref << std::endl;

    // // Submit function with return parameter
    // auto future2 = pool.submit(multiply_return, 5, 3);

    // // Wait for multiplication output to finish
    // int res = future2.get();
    // std::cout << "Last operation result is equals to " << res << std::endl;

    return 0;
}
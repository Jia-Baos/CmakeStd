#include <bits/stdc++.h>
#include "./ThreadPool.hpp"

// Simple function that adds multiplies two numbers and returns the result
int Multiply(const int a, const int b) {
  const int kRes = a * b;
  return kRes;
}

int main(int argc, char *argv[]) {
  // Create pool with 3 threads
  ThreadPool pool(3);

  // Initialize pool
  pool.Init();

  /// The type of future is given by the return type of the function
  std::future<int> future = pool.Submit(Multiply, 2, 3);
  // auto future = pool.submit(multiply, 2, 3);

  const int kResult = future.get();
  std::cout << kResult << std::endl;

  // Shutdown the pool, releasing all threads
  pool.Shutdown();

  return 0;
}

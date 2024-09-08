#include <bits/stdc++.h>
#include "./ThreadPool.hpp"

// Simple function that adds multiplies two numbers and updates the out_res variable passed by ref
void Multiply(int &out_res, const int a, const int b) { out_res = a * b; }

int main(int argc, char *argv[]) {
  // Create pool with 3 threads
  ThreadPool pool(3);

  // Initialize pool
  pool.Init();

  int result = 0;
  auto future = pool.Submit(Multiply, std::ref(result), 2, 3);
  // result is 0
  // future.get();
  // result is 6
  std::cout << result << std::endl;

  // Shutdown the pool, releasing all threads
  pool.Shutdown();

  return 0;
}

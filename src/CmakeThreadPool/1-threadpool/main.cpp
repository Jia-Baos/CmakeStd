#include <bits/stdc++.h>
#include "./ThreadPool.hpp"

// Simple function that adds multiplies two numbers and prints the result
void Multiply(const int a, const int b) {
  const int kRes = a * b;
  std::cout << "res in thread is: " << kRes << std::endl;
}

int main(int argc, char *argv[]) {
  // Create pool with 3 threads
  ThreadPool pool(3);

  // Initialize pool
  pool.Init();

  auto future = pool.Submit(Multiply, 2, 3);

  // Shutdown the pool, releasing all threads
  pool.Shutdown();

  return 0;
}

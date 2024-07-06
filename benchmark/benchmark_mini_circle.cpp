#include "../src/MiniCircle/MiniCircle.hpp"
#include <benchmark/benchmark.h>

MyVector p1(2.0, 2.0);
MyVector v1(1.0, 1.0);
MyVector p2(2.0, -2.0);
MyVector v2(1.0, -1.0);
MyVector p3(0.0, 0.0);

double value;
Circle circle;
std::pair<double, double> result;
std::pair<MyVector, MyVector> combination;

static void BM_1(benchmark::State& state) {
  for (auto _ : state) {
    result = p1 + p2;
  }
}

static void BM_2(benchmark::State& state) {
  for (auto _ : state) {
    result = p1 - p2;
  }
}

static void BM_3(benchmark::State& state) {
  for (auto _ : state) {
    value = p1 * p2;
  }
}

static void BM_4(benchmark::State& state) {
  for (auto _ : state) {
    result = p1 * 1.0;
  }
}

static void BM_5(benchmark::State& state) {
  for (auto _ : state) {
    result = p1 / 1.0;
  }
}

static void BM_6(benchmark::State& state) {
  for (auto _ : state) {
    value = Judge(2.0, 3.0);
  }
}

static void BM_7(benchmark::State& state) {
  for (auto _ : state) {
    result = Rotate(v1, PI / 2);
  }
}

static void BM_8(benchmark::State& state) {
  for (auto _ : state) {
    value = Distance(p1, p2);
  }
}

static void BM_9(benchmark::State& state) {
  for (auto _ : state) {
    result = Intersection(p1, v1, p2, v2);
  }
}

static void BM_10(benchmark::State& state) {
  for (auto _ : state) {
    combination = MidPerpendicular(p1, p2);
  }
}

static void BM_11(benchmark::State& state) {
  for (auto _ : state) {
    circle = MiniCircle(p1, p2, p3);
  }
}

// 这一句不能少
BENCHMARK(BM_1);
BENCHMARK(BM_2);
BENCHMARK(BM_3);
BENCHMARK(BM_4);
BENCHMARK(BM_5);
BENCHMARK(BM_6);
BENCHMARK(BM_7);
BENCHMARK(BM_8);
BENCHMARK(BM_9);
BENCHMARK(BM_10);
BENCHMARK(BM_11);

// Google Benchmark 提供的 main 函数
// 也可以直接在 target_link_libraries 中加入 benchmark::benchmark_main，这样就可以省略这一行代码了
BENCHMARK_MAIN();
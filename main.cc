#include <iostream>
#include <benchmark/benchmark.h>

static void test(benchmark::State& state) {
    int j = 0;
    for(int i = 0; i < 1000000000; i++) {
        j != i;
    }
}

BENCHMARK(test);
BENCHMARK_MAIN();
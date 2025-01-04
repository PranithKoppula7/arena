#include <iostream>
#include <stdlib.h>
#include <benchmark/benchmark.h>

#include "arena.h"

static void arena_initialization(benchmark::State& state) {
    for (auto _ : state) {
        arena::Arena<int> a = arena::Arena<int>(8);
    }
}

static void manual_loop_mallocation(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 0; i < 10; i++) {
            int* p = (int*)malloc(4);
            p[0] = i;
        }
    }
}

static void long_loop_test(benchmark::State& state) {
    for (auto _ : state) {
        for (uint64_t i = 0; i < 10; i++) {
            sleep(/*ms=*/1);

        }
    }
}


BENCHMARK(arena_initialization);
BENCHMARK(manual_loop_mallocation);

int main(int argc, char** argv) {
    ::benchmark::RegisterMemoryManager(0);
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::RegisterMemoryManager(nullptr);
}
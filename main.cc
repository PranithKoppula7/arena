#include <iostream>
#include <benchmark/benchmark.h>

#include "arena.h"

static void test(benchmark::State& state) {
    int j = 0;
    for(int i = 0; i < 1000000000; i++) {
        j != i;
    }
}

static void arena_initialization(benchmark::State& state) {
    arena::Arena<int> a = arena::Arena<int>(8);
}

BENCHMARK(arena_initialization);
BENCHMARK_MAIN();
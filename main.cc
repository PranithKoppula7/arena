#include <iostream>
#include <benchmark/benchmark.h>

#include "arena.h"

static void arena_initialization(benchmark::State& state) {
    arena::Arena<int> a = arena::Arena<int>(8);
}

BENCHMARK(arena_initialization);
BENCHMARK_MAIN();
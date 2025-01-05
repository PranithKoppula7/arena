#include <iostream>
#include <stdlib.h>
#include <benchmark/benchmark.h>

#include "arena.h"

class SimpleMemoryManager : public benchmark::MemoryManager {
public:
    int64_t num_allocs;
    int64_t max_bytes_used;


    void Start() BENCHMARK_OVERRIDE {
        num_allocs = 0;
        max_bytes_used = 0;
    }

    void Stop(Result& result) BENCHMARK_OVERRIDE {
        result.num_allocs = num_allocs;
        result.max_bytes_used = max_bytes_used;
    }
};

std::unique_ptr<SimpleMemoryManager> mm(new SimpleMemoryManager());

// #ifdef MEMORY_PROFILER
void *custom_malloc(size_t size) {
    void *p = malloc(size);
    mm.get()->num_allocs += 1;
    mm.get()->max_bytes_used += size;
    return p;
}
#define malloc(size) custom_malloc(size)
// #endif

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

static void BM_memory(benchmark::State& state) {
    for (auto _ : state)
        for (int i =0; i < 10; i++) {
            benchmark::DoNotOptimize((int *) malloc(10 * sizeof(int *)));
        }
}

BENCHMARK(BM_memory)->Unit(benchmark::kMillisecond)->Iterations(17);


BENCHMARK(arena_initialization);
BENCHMARK(manual_loop_mallocation);

int main(int argc, char** argv) {
    ::benchmark::RegisterMemoryManager(mm.get());
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::RegisterMemoryManager(nullptr);
}
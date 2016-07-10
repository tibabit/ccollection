#include <iostream>
#include <vector>

#include "benchmark/benchmark.h"

#include "include/ccollection.h"

static void BM_VectorNew(benchmark::State& state)
{
    vector_t * vector = NULL;
    while(state.KeepRunning())
    {
        vector = vector_new(sizeof(int));
    }
}
BENCHMARK(BM_VectorNew);

#if 0
static void BM_VectorDestroy(benchmark::State& state)
{
    vector_t * vector = NULL;
    while(state.KeepRunning())
    {
        vector = vector_new(sizeof(int));
        vector_destroy(vector);
    }
}
BENCHMARK(BM_VectorDestroy);
#endif

static void BM_VectorPushBack(benchmark::State& state)
{

    vector_t * vector = vector_new(sizeof(int));
    while(state.KeepRunning())
    {

        for (int i = 0; i < state.range_x(); i++)
        {
            vector_push_back(vector, &i);
        }
    }
    vector_destroy(vector);
}
BENCHMARK(BM_VectorPushBack)->RangeMultiplier(2)->Range(1, 1 << 2);

BENCHMARK_MAIN()

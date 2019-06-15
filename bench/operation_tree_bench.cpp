#include <benchmark/benchmark.h>
#include <real/real.hpp>
#include <benchmark_helpers.hpp>

/** @file benchmark the operation trees,
 * with different kinds of leaves, and/or a large number of nodes. 
 */ 

// constants used in the benchmarks
const int MIN_TREE_SIZE = 8; 
const int MAX_TREE_SIZE = 16;

// used to force evaluation, without console output
NullStream null_stream; 

// trees between MIN_TREE_SIZE and MAX_TREE_SIZE of single operations
static void BM_RealAdditionTree(benchmark::State& state) {
    boost::real::real a ("1.2");
    boost::real::real c ("0");

    for (auto i : state)
        for (int i = 0; i < state.range(0); i++)
            c += a;
    null_stream << c << '\n';
}
BENCHMARK(BM_RealAdditionTree)->Range(MIN_TREE_SIZE,MAX_TREE_SIZE)->Unit(benchmark::kMillisecond);

static void BM_RealSubtractionTree(benchmark::State& state) {
    boost::real::real a ("1");
    boost::real::real c ("9999");

    for (auto i : state)
    {
        for (int i = 0; i < state.range(0); i++)
            c -= a;
    null_stream << c << '\n';
    }
}
BENCHMARK(BM_RealSubtractionTree)->Range(MIN_TREE_SIZE,MAX_TREE_SIZE)->Unit(benchmark::kMillisecond);

static void BM_RealMultiplicationTree(benchmark::State& state) {
    boost::real::real a ("1");
    boost::real::real c ("9");

    for (auto i : state)
    {
        for (int i = 0; i < state.range(0); i++)
            c *= a;
    null_stream << c << '\n';
    }
}
BENCHMARK(BM_RealMultiplicationTree)->Range(MIN_TREE_SIZE,MAX_TREE_SIZE)->Unit(benchmark::kMillisecond);

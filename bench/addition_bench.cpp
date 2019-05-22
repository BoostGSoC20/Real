#include <bench_helpers.hpp>
#include <benchmark/benchmark.h>
#include <real/real.hpp>
#include <iostream>

// this process uses an absurd amount of memory
// sums 10,000 reals, then evaluates.
static void BM_RealAddition10000(benchmark::State& state) {
    boost::real::real a ("1.2");
    boost::real::real c ("0");

    for (auto i : state)
        for (int i = 0; i < 10000; i++)
            c += a;
    std::cout << c << '\n';
}
BENCHMARK(BM_RealAddition10000);

BENCHMARK_MAIN();

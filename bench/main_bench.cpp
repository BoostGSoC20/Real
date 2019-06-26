#include <benchmark/benchmark.h>
#include <real/real.hpp>

std::optional<unsigned int> boost::real::real::maximum_precision = 10;
std::optional<unsigned int> boost::real::real_algorithm::maximum_precision = 10;

BENCHMARK_MAIN();

#include <benchmark/benchmark.h>
#include <real/real.hpp>

unsigned int boost::real::real::maximum_precision = 10;
unsigned int boost::real::real_algorithm::maximum_precision = 10;

BENCHMARK_MAIN();

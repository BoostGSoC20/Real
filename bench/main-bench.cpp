#include <benchmark/benchmark.h>
#include <real/real.hpp>

// ensure this is >= to MAX_NUM_DIGITS_XX for all benchmarks, else we will get
// a precision error and the benchmarks will not be meaningful.
std::optional<size_t> boost::real::const_precision_iterator::maximum_precision = 10000;

BENCHMARK_MAIN();

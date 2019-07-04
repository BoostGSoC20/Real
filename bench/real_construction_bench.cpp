#include <benchmark/benchmark.h>
#include <benchmark_helpers.hpp>

/** benchmarks the construction of a real number
 *  for some varying parameter
 *  (number of tree nodes, or number of digits)
 */ 

const int MIN_TREE_NODES = 10; 
const int MAX_TREE_NODES = 10000;
const int MULTIPLIER_TC = 10;  // for range evaluation of tree construction benchmarks
/// benchmarks the construction speed of doing a op= b, n times, where n is the set of powers of
/// MULTIPLIER_TC between MIN_TREE_NODES and MAX_TREE_NODES
void BM_RealOperationTreeConstruction(benchmark::State& state, boost::real::OPERATION op) {
    for (auto i : state) {
        boost::real::real a ("1234567891");
        boost::real::real b ("9876532198");

        // We keep the precision constant here because in constructing the *= tree, we would get way more digits
        // than in +=, -= trees. This should make the benchmarks more meaningful
        a.set_maximum_precision(10);

        for (int i = 0; i < state.range(0); i++)
            realOperationEq(a,b,op);

        state.SetComplexityN(state.range(0));
    }
}

// these benchmark the operation tree constructors for each operation type.
/// @TODO: add division bench
BENCHMARK_CAPTURE(BM_RealOperationTreeConstruction, addition, boost::real::OPERATION(boost::real::OPERATION::ADDITION))
    ->RangeMultiplier(MULTIPLIER_TC)->Range(MIN_TREE_NODES ,MAX_TREE_NODES)->Unit(benchmark::kMillisecond)
    ->Complexity();

BENCHMARK_CAPTURE(BM_RealOperationTreeConstruction, subtraction, boost::real::OPERATION(boost::real::OPERATION::SUBTRACTION))
    ->RangeMultiplier(MULTIPLIER_TC)->Range(MIN_TREE_NODES ,MAX_TREE_NODES)->Unit(benchmark::kMillisecond)
    ->Complexity();

BENCHMARK_CAPTURE(BM_RealOperationTreeConstruction, multiplication, boost::real::OPERATION(boost::real::OPERATION::MULTIPLICATION))
    ->RangeMultiplier(MULTIPLIER_TC)->Range(MIN_TREE_NODES ,MAX_TREE_NODES)->Unit(benchmark::kMillisecond)
    ->Complexity();

const int MIN_NUM_DIGITS_EC = 10;
const int MAX_NUM_DIGITS_EC = 10000;
const int MULTIPLIER_EC = 10;  // for range evaluation of explicit construction benchmarks

/// benchmarks real explicit's string constructor for a varying number of digits
void BM_RealExplicitConstruction_String(benchmark::State& state) {
    for (auto i : state) {
        state.PauseTiming(); // construct a string representing a number of n digits
        std::string number;

        for (int i = 0; i < state.range(0); i++) {
            number.push_back('1');
        }
        state.ResumeTiming();

        boost::real::real a(number);
        state.SetComplexityN(state.range(0));
    }
}
BENCHMARK(BM_RealExplicitConstruction_String)
    ->RangeMultiplier(MULTIPLIER_EC)->Range(MIN_NUM_DIGITS_EC,MAX_NUM_DIGITS_EC)->Unit(benchmark::kMillisecond)
    ->Complexity();

// benchmarks for real_algorithm construction seem unnecessary because there's not much that goes on in it
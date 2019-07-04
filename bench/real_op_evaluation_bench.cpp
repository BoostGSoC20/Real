#include <benchmark/benchmark.h>
#include <benchmark_helpers.hpp>

const int MIN_TREE_NODES = 10; 
const int MAX_TREE_NODES = 10000;
const int MULTIPLIER_TE = 10;  // for range evaluation of tree evaluation benchmarks

/// benchmarks the evaluation speed of doing a op= b, n times, where n is the set of powers of
/// MULTIPLIER_TE between MIN_TREE_NODES and MAX_TREE_NODES
void BM_RealOperationTreeEvaluation(benchmark::State& state, boost::real::OPERATION op) {
    for (auto i : state) {
    boost::real::real a ("12");
    boost::real::real b ("34");

    state.PauseTiming();
    for (int i = 0; i < state.range(0); i++) {
        realOperationEq(a,b,op);
    }
    state.ResumeTiming();

    a.get_real_itr().cend(); // force evaluation
    state.SetComplexityN(state.range(0));
    }
}

/// @TODO: add division. 
BENCHMARK_CAPTURE(BM_RealOperationTreeEvaluation, addition, boost::real::OPERATION(boost::real::OPERATION::ADDITION))
    ->RangeMultiplier(MULTIPLIER_TE)->Range(MIN_TREE_NODES ,MAX_TREE_NODES)->Unit(benchmark::kMillisecond)
    ->Complexity();

BENCHMARK_CAPTURE(BM_RealOperationTreeEvaluation, subtraction, boost::real::OPERATION(boost::real::OPERATION::SUBTRACTION))
    ->RangeMultiplier(MULTIPLIER_TE)->Range(MIN_TREE_NODES ,MAX_TREE_NODES)->Unit(benchmark::kMillisecond)
    ->Complexity();

BENCHMARK_CAPTURE(BM_RealOperationTreeEvaluation, multiplication, boost::real::OPERATION(boost::real::OPERATION::MULTIPLICATION))
    ->RangeMultiplier(MULTIPLIER_TE)->Range(MIN_TREE_NODES ,MAX_TREE_NODES)->Unit(benchmark::kMillisecond)
    ->Complexity();


const int MIN_NUM_DIGITS = 1000;
const int MAX_NUM_DIGITS = 10000;
const int MULTIPLIER_OE = 6;

/// benchmarks a op= b, where a, b, have n digits, where n is the set of powers of 
/// MULTIPLIER_OE, between MIN_NUM_DIGITS and MAX_NUM_DIGITS
void BM_RealOperationEvaluation(benchmark::State& state, boost::real::OPERATION op) {
    for (auto i : state) {
        state.PauseTiming(); // construct a, b
        std::string tmp;
        for (int i = 0; i < state.range(0); i++) {
            tmp.push_back('2');
        }
        boost::real::real a(tmp);

        tmp.clear();
        for (int i = 0; i < state.range(0); i++) {
            tmp.push_back('3');
        }
        boost::real::real b(tmp);
        realOperationEq(a,b,op);
        state.ResumeTiming();

    a.get_real_itr().cend(); // force evaluation
    state.SetComplexityN(state.range(0));
    }
}

///@TODO: add division
// The BM_RealOperationEvaluation operations are much faster, so these use nanoseconds in the result.
BENCHMARK_CAPTURE(BM_RealOperationEvaluation, addition, boost::real::OPERATION(boost::real::OPERATION::ADDITION))
    ->RangeMultiplier(MULTIPLIER_OE)->Range(MIN_NUM_DIGITS,MAX_NUM_DIGITS)
    ->Complexity();

BENCHMARK_CAPTURE(BM_RealOperationEvaluation, subtraction, boost::real::OPERATION(boost::real::OPERATION::SUBTRACTION))
    ->RangeMultiplier(MULTIPLIER_OE)->Range(MIN_NUM_DIGITS,MAX_NUM_DIGITS)
    ->Complexity();

BENCHMARK_CAPTURE(BM_RealOperationEvaluation, multiplication, boost::real::OPERATION(boost::real::OPERATION::MULTIPLICATION))
    ->RangeMultiplier(MULTIPLIER_OE)->Range(MIN_NUM_DIGITS,MAX_NUM_DIGITS)
    ->Complexity();


/// benchmarks operator> operator< and operator== for numbers a, b, where a == b, with n digits
void BM_RealComparisonEvaluation(benchmark::State& state, Comparison comp) {
    for (auto i : state) {
        state.PauseTiming(); // construct a, b
        std::string tmp;
        for (int i = 0; i < state.range(0); i++) { // we compare 111...1 and 111..1
            tmp.push_back('1');
        }
        boost::real::real a(tmp);
        boost::real::real b(tmp);

        state.ResumeTiming();

        bool boo = realComp(a,b,comp); // evaluation
        state.SetComplexityN(state.range(0));
    }
}

BENCHMARK_CAPTURE(BM_RealComparisonEvaluation, less_than, Comparison::less_than)
    ->RangeMultiplier(MULTIPLIER_OE)->Range(MIN_NUM_DIGITS,MAX_NUM_DIGITS)->Unit(benchmark::kMillisecond)
    ->Complexity();

BENCHMARK_CAPTURE(BM_RealComparisonEvaluation, greater_than, Comparison::greater_than)
    ->RangeMultiplier(MULTIPLIER_OE)->Range(MIN_NUM_DIGITS,MAX_NUM_DIGITS)->Unit(benchmark::kMillisecond)
    ->Complexity();

BENCHMARK_CAPTURE(BM_RealComparisonEvaluation, equals, Comparison::equals)
    ->RangeMultiplier(MULTIPLIER_OE)->Range(MIN_NUM_DIGITS,MAX_NUM_DIGITS)->Unit(benchmark::kMillisecond)
    ->Complexity();
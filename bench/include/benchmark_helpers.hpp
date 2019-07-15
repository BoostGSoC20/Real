#ifndef BOOST_REAL_BENCHMARK_HELPERS_HPP
#define BOOST_REAL_BENCHMARK_HELPERS_HPP

#include <real/real.hpp>


struct bench_invalid_operation_exception : public std::exception {
    const char * what () const throw () override {
        return "This operation is not supported by real benchmarks at this time.";
    }
};

constexpr void realOperationEq(boost::real::real& lhs, boost::real::real& rhs, 
                               boost::real::OPERATION op) {
    switch (op) {
        case boost::real::OPERATION::ADDITION:
            lhs += rhs;
            break;
        case boost::real::OPERATION::SUBTRACTION:
            lhs -= rhs;
            break;
        case boost::real::OPERATION::MULTIPLICATION:
            lhs *= rhs;
            break;
        default:
            throw bench_invalid_operation_exception();
    }
}

enum class Comparison {GREATER_THAN, LESS_THAN, EQUALS};
constexpr bool realComp(boost::real::real& lhs,boost::real::real& rhs, Comparison comp) {
    switch (comp) {
        case (Comparison::GREATER_THAN):
            return lhs > rhs;
        case (Comparison::LESS_THAN):
            return lhs < rhs;
        case(Comparison::EQUALS):
            return lhs==rhs;
        default:
            throw bench_invalid_operation_exception();
    }
}

#endif // BOOST_REAL_BENCHMARK_HELPERS_HPP
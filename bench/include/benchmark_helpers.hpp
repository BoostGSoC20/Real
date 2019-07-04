#ifndef BOOST_REAL_BENCHMARK_HELPERS_HPP
#define BOOST_REAL_BENCHMARK_HELPERS_HPP

#include <real/real.hpp>

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
    }
}

enum class Comparison {greater_than, less_than, equals};
constexpr bool realComp(boost::real::real& lhs,boost::real::real& rhs, Comparison comp) {
    switch (comp) {
        case (Comparison::greater_than):
            return lhs > rhs;
        case (Comparison::less_than):
            return lhs < rhs;
        case(Comparison::equals):
            return lhs==rhs;
    }
}

#endif // BOOST_REAL_BENCHMARK_HELPERS_HPP
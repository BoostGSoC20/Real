#ifndef BOOST_REAL_TEST_HELPERS_HPP
#define BOOST_REAL_TEST_HELPERS_HPP

#include <real/real.hpp>
#include <limits>
#include <sstream>

int BASE = (std::numeric_limits<int>::max() /4)*2;

template<> std::optional<size_t> boost::real::const_precision_iterator<int>::maximum_precision = 10;

namespace Catch {
    template<>
    struct StringMaker<boost::real::interval<int>> {
        static std::string convert( boost::real::interval<int> value ) {
            return value.as_string();
        }
    };
}

namespace Catch {
    template<>
    struct StringMaker<boost::real::real<int>> {
        static std::string convert( boost::real::real<int> value ) {
            return value.get_real_itr().cend().get_interval().as_string();
        }
    };
}

int one_and_max(unsigned int n) {
    if (n == 0) {
        return 1;
    }
    return BASE - 1;
}

int ones(unsigned int n) {
    return 1;
}

int one_one_one(unsigned int n) {
    if (n < 3) {
        return 1;
    }

    return 0;
}

#endif //BOOST_REAL_TEST_HELPERS_HPP

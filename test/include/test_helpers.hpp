#ifndef BOOST_REAL_TEST_HELPERS_HPP
#define BOOST_REAL_TEST_HELPERS_HPP

#include <real/interval.hpp>

namespace Catch {
    template<>
    struct StringMaker<boost::real::interval> {
        static std::string convert( boost::real::interval const& value ) {
            return value.as_sting();

        }
    };
}

int one_and_nines(unsigned int n) {
    if (n == 0) {
        return 1;
    }
    return 9;
}

int ones(unsigned int n) {
    return 1;
}

#endif //BOOST_REAL_TEST_HELPERS_HPP

#ifndef BOOST_REAL_IRRATIONALS_HPP
#define BOOST_REAL_IRRATIONALS_HPP

#include <real/real.hpp>
#include <real/irrational_helpers.hpp>


namespace boost {
    namespace real {
        namespace irrational {

            /**
             * @brief The Champernowne is a transcendental real constant whose digits are formed by
             * consecutively concatenate representations of sucessive integers in a determined base.
             * In this function, a binary base is used.
             */
            boost::real::real CHAMPERNOWNE_BINARY(boost::real::irrational::champernowne_binary_get_nth_digit, 0);
        }
    }
}

#endif //BOOST_REAL_IRRATIONALS_HPP

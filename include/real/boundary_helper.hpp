#ifndef BOOST_REAL_BOUNDARY_HELPER_HPP
#define BOOST_REAL_BOUNDARY_HELPER_HPP

#include <algorithm>
#include "interval.hpp"

namespace boost {
    namespace real {
        namespace helper {

            /**
             * @author Laouen Mayal Louan Belloli
             *
             * @brief checks whether the lhs vector elements are lower than the rhs elements if those
             * elements are interpreted as a number digits.
             *
             * @pre lhs and rhs must be aligned, i.e. two digits in the same index represent the same unit.
             *
             * @param lhs - a std::vector<int> used as the left side operand
             * @param rhs - a std::vector<int> used as the right side operand
             *
             * @return a bool that is true if and only if, the represented number by lsh is lower than
             * the represented number by rhs.
             */
            bool aligned_vectors_is_lower(const std::vector<int> &lhs, const std::vector<int> &rhs) {

                // Check if lhs is lower than rhs
                auto lhs_it = lhs.cbegin();
                auto rhs_it = rhs.cbegin();
                while (rhs_it != rhs.end() && lhs_it != lhs.end() && *lhs_it == *rhs_it) {
                    ++lhs_it;
                    ++rhs_it;
                }

                if (rhs_it != rhs.cend() && lhs_it != lhs.cend()) {
                    return *lhs_it < *rhs_it;
                }

                bool lhs_all_zero = std::all_of(lhs_it, lhs.cend(), [](int i){ return i == 0; });
                bool rhs_all_zero = std::all_of(rhs_it, rhs.cend(), [](int i){ return i == 0; });

                return lhs_all_zero && !rhs_all_zero;
            }

        }
    }
}

#endif //BOOST_REAL_BOUNDARY_HELPER_HPP

#ifndef BOOST_REAL_REAL_HELPERS_HPP
#define BOOST_REAL_REAL_HELPERS_HPP

#include <list>

#include <real/range.hpp>
#include <real/range_helper.hpp>

namespace boost {
    namespace real {
        namespace helper {

            Boundary abs(const boost::real::Boundary& boundary) {
                Boundary result = boundary;
                result.positive = true;
                return result;
            }

            int add_vectors(const std::vector<int> &lhs,
                            int lhs_integers,
                            const std::vector<int> &rhs,
                            int rhs_integers,
                            std::vector<int> &result) {
                int carry = 0;
                int digit;

                std::vector<int> aligned_lhs = lhs;
                std::vector<int> aligned_rhs = rhs;

                boost::real::helper::align_numbers(aligned_lhs, lhs_integers, aligned_rhs, rhs_integers);

                auto lhs_it = aligned_lhs.crbegin();
                auto rhs_it = aligned_rhs.crbegin();

                while(lhs_it != aligned_lhs.crend() and rhs_it != aligned_rhs.crend()) {

                    digit = carry + *lhs_it + *rhs_it;

                    if (digit > 9) {
                        carry = 1;
                        digit -= 10;
                    } else {
                        carry = 0;
                    }

                    result.insert(result.begin(), digit);
                    ++lhs_it;
                    ++rhs_it;
                }

                if (carry == 1) {
                    result.insert(result.begin(), 1);
                    return rhs_integers + 1;
                }

                return rhs_integers;
            }

            /*
             * Pre-condition: lhs >= rhs
             */
            int subtract_vectors(const std::vector<int> &lhs,
                                 int lhs_integers,
                                 const std::vector<int> &rhs,
                                 int rhs_integers,
                                 std::vector<int> &result) {
                int borrow = 0;

                std::vector<int> aligned_lhs = lhs;
                std::vector<int> aligned_rhs = rhs;

                boost::real::helper::align_numbers(aligned_lhs, lhs_integers, aligned_rhs, rhs_integers);

                auto lhs_it = aligned_lhs.rbegin();
                auto rhs_it = aligned_rhs.rbegin();

                while(lhs_it != aligned_lhs.rend() and rhs_it != aligned_rhs.rend()) {

                    if (*lhs_it < borrow) {
                        *lhs_it += (10 - borrow); // Borrow is always 0 or 1, then it is never greater than 10
                    } else {
                        *lhs_it -= borrow;
                        borrow = 0;
                    }

                    if (*lhs_it < *rhs_it) {
                        *lhs_it += 10;
                        borrow++;
                    }

                    result.insert(result.begin(), *lhs_it - *rhs_it);
                    ++lhs_it;
                    ++rhs_it;
                }


                // Remove possible 0 prefix if more significant digits were canceled.
                while (result.front() == 0 && lhs_integers > 1) {
                    result.erase(result.begin());
                    --lhs_integers;
                }

                return lhs_integers;
            }

            void add_boundaries(const boost::real::Boundary &lhs,
                                const boost::real::Boundary &rhs,
                                boost::real::Boundary &result) {
                if (lhs.positive == rhs.positive) {
                    result.integer_part = add_vectors(lhs.digits,
                                                      lhs.integer_part,
                                                      rhs.digits,
                                                      rhs.integer_part,
                                                      result.digits);
                    result.positive = lhs.positive;
                } else if (vector_is_lower(rhs.digits, lhs.digits)) {
                    result.integer_part = subtract_vectors(lhs.digits,
                                                           lhs.integer_part,
                                                           rhs.digits,
                                                           rhs.integer_part,
                                                           result.digits);
                    result.positive = lhs.positive;
                } else {
                    result.integer_part = subtract_vectors(rhs.digits,
                                                           rhs.integer_part,
                                                           lhs.digits,
                                                           lhs.integer_part,
                                                           result.digits);
                    result.positive = rhs.positive;
                }
            }

            void subtract_boundaries(const boost::real::Boundary &lhs,
                                     const boost::real::Boundary &rhs,
                                     boost::real::Boundary &result) {
                if (lhs.positive != rhs.positive) {
                    result.integer_part = add_vectors(lhs.digits,
                                                      lhs.integer_part,
                                                      rhs.digits,
                                                      rhs.integer_part,
                                                      result.digits);
                    result.positive = lhs.positive;
                } else {

                    if (abs(rhs) < abs(lhs)) {
                        result.integer_part = subtract_vectors(lhs.digits,
                                                               lhs.integer_part,
                                                               rhs.digits,
                                                               rhs.integer_part,
                                                               result.digits);
                        result.positive = lhs.positive;
                    } else {
                        result.integer_part = subtract_vectors(rhs.digits,
                                                               rhs.integer_part,
                                                               lhs.digits,
                                                               lhs.integer_part,
                                                               result.digits);
                        result.positive = !lhs.positive;
                    }
                }
            }

            // Multiplies str1 and str2, and prints result.
            int multiply_vectors(
                    const std::vector<int>& lhs,
                    int lhs_integer_part,
                    const std::vector<int>& rhs,
                    int rhs_integer_part,
                    std::vector<int>& result
            ) {

                // will keep the result number in vector
                // in reverse order
                size_t new_size = lhs.size() + rhs.size();

                if (!result.empty()) result.clear();
                for (int i = 0; i < (int)new_size; i++) result.push_back(0);
                // TODO: Check why the assign method crashes.
                //result.assign(new_size, 0);

                // Below two indexes are used to find positions
                // in result.
                auto i_n1 = (int) result.size() - 1;

                // Go from right to left in lhs
                for (int i = (int)lhs.size()-1; i>=0; i--) {
                    int carry = 0;

                    // To shift position to left after every
                    // multiplication of a digit in rhs
                    int i_n2 = 0;

                    // Go from right to left in rhs
                    for (int j = (int)rhs.size()-1; j>=0; j--) {

                        // Multiply current digit of second number with current digit of first number
                        // and add result to previously stored result at current position.
                        int sum = lhs[i]*rhs[j] + result[i_n1 - i_n2] + carry;

                        // Carry for next iteration
                        carry = sum / 10;

                        // Store result
                        result[i_n1 - i_n2] = sum % 10;

                        i_n2++;
                    }

                    // store carry in next cell
                    if (carry > 0) {
                        result[i_n1 - i_n2] += carry;
                    }

                    // To shift position to left after every
                    // multiplication of a digit in lhs.
                    i_n1--;
                }

                int fractional_part = ((int)lhs.size() - lhs_integer_part) + ((int)rhs.size() - rhs_integer_part);

                // ignore 0s from the most right of the integer part
                auto it = result.begin();
                while ((int)result.size() > fractional_part + 1 && *it == 0) {
                    result.erase(it);
                }

                if (result.empty()) {
                    result.assign(1, 0);
                    return 1;
                }

                return (int)result.size() - fractional_part;
            }


            void multiply_boundaries(const boost::real::Boundary &lhs,
                                     const boost::real::Boundary &rhs,
                                     boost::real::Boundary &result) {

                result.positive = lhs.positive == rhs.positive;
                result.integer_part = multiply_vectors(lhs.digits,
                                                       lhs.integer_part,
                                                       rhs.digits,
                                                       rhs.integer_part,
                                                       result.digits);
            }
        }
    }
}

#endif //BOOST_REAL_REAL_HELPERS_HPP

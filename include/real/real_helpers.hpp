#ifndef BOOST_REAL_REAL_HELPERS_HPP
#define BOOST_REAL_REAL_HELPERS_HPP

#include <list>

#include <real/interval.hpp>
#include <real/boundary.hpp>

namespace boost {
    namespace real {
        namespace helper {

            boundary abs(const boundary& b) {
                boundary result = b;
                result.positive = true;
                return result;
            }

            /**
             * @author Laouen Mayal Louan Belloli
             *
             * @brief Implement the addition between two std::vector<int> that represent numbers.
             * The numbers in the vectors are the digit and each vector has a corresponding exponent
             * to correctly align the vectors for the addition.
             *
             * @param lhs - a std::vector<int> representing the left operand.
             * @param lhs_exponent - a int representing the exponent of the left operand.
             * @param rhs - a std::vector<int> representing the right operand.
             * @param rhs_exponent - a int representing the exponent of the right operand.
             * @param result - a std::vector<int> that is used to store the result.
             * @return a integer representing the exponent of the result.
             */
            int add_vectors(const std::vector<int> &lhs,
                            int lhs_exponent,
                            const std::vector<int> &rhs,
                            int rhs_exponent,
                            std::vector<int> &result) {
                int carry = 0;

                int fractional_length = std::max((int)lhs.size() - lhs_exponent, (int)rhs.size() - rhs_exponent);
                int integral_length = std::max(lhs_exponent, rhs_exponent);

                // we walk the numbers from the lowest to the highest digit
                for (int i = fractional_length - 1; i >= -integral_length; i--) {

                    int lhs_digit = 0;
                    if (0 <= lhs_exponent + i && lhs_exponent + i < (int)lhs.size()) {
                        lhs_digit = lhs[lhs_exponent + i];
                    }

                    int rhs_digit = 0;
                    if (0 <= rhs_exponent + i && rhs_exponent + i < (int)rhs.size()) {
                        rhs_digit = rhs[rhs_exponent + i];
                    }

                    int digit = carry + lhs_digit + rhs_digit;

                    if (digit > 9) {
                        carry = 1;
                        digit -= 10;
                    } else {
                        carry = 0;
                    }

                    result.insert(result.begin(), digit);
                }

                if (carry == 1) {
                    result.insert(result.begin(), 1);
                    integral_length++;
                }

                return integral_length;
            }

            /**
             * @author Laouen Mayal Louan Belloli
             *
             * @brief Implement the subtraction between two std::vector<int> that represent numbers.
             * The numbers in the vectors are the digit and each vector has a corresponding exponent
             * to correctly align the vectors for the addition.
             *
             * @pre lhs >= rhs.
             *
             * @param lhs - a std::vector<int> representing the left operand.
             * @param lhs_exponent - a int representing the exponent of the left operand.
             * @param rhs - a std::vector<int> representing the right operand.
             * @param rhs_exponent - a int representing the exponent of the right operand.
             * @param result - a std::vector<int> that is used to store the result.
             * @return a integer representing the exponent of the result.
             */
            int subtract_vectors(const std::vector<int> &lhs,
                                 int lhs_exponent,
                                 const std::vector<int> &rhs,
                                 int rhs_exponent,
                                 std::vector<int> &result) {

                int fractional_length = std::max((int)lhs.size() - lhs_exponent, (int)rhs.size() - rhs_exponent);
                int integral_length = std::max(lhs_exponent, rhs_exponent);

                int borrow = 0;
                // we walk the numbers from the lowest to the highest digit
                for (int i = fractional_length - 1; i >= -integral_length; i--) {

                    int lhs_digit = 0;
                    if (0 <= lhs_exponent + i && lhs_exponent + i < (int)lhs.size()) {
                        lhs_digit = lhs[lhs_exponent + i];
                    }

                    int rhs_digit = 0;
                    if (0 <= rhs_exponent + i && rhs_exponent + i < (int)rhs.size()) {
                        rhs_digit = rhs[rhs_exponent + i];
                    }

                    if (lhs_digit < borrow) {
                        lhs_digit += (10 - borrow);
                    } else {
                        lhs_digit -= borrow;
                        borrow = 0;
                    }

                    if (lhs_digit < rhs_digit) {
                        lhs_digit += 10;
                        borrow++;
                    }

                    result.insert(result.begin(), lhs_digit - rhs_digit);
                }

                return lhs_exponent;
            }

            /**
             * @author Laouen Mayal Louan Belloli
             *
             * @brief Implement the multiplication between two std::vector<int> that represent numbers.
             * The numbers in the vectors are the digit and each vector has a corresponding exponent
             * to correctly align the vectors for the addition.
             *
             * @param lhs - a std::vector<int> representing the left operand.
             * @param lhs_exponent - a int representing the exponent of the left operand.
             * @param rhs - a std::vector<int> representing the right operand.
             * @param rhs_exponent - a int representing the exponent of the right operand.
             * @param result - a std::vector<int> that is used to store the result.
             * @return a integer representing the exponent of the result.
             */
            int multiply_vectors(
                    const std::vector<int>& lhs,
                    int lhs_exponent,
                    const std::vector<int>& rhs,
                    int rhs_exponent,
                    std::vector<int>& result
            ) {

                // will keep the result number in vector in reverse order
                // Digits: .123 | Exponent: -3 | .000123 <--- Number size is the Digits size less the exponent
                // Digits: .123 | Exponent: 2  | 12.3
                size_t new_size = lhs.size() + rhs.size();
                if (lhs_exponent < 0) new_size -= lhs_exponent; // <--- Less the exponent
                if (rhs_exponent < 0) new_size -= rhs_exponent; // <--- Less the exponent

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

                int fractional_part = ((int)lhs.size() - lhs_exponent) + ((int)rhs.size() - rhs_exponent);
                int result_exponent = (int)result.size() - fractional_part;

                return result_exponent;
            }

            /**
             * @author Laouen Mayal Louan Belloli
             *
             * @brief Implement the addition between two boost::real::boundary variables.
             *
             * @param lhs - a boost::real::boundary representing the left operand.
             * @param rhs - a boost::real::boundary representing the right operand.
             * @param result - a boost::real::boundary to store the result.
             */
            void add_boundaries(const boundary &lhs,
                                const boundary &rhs,
                                boundary &result) {
                if (lhs.positive == rhs.positive) {
                    result.exponent = add_vectors(lhs.digits,
                                                  lhs.exponent,
                                                  rhs.digits,
                                                  rhs.exponent,
                                                  result.digits);
                    result.positive = lhs.positive;
                } else if (abs(rhs) < abs(lhs)) {
                    result.exponent = subtract_vectors(lhs.digits,
                                                       lhs.exponent,
                                                       rhs.digits,
                                                       rhs.exponent,
                                                       result.digits);
                    result.positive = lhs.positive;
                } else {
                    result.exponent = subtract_vectors(rhs.digits,
                                                       rhs.exponent,
                                                       lhs.digits,
                                                       lhs.exponent,
                                                       result.digits);
                    result.positive = rhs.positive;
                }

                result.normalize();
            }

            /**
             * @author Laouen Mayal Louan Belloli
             *
             * @brief Implement the subtraction between two boost::real::boundary variables.
             *
             * @param lhs - a boost::real::boundary representing the left operand.
             * @param rhs - a boost::real::boundary representing the right operand.
             * @param result - a boost::real::boundary to store the result.
             */
            void subtract_boundaries(const boundary &lhs,
                                     const boundary &rhs,
                                     boundary &result) {
                if (lhs.positive != rhs.positive) {
                    result.exponent = add_vectors(lhs.digits,
                                                      lhs.exponent,
                                                      rhs.digits,
                                                      rhs.exponent,
                                                      result.digits);
                    result.positive = lhs.positive;
                } else {

                    if (abs(rhs) < abs(lhs)) {
                        result.exponent = subtract_vectors(lhs.digits,
                                                               lhs.exponent,
                                                               rhs.digits,
                                                               rhs.exponent,
                                                               result.digits);
                        result.positive = lhs.positive;
                    } else {
                        result.exponent = subtract_vectors(rhs.digits,
                                                               rhs.exponent,
                                                               lhs.digits,
                                                               lhs.exponent,
                                                               result.digits);
                        result.positive = !lhs.positive;
                    }
                }

                result.normalize();
            }

            /**
             * @author Laouen Mayal Louan Belloli
             *
             * @brief Implement the multiplication between two boost::real::boundary variables.
             *
             * @param lhs - a boost::real::boundary representing the left operand.
             * @param rhs - a boost::real::boundary representing the right operand.
             * @param result - a boost::real::boundary to store the result.
             */
            void multiply_boundaries(const boundary &lhs,
                                     const boundary &rhs,
                                     boundary &result) {

                result.positive = lhs.positive == rhs.positive;
                result.exponent = multiply_vectors(lhs.digits,
                                                       lhs.exponent,
                                                       rhs.digits,
                                                       rhs.exponent,
                                                       result.digits);

                result.normalize();
            }
        }
    }
}

#endif //BOOST_REAL_REAL_HELPERS_HPP
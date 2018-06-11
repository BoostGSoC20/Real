#ifndef BOOST_REAL_REAL_HELPERS_HPP
#define BOOST_REAL_REAL_HELPERS_HPP

#include <list>

namespace boost {
    namespace real {
        namespace helper {

            bool is_lower(const std::vector<int>& lhs, const std::vector<int>& rhs) {

                // Check if lhs is lower than rhs
                auto lhs_it = lhs.cbegin();
                auto rhs_it = rhs.cbegin();
                while (rhs_it != rhs.end() && lhs_it != lhs.end() && *lhs_it == *rhs_it) {
                    ++lhs_it;
                    ++rhs_it;
                }

                return rhs_it != rhs.end() && lhs_it != lhs.end() && *lhs_it < *rhs_it;
            }

            /*
             * Align two numbers so the digits positions corresponds
             */
            void align_numbers(std::vector<int>& lhs, int& lhs_integers, std::vector<int>& rhs, int& rhs_integers) {
                while (lhs_integers < rhs_integers) {
                    lhs.insert(lhs.begin(), 0);
                    lhs_integers++;
                }

                while (rhs_integers < lhs_integers) {
                    lhs.insert(lhs.begin(), 0);
                    rhs_integers++;
                }

                while (lhs.size() < rhs.size()) {
                    lhs.push_back(0);
                }

                while (rhs.size() < lhs.size()) {
                    rhs.push_back(0);
                }
            }

            std::string print_digits(const std::vector<int>& digits, int integer_part) {
                std::string result = "";

                for (int i = 0; i < integer_part; ++i) {
                    result += std::to_string(digits[i]);
                }

                result += ".";

                for (int i = integer_part; i < (int)digits.size(); ++i) {
                    result += digits[i];
                }

                return result;
            }

            int add_bounds(std::vector<int>& lhs, int lhs_integers, std::vector<int>& rhs, int rhs_integers, std::vector<int>& result) {
                int carry = 0;
                int digit;

                boost::real::helper::align_numbers(lhs, lhs_integers, rhs, rhs_integers);

                auto lhs_it = lhs.crbegin();
                auto rhs_it = rhs.crbegin();

                while(lhs_it != lhs.crend() and rhs_it != rhs.crend()) {

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
            int subtract_bounds(std::vector<int>& lhs, int lhs_integers, std::vector<int>& rhs, int rhs_integers, std::vector<int>& result) {
                int borrow = 0;

                boost::real::helper::align_numbers(lhs, lhs_integers, rhs, rhs_integers);

                auto lhs_it = lhs.rbegin();
                auto rhs_it = rhs.rbegin();

                while(lhs_it != lhs.rend() and rhs_it != rhs.rend()) {

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
                while (result.front() == 0 && lhs_integers > 0) {
                    result.erase(result.begin());
                    --lhs_integers;
                }

                return lhs_integers;
            }
        }
    }
}

#endif //BOOST_REAL_REAL_HELPERS_HPP

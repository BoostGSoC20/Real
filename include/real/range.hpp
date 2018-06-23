#ifndef BOOST_REAL_RANGE_HPP
#define BOOST_REAL_RANGE_HPP

#include <vector>

#include <real/range_helper.hpp>

namespace boost {
    namespace real {
        struct Bound {
            std::vector<int> digits = {};
            int integer_part = 0;
            bool positive = true;

            Bound() = default;

            Bound(const boost::real::Bound& other) = default;

            Bound& operator=(const boost::real::Bound& other) = default;

            bool operator<(const boost::real::Bound& other) {

                boost::real::helper::align_numbers(
                        this->digits,
                        this->integer_part,
                        other.digits,
                        other.integer_part
                );

                if (this->positive != other.positive) {
                    return !this->positive;
                }

                if (this->positive) {
                    return boost::real::helper::vector_is_lower(this->digits, other.digits);
                }

                return boost::real::helper::vector_is_lower(other.digits, this->digits);
            }

            std::string as_string() {
                std::string result = "";

                if (!this->positive) {
                    result = "-";
                }

                for (int i = 0; i < this->integer_part; ++i) {
                    result += std::to_string(this->digits[i]);
                }

                result += ".";

                for (int i = this->integer_part; i < (int)this->digits.size(); ++i) {
                    result += std::to_string(this->digits[i]);
                }

                if (result.back() == '.') {
                    result.pop_back();
                }

                return result;
            }

            void swap(boost::real::Bound& other) {
                this->digits.swap(other.digits);
                std::swap(this->integer_part, other.integer_part);
                std::swap(this->positive, other.positive);
            }

            void push_back(int digit) {
                this->digits.push_back(digit);
            }

            void push_front(int digit) {
                this->digits.insert(this->digits.begin(), digit);
            }

            void clear() {
                this->digits.clear();
            }

            int operator[](int n) {
                return this->digits[n];
            }

            size_t size() {
                return this->digits.size();
            }
        };

        struct Range {
            boost::real::Bound lower_bound;
            boost::real::Bound upper_bound;

            void swap_bounds() {
                this->lower_bound.swap(this->upper_bound);
            }
        };
    }
}

std::ostream& operator<<(std::ostream& os, const boost::real::Range& range) {
    std::string lb = range.lower_bound.as_string();
    std::string ub = range.upper_bound.as_string();

    if (lb == ub) {
        os << lb;
    } else {
        os << '[' << lb << ", " << ub << ']';
    }
    return os;
}

#endif //BOOST_REAL_RANGE_HPP

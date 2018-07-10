#ifndef BOOST_REAL_RANGE_HPP
#define BOOST_REAL_RANGE_HPP

#include <vector>

#include <real/range_helper.hpp>

namespace boost {
    namespace real {
        struct Boundary {
            std::vector<int> digits = {};
            int exponent = 0;
            bool positive = true;

            Boundary() = default;

            Boundary(const boost::real::Boundary& other) = default;

            Boundary& operator=(const boost::real::Boundary& other) = default;

            bool operator<(const boost::real::Boundary& other) const {

                if (this->positive != other.positive) {
                    return !this->positive;
                }

                if (this->positive) {
                    if (this->exponent == other.exponent) {
                        return boost::real::helper::vector_is_lower(this->digits, other.digits);
                    }

                    return this->exponent < other.exponent;
                }

                if (this->exponent == other.exponent) {
                    return boost::real::helper::vector_is_lower(other.digits, this->digits);
                }

                return other.exponent < this->exponent;
            }

            std::string as_string() const {
                std::string result = "";

                if (!this->positive) {
                    result = "-";
                }

                for (int i = 0; i < this->exponent; ++i) {
                    result += std::to_string(this->digits[i]);
                }

                result += ".";

                for (int i = this->exponent; i < (int)this->digits.size(); ++i) {
                    result += std::to_string(this->digits[i]);
                }

                if (result.back() == '.') {
                    result.pop_back();
                }

                return result;
            }

            void swap(boost::real::Boundary& other) {
                this->digits.swap(other.digits);
                std::swap(this->exponent, other.exponent);
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

            int& operator[](int n) {
                return this->digits[n];
            }

            size_t size() {
                return this->digits.size();
            }
        };

        struct interval {
            boost::real::Boundary lower_bound;
            boost::real::Boundary upper_bound;

            void swap_bounds() {
                this->lower_bound.swap(this->upper_bound);
            }

            bool operator<(const boost::real::interval& other) const {
                return this->upper_bound < other.lower_bound;
            }

            bool positive() const {
                // If the lower bound of a range is positive, then the upper bound is also positive
                // and the range is fully contained in the positive number line
                return this->lower_bound.positive;
            }

            bool negative() const {
                // If the upper bound of a range is negative, then the lower bound is also negative
                // and the range is fully contained in the negative number line
                return !this->upper_bound.positive;
            }
        };
    }
}

std::ostream& operator<<(std::ostream& os, const boost::real::interval& range) {
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

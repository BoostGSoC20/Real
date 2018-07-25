#ifndef BOOST_REAL_BOUNDARY_HPP
#define BOOST_REAL_BOUNDARY_HPP

#include <vector>
#include <real/boundary_helper.hpp>

namespace boost {
    namespace real {
        struct boundary {
            std::vector<int> digits = {};
            int exponent = 0;
            bool positive = true;

            boundary() = default;

            boundary(const boundary &other) = default;

            boundary &operator=(const boundary &other) = default;

            bool operator<(const boundary &other) const {

                if (this->positive != other.positive) {
                    return !this->positive;
                }

                if (this->positive) {
                    if (this->exponent == other.exponent) {
                        return boost::real::helper::aligned_vectors_is_lower(this->digits,
                                                                             other.digits);
                    }

                    return this->exponent < other.exponent;
                }

                if (this->exponent == other.exponent) {
                    return boost::real::helper::aligned_vectors_is_lower(other.digits,
                                                                         this->digits);
                }

                return other.exponent < this->exponent;
            }

            std::basic_string<char> as_string() const {
                std::basic_string<char> result = "";

                if (!this->positive) {
                    result = "-";
                }

                if (this->exponent <= 0) {
                    result = "0.";

                    for (int i = this->exponent; i < (int) this->digits.size(); ++i) {
                        if (i < 0) {
                            result += "0";
                        } else {
                            result += std::to_string(this->digits[i]);
                        }
                    }
                } else {

                    int digit_amount = std::max(this->exponent, (int) this->digits.size());
                    for (int i = 0; i < digit_amount; ++i) {

                        if (i == this->exponent) {
                            result += ".";
                        }

                        if (i < (int) this->digits.size()) {
                            result += std::to_string(this->digits[i]);
                        } else {
                            result += "0";
                        }
                    }

                    if (result.back() == '.') {
                        result.pop_back();
                    }
                }


                return result;
            }

            void swap(boundary &other) {
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

            int &operator[](int n) {
                return this->digits[n];
            }

            unsigned long size() {
                return this->digits.size();
            }
        };
    }
}

#endif //BOOST_REAL_BOUNDARY_HPP

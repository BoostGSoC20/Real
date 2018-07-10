#ifndef BOOST_REAL_REAL_EXPLICIT_HPP
#define BOOST_REAL_REAL_EXPLICIT_HPP

#include <vector>
#include <iostream>
#include <initializer_list>

#include <real/real_exception.hpp>
#include <real/real_helpers.hpp>
#include <real/interval.hpp>

namespace boost {
    namespace real {

        // Explicit number definition
        class real_explicit {

            // Number representation as a vector of digits with an integer part and a sign (+/-)
            std::vector<int> _digits = {0};
            int _exponent = 1;
            bool _positive = true;

            // The number max precision is the same as the explicit number digits size
            int _max_precision = 1;
        public:

            class const_precision_iterator {
            private:

                // Iterator precision
                int _n = 0;

                // Internal number to iterate
                real_explicit const* _real_ptr = nullptr;

                void check_and_swap_bounds() {
                    if (!this->_real_ptr->_positive) {
                        this->range.swap_bounds();
                    }
                }

            public:

                // Number range boundaries
                boost::real::interval range;

                const_precision_iterator() = default;

                const_precision_iterator(const const_precision_iterator& other) = default;

                explicit const_precision_iterator(real_explicit const* ptr) : _real_ptr(ptr) {
                    // Lower bound and upper bounds of the number integer part
                    this->range.lower_bound.exponent = this->_real_ptr->_exponent;
                    this->range.upper_bound.exponent = this->_real_ptr->_exponent;
                    this->range.lower_bound.positive = this->_real_ptr->_positive;
                    this->range.upper_bound.positive = this->_real_ptr->_positive;

                    for(int i = 0; i < this->_real_ptr->_exponent; i++) {
                        ++(*this);
                    }
                }

                /**
                 * @brief Increases the interval number precision, the interval becomes smaller and
                 * the number error is decreased.
                 *
                 * WARNING: This method asumes the current precision is greater than the integer part
                 * of the number. Otherwise, the number will be miss-represented because the tuncation
                 * is made before the fractional part.
                 */
                void operator++() {

                    // If the explicit number full precision has been already reached,
                    // then just add zeros at the boundaries ends
                    if (this->_n >= (int)this->_real_ptr->_digits.size()) {
                        this->range.lower_bound.push_back(0);
                        this->range.upper_bound.push_back(0);
                        this->_n++;
                        return;
                    }

                    // If the number is negative, boundaries are interpreted as mirrored:
                    // First, the operation is made as positive, and after bound calculation
                    // bounds are swapped to come back to the negative representation.
                    this->check_and_swap_bounds();

                    // If the explicit number just reaches the full precision
                    // then set both boundaries equals
                    if (this->_n == (int)this->_real_ptr->_digits.size() - 1) {

                        this->range.lower_bound.push_back(this->_real_ptr->_digits[this->_n]);
                        this->range.upper_bound = this->range.lower_bound;


                    } else {

                        // If the explicit number didn't reaches the full precision
                        // then the number interval is defined by truncation.
                        this->range.lower_bound.push_back(this->_real_ptr->_digits[this->_n]);

                        this->range.upper_bound.clear();
                        this->range.upper_bound.digits.resize(this->range.lower_bound.size());

                        int carry = 1;
                        for (int i = (int)this->range.lower_bound.size() - 1; i >= 0; --i) {
                            if (this->range.lower_bound[i] + carry == 10) {
                                this->range.upper_bound[i] = 0;
                            } else {
                                this->range.upper_bound[i] = this->range.lower_bound[i] + carry;
                                carry = 0;
                            }
                        }

                        if (carry > 0) {
                            this->range.upper_bound.push_front(carry);
                            this->range.upper_bound.exponent = this->range.lower_bound.exponent + 1;
                        } else {
                            this->range.upper_bound.exponent = this->range.lower_bound.exponent;
                        }
                    }

                    this->check_and_swap_bounds();
                    this->_n++;
                }
            };

            real_explicit() = default;

            real_explicit(const real_explicit& other)  = default;

            real_explicit(std::initializer_list<int> digits, int exponent) :
                    _digits(digits),
                    _exponent(exponent),
                    _max_precision((int)this->_digits.size())
            {};

            real_explicit(std::initializer_list<int> digits, int exponent, bool positive):
                    _digits(digits),
                    _exponent(exponent),
                    _positive(positive),
                    _max_precision((int)this->_digits.size())
            {};

            int max_precision() const {
                return this->_max_precision;
            }

            const_precision_iterator cbegin() const {
                return const_precision_iterator(this);
            }

            int operator[](unsigned int n) const {
                if (n < this->_digits.size()) {
                    return this->_digits.at(n);
                }

                return 0;
            }

            real_explicit& operator=(const real_explicit& other) = default;
        };
    }
}

std::ostream& operator<<(std::ostream& os, const boost::real::real_explicit& r) {
    auto it = r.cbegin();
    for (int i = 0; i <= r.max_precision(); i++) {
        ++it;
    }
    os << it.range;
    return os;
}


#endif //BOOST_REAL_REAL_EXPLICIT_HPP

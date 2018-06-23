#ifndef BOOST_REAL_REAL_EXPLICIT_HPP
#define BOOST_REAL_REAL_EXPLICIT_HPP

#include <vector>
#include <iostream>
#include <initializer_list>

#include <real/real_exception.hpp>
#include <real/real_helpers.hpp>
#include <real/range.hpp>

namespace boost {
    namespace real {

        // Explicit number definition
        class Real_explicit {

            // Number representation as a vector of digits with an integer part and a sign (+/-)
            std::vector<int> _digits = {0};
            int _integer_part = 1;
            bool _positive = true;

            // The number max presition is the same as the explicit number digits size
            int _max_precision = 1;
        public:

            class const_precision_iterator {
            private:

                // Iterator precision
                int _n = 0;

                // Internal number to iterate
                Real_explicit const* _real_ptr = nullptr;

                void check_and_swap_bounds() {
                    if (!this->_real_ptr->_positive) {
                        this->range.swap_bounds();
                    }
                }

            public:

                // Number range boundaries
                boost::real::Range range;

                const_precision_iterator() = default;

                const_precision_iterator(const const_precision_iterator& other) = default;

                explicit const_precision_iterator(Real_explicit const* ptr) : _real_ptr(ptr) {
                    auto first_integer = this->_real_ptr->_digits.cbegin();
                    auto last_integer = this->_real_ptr->_digits.cbegin();

                    // Lower bound and upper bounds of the number integer part
                    for (int i = 0; i < this->_real_ptr->_integer_part; i++) ++last_integer;
                    this->range.lower_bound.digits.insert(this->range.lower_bound.digits.end(), first_integer, last_integer);
                    this->range.upper_bound.digits.insert(this->range.upper_bound.digits.end(), first_integer, last_integer);
                    this->range.upper_bound.digits.at(this->_real_ptr->_integer_part - 1)++;
                    this->range.lower_bound.integer_part = this->_real_ptr->_integer_part;
                    this->range.upper_bound.integer_part = this->_real_ptr->_integer_part;
                    this->range.lower_bound.positive = this->_real_ptr->_positive;
                    this->range.upper_bound.positive = this->_real_ptr->_positive;
                    this->_n = this->_real_ptr->_integer_part;
                    this->check_and_swap_bounds();
                }

                void operator++() {

                    // If the explicit number full precision is reached,
                    // then just add zeros at the bounds ends
                    if (this->_n >= (int)this->_real_ptr->_digits.size()) {
                        this->range.lower_bound.push_back(0);
                        this->range.upper_bound.push_back(0);
                        this->_n++;
                        return;
                    }

                    this->range.lower_bound.push_back(this->_real_ptr->_digits[this->_n]);

                    if (this->_n == (int)this->_real_ptr->_digits.size() - 1) {
                        this->range.upper_bound = this->range.lower_bound;
                        this->_n++;
                        return;
                    }

                    // If the number is negative, bounds are interpreted as mirrored:
                    // First, the operation is made as positive, and after bound calculation
                    // bounds are swapped to come back to the negative representation.
                    this->check_and_swap_bounds();

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
                        this->range.upper_bound.integer_part = this->range.lower_bound.integer_part + 1;
                    } else {
                        this->range.upper_bound.integer_part = this->range.lower_bound.integer_part;
                    }

                    // If the number is negative, the bounds are interpreted as mirrored.
                    this->check_and_swap_bounds();
                    this->_n++;
                }
            };

            Real_explicit() = default;

            Real_explicit(const Real_explicit& other)  = default;

            Real_explicit(std::initializer_list<int> digits, int integer_part) :
                    _digits(digits),
                    _integer_part(integer_part),
                    _max_precision((int)this->_digits.size())
            {};

            Real_explicit(std::initializer_list<int> digits, int integer_part, bool positive):
                    _digits(digits),
                    _integer_part(integer_part),
                    _positive(positive),
                    _max_precision((int)this->_digits.size())
            {};

            const_precision_iterator cbegin() const {
                return const_precision_iterator(this);
            }

            int operator[](int n) const {
                if (n < (int)this->_digits.size()) {
                    return this->_digits.at(n);
                }

                return 0;
            }

            Real_explicit& operator=(const Real_explicit& other) = default;
        };
    }
}

std::ostream& operator<<(std::ostream& os, const boost::real::Real_explicit& r) {
    auto it = r.cbegin();
    for (int i = 0; i <= r._max_precision; i++) {
        ++it;
    }
    os << it.range;
    return os;
}


#endif //BOOST_REAL_REAL_EXPLICIT_HPP

#ifndef BOOST_REAL_REAL_EXPLICIT_HPP
#define BOOST_REAL_REAL_EXPLICIT_HPP

#include <vector>
#include <iostream>
#include <initializer_list>
#include <string>

#include <real/real_exception.hpp>
#include <real/real_helpers.hpp>
#include <real/interval.hpp>

namespace boost {
    namespace real {

        // Explicit number definition
        class real_explicit {

            // Number representation as a vector of digits with an integer part and a sign (+/-)
            // TODO: Replace this by a boost::real::boundary type
            // TODO: Add normalizations to the constructors
            std::vector<int> _digits = {};
            int _exponent = 1;
            bool _positive = true;

            // The number max precision is the same as the explicit number digits size
            int _max_precision = 1;
        public:

            class const_precision_iterator {
            private:

                // Iterator precision
                int _n;

                // Internal number to iterate
                real_explicit const* _real_ptr = nullptr;

                void check_and_swap_boundaries() {
                    if (!this->_real_ptr->_positive) {
                        this->approximation_interval.swap_bounds();
                    }
                }

            public:

                // Number approximation_interval boundaries
                boost::real::interval approximation_interval;

                const_precision_iterator() = default;

                const_precision_iterator(const const_precision_iterator& other) = default;

                explicit const_precision_iterator(real_explicit const* ptr) : _n(1), _real_ptr(ptr) {
                    this->approximation_interval.lower_bound.exponent = this->_real_ptr->_exponent;
                    this->approximation_interval.upper_bound.exponent = this->_real_ptr->_exponent;
                    this->approximation_interval.lower_bound.positive = this->_real_ptr->_positive;
                    this->approximation_interval.upper_bound.positive = this->_real_ptr->_positive;

                    int first_digit = this->_real_ptr->_digits[0];
                    this->approximation_interval.lower_bound.digits.push_back(first_digit);

                    if (first_digit == 10) {
                        this->approximation_interval.upper_bound.digits.push_back(1);
                        this->approximation_interval.upper_bound.exponent++;
                    } else {
                        this->approximation_interval.upper_bound.digits.push_back(first_digit + 1);
                    }

                    this->check_and_swap_boundaries();
                }

                /**
                 * @brief Increases the approximation interval number precision,
                 * the interval becomes smaller and the number error is decreased.
                 */
                void operator++() {
                    this->iterate_n_times(1);
                }

                void iterate_n_times(int n) {
                    // If the explicit number full precision has been already reached (the end)
                    // is the end of the iterator
                    if (this->_n >= (int)this->_real_ptr->_digits.size()) {
                        // TODO: Remove commented lines that are deprecatod code
                        //this->approximation_interval.lower_bound.push_back(0);
                        //this->approximation_interval.upper_bound.push_back(0);
                        //this->_n++;
                        return;
                    }

                    // If the number is negative, boundaries are interpreted as mirrored:
                    // First, the operation is made as positive, and after boundary calculation
                    // boundaries are swapped to come back to the negative representation.
                    this->check_and_swap_boundaries();

                    // If the explicit number just reaches the full precision (the end)
                    // then set both boundaries are equals
                    if (this->_n + n >= (int)this->_real_ptr->_digits.size()) {

                        for(int i = this->_n; i < (int)this->_real_ptr->_digits.size(); i++) {
                            this->approximation_interval.lower_bound.push_back(this->_real_ptr->_digits[i]);
                        }
                        this->approximation_interval.upper_bound = this->approximation_interval.lower_bound;


                    } else {

                        // If the explicit number didn't reaches the full precision (the end)
                        // then the number interval is defined by truncation.

                        for(int i = 0; i < n; i++) {
                            this->approximation_interval.lower_bound.push_back(this->_real_ptr->_digits[this->_n]);
                        }

                        this->approximation_interval.upper_bound.clear();
                        this->approximation_interval.upper_bound.digits.resize(this->approximation_interval.lower_bound.size());

                        int carry = 1;
                        for (int i = (int)this->approximation_interval.lower_bound.size() - 1; i >= 0; --i) {
                            if (this->approximation_interval.lower_bound[i] + carry == 10) {
                                this->approximation_interval.upper_bound[i] = 0;
                            } else {
                                this->approximation_interval.upper_bound[i] = this->approximation_interval.lower_bound[i] + carry;
                                carry = 0;
                            }
                        }

                        if (carry > 0) {
                            this->approximation_interval.upper_bound.push_front(carry);
                            this->approximation_interval.upper_bound.exponent = this->approximation_interval.lower_bound.exponent + 1;
                        } else {
                            this->approximation_interval.upper_bound.exponent = this->approximation_interval.lower_bound.exponent;
                        }
                    }

                    // Left normalization of boundaries representation
                    this->approximation_interval.lower_bound.normalize_left();
                    this->approximation_interval.upper_bound.normalize_left();

                    this->check_and_swap_boundaries();
                    this->_n = std::min(this->_n + n, (int)this->_real_ptr->_digits.size());
                }

                bool operator==(const const_precision_iterator& other) const {
                    // uninitialized iterators are never equals
                    if (this->_real_ptr == nullptr || other._real_ptr == nullptr) {
                        return false;
                    }

                    return (other._real_ptr == this->_real_ptr) &&
                            (other._n == this->_n) &&
                            (other.approximation_interval == this->approximation_interval);
                }
            };

            real_explicit() = default;

            real_explicit(const real_explicit& other)  = default;

            explicit real_explicit(const std::string& number) {
                // Check that is not an empty string
                if (number.length() == 0) {
                    throw boost::real::invalid_string_number();
                }

                // Check that there is no more that one '.' symbol
                unsigned int dot_amount = 0;
                for (const auto& c : number ) {
                    if (c == '.' && dot_amount >= 1) {
                        throw boost::real::invalid_string_number();
                    } else if (c == '.') {
                        dot_amount++;
                    }
                }

                int exponent = 0;
                dot_amount = 0;

                // Check whether the number is explicitly specified as positive or negative
                unsigned int first_index = 0;
                if (number.at(first_index) == '+') {
                    this->_positive = true;
                    first_index++;
                } else if (number.at(first_index) == '-') {
                    this->_positive = false;
                    first_index++;
                }

                // Remove zeros from the lefts side
                // Note: We know at this point that number.length > 0 because the first check
                unsigned int last_index = (unsigned int)number.length() - 1;
                while (last_index > first_index && (number.at(last_index) == '0' || number.at(last_index) == '.')) {
                    if (number.at(last_index) == '.') {
                        dot_amount++;
                    }
                    last_index--;
                }

                // The number is all composed by zeros, then it is zero
                if (last_index == first_index && number.at(last_index) == '0') {
                    this->_digits = {0};
                    this->_exponent = 1;
                    return;
                }

                // Remove zeros from the right side
                // Note: if the number is all made by zeros, then the code never reaches this part
                // This is why we don't need to check that first_index is lower than the string length
                while (number.at(first_index) == '0') {
                    first_index++;
                }

                if (number.at(first_index) == '.') {
                    dot_amount++;
                    first_index++;
                    while (number.at(first_index) == '0') {
                        first_index++;
                        exponent--;
                    }
                }

                for (unsigned int i = first_index; i <= last_index; i++) {

                    if (number.at(i) == '.') {
                        dot_amount++;

                    } else {
                        // This will only affect if the '.' appears, in that case, exponent
                        // wasn't negative and no inconsistency is made.
                        if (dot_amount == 0)  exponent++;
                        try {
                            this->_digits.push_back(number.at(i) - '0');
                        } catch (const std::invalid_argument& e) {
                            throw boost::real::invalid_string_number();
                        }

                    }
                }

                this->_exponent = exponent;
            };

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

            int exponent() const {
                return this->_exponent;
            }

            bool positive() const {
                return this->_positive;
            }

            const std::vector<int>& digits() const {
                return this->_digits;
            }

            const_precision_iterator cbegin() const {
                return const_precision_iterator(this);
            }

            const_precision_iterator cend() const {
                const_precision_iterator it(this);
                it.iterate_n_times((int)this->_digits.size() + 1);
                return it;
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
    os << it.approximation_interval;
    return os;
}


#endif //BOOST_REAL_REAL_EXPLICIT_HPP

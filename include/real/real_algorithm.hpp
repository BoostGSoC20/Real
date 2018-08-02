#ifndef BOOST_REAL_REAL_ALGORITHM_HPP
#define BOOST_REAL_REAL_ALGORITHM_HPP

#include <real/interval.hpp>

namespace boost {
    namespace real {

        class real_algorithm {

            // Number representation as a function that return the number digits
            // an integer part and a sign (+/-)
            int (*_get_nth_digit)(unsigned int) = [](unsigned int n) { return 0; };
            int _exponent = 1;
            bool _positive = true;

            // The number max precision is the same as the explicit number digits size
            int _max_precision = 10;

        public:

            class const_precision_iterator {
            private:

                // Iterator precision
                int _n = 0;

                // Internal number to iterate
                real_algorithm const* _real_ptr = nullptr;

                void check_and_swap_bounds() {
                    if (!this->_real_ptr->_positive) {
                        this->approximation_interval.swap_bounds();
                    }
                }

            public:

                // Number approximation_interval boundaries
                boost::real::interval approximation_interval;

                const_precision_iterator() = default;

                const_precision_iterator(const const_precision_iterator& other) = default;

                explicit const_precision_iterator(real_algorithm const* ptr) : _real_ptr(ptr) {

                    for (int i = 0; i < this->_real_ptr->_exponent; i++) {
                        this->approximation_interval.lower_bound.push_back((*this->_real_ptr)[i]);
                        this->approximation_interval.upper_bound.push_back((*this->_real_ptr)[i]);
                    }

                    this->approximation_interval.upper_bound.digits.at((uint)this->_real_ptr->_exponent - 1)++;
                    this->approximation_interval.lower_bound.exponent = this->_real_ptr->_exponent;
                    this->approximation_interval.upper_bound.exponent = this->_real_ptr->_exponent;
                    this->approximation_interval.lower_bound.positive = this->_real_ptr->_positive;
                    this->approximation_interval.upper_bound.positive = this->_real_ptr->_positive;
                    this->_n = this->_real_ptr->_exponent;
                    this->check_and_swap_bounds();
                }

                void operator++() {

                    // If the number is negative, bounds are interpreted as mirrored:
                    // First, the operation is made as positive, and after bound calculation
                    // bounds are swapped to come back to the negative representation.
                    this->check_and_swap_bounds();

                    this->approximation_interval.lower_bound.push_back((*this->_real_ptr)[this->_n]);

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

                    this->check_and_swap_bounds();
                    this->_n++;
                }
            };

            real_algorithm() = default;

            real_algorithm(const real_algorithm& other) = default;

            explicit real_algorithm(int (*get_nth_digit)(unsigned int), int exponent)
                    : _get_nth_digit(get_nth_digit), _exponent(exponent) {}

            explicit real_algorithm(int (*get_nth_digit)(unsigned int),
                                    int exponent,
                                    bool positive)
                    : _get_nth_digit(get_nth_digit),
                      _exponent(exponent),
                      _positive(positive) {}

            explicit real_algorithm(int (*get_nth_digit)(unsigned int),
                                    int exponent,
                                    bool positive,
                                    int max_precision)
                    : _get_nth_digit(get_nth_digit),
                      _exponent(exponent),
                      _positive(positive),
                      _max_precision(max_precision) {}

            int max_precision() const {
                return this->_max_precision;
            }

            const_precision_iterator cbegin() const {
                return const_precision_iterator(this);
            }

            int operator[](unsigned int n) const { return this->_get_nth_digit(n); }

            real_algorithm& operator=(const real_algorithm& other) = default;
        };
    }
}

std::ostream& operator<<(std::ostream& os, const boost::real::real_algorithm& r) {
    auto it = r.cbegin();
    for (int i = 0; i <= r.max_precision(); i++) {
        ++it;
    }
    os << it.approximation_interval;
    return os;
}

#endif //BOOST_REAL_REAL_ALGORITHM_HPP

#ifndef BOOST_REAL_REAL_ALGORITHM_HPP
#define BOOST_REAL_REAL_ALGORITHM_HPP

#include <real/interval.hpp>

namespace boost {
    namespace real {

        class real_algorithm {

            // Number representation as a function that return the number digits
            // an integer part and a sign (+/-)
            int (*_get_nth_digit)(unsigned int);
            int _exponent;
            bool _positive;

            // TODO: Check a better way to set a max precision
            // The number max precision is the same as the explicit number digits size
            int _max_precision = 10;

        public:

            class const_precision_iterator {
            private:

                // Iterator precision
                int _n = 0;

                // Internal number to iterate
                real_algorithm const* _real_ptr = nullptr;

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

                explicit const_precision_iterator(real_algorithm const* ptr) : _n(1), _real_ptr(ptr) {

                    this->approximation_interval.lower_bound.exponent = this->_real_ptr->_exponent;
                    this->approximation_interval.upper_bound.exponent = this->_real_ptr->_exponent;
                    this->approximation_interval.lower_bound.positive = this->_real_ptr->_positive;
                    this->approximation_interval.upper_bound.positive = this->_real_ptr->_positive;

                    int first_digit = (*this->_real_ptr)[0];
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

                    // If the number is negative, bounds are interpreted as mirrored:
                    // First, the operation is made as positive, and after bound calculation
                    // bounds are swapped to come back to the negative representation.
                    this->check_and_swap_boundaries();

                    for (int i = 0; i < n; i++) {
                        this->approximation_interval.lower_bound.push_back((*this->_real_ptr)[this->_n + i]);
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

                    // Left normalization of boundaries representation
                    this->approximation_interval.lower_bound.normalize_left();
                    this->approximation_interval.upper_bound.normalize_left();

                    this->check_and_swap_boundaries();
                    this->_n += n;
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

            real_algorithm() = default;

            real_algorithm(const real_algorithm& other) = default;

            explicit real_algorithm(int (*get_nth_digit)(unsigned int), int exponent)
                    : _get_nth_digit(get_nth_digit), _exponent(exponent), _positive(true) {}

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

            int exponent() const {
                return this->_exponent;
            }

            bool positive() const {
                return this->_positive;
            }

            const_precision_iterator cbegin() const {
                return const_precision_iterator(this);
            }

            const_precision_iterator cend() const {
                const_precision_iterator it(this);
                it.iterate_n_times(this->_max_precision - 1);
                return it;
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

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

        /**
         * @author Laouen Mayal Louan Belloli
         *
         * @brief boost::real::real_explicit is a C++ class that fully represents real numbers as
         * a vector of digits, a sign and an exponent.
         */
        class real_explicit {

            // Number representation as a vector of digits with an integer part and a sign (+/-)
            // TODO: Replace this by a boost::real::boundary type
            // TODO: Add normalizations to the constructors
            std::vector<int> _digits = {};
            int _exponent = 1;
            bool _positive = true;

            // The number max precision is the same as the explicit number digits size
            unsigned int _maximum_precision = 1;
        public:

            /**
             * @author Laouen Mayal Louan Belloli
             *
             * @brief is a forward iterator that iterates a boost::real::real_explicit number approximation
             * intervals. The iterator calculates the initial interval with the initial precision and
             * then it increase the precision in each iteration (++) and recalculate the interval.
             */
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

                /**
                 * @brief **Default constructor:** Constructs an empty
                 * boost::real::real_explicit::const_precision_iterator that points to nullptr.
                 */
                const_precision_iterator() = default;

                /**
                 * @brief **Copy constructor:**
                 * Construct a new boost::real::real_explicit::const_precision_iterator which is
                 * a copy of the other iterator.
                 *
                 * @param other - the boost::real::real::const_precision_iterator to copy.
                 */
                const_precision_iterator(const const_precision_iterator& other) = default;

                /**
                 * @brief *Pointer constructor:* Construct a new boost::real::real_explicit::const_precision_iterator
                 * pointing to the boost::real::real_explicit number to iterate the number approximation intervals.
                 *
                 * The iterator will start pointing the lowest precision interval.
                 *
                 * @param real_number - the boost::real::real number to iterate.
                 */
                explicit const_precision_iterator(real_explicit const* real_number) : _n(1), _real_ptr(real_number) {
                    this->approximation_interval.lower_bound.exponent = this->_real_ptr->_exponent;
                    this->approximation_interval.upper_bound.exponent = this->_real_ptr->_exponent;
                    this->approximation_interval.lower_bound.positive = this->_real_ptr->_positive;
                    this->approximation_interval.upper_bound.positive = this->_real_ptr->_positive;

                    int first_digit = this->_real_ptr->_digits[0];
                    this->approximation_interval.lower_bound.digits.push_back(first_digit);

                    if (first_digit == 9) {
                        this->approximation_interval.upper_bound.digits.push_back(1);
                        this->approximation_interval.upper_bound.exponent++;
                    } else if (this->_n < (int)this->_real_ptr->_digits.size()) {
                        this->approximation_interval.upper_bound.digits.push_back(first_digit + 1);
                    } else {
                        this->approximation_interval.upper_bound.digits.push_back(first_digit);
                    }

                    this->check_and_swap_boundaries();
                }

                /**
                 * @brief It recalculates the approximation interval boundaries increasing the used
                 * precision, the new pointed approximation interval is smaller than the current one.
                 */
                void operator++() {
                    this->iterate_n_times(1);
                }

                /**
                 * @brief It recalculates the approximation interval boundaries increasing the used
                 * precision n times, the new pointed approximation interval is smaller than the current one.
                 */
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

                /**
                 * @brief It compare by value equality; two boost::real::real_explicit::const_precision_iterators
                 * are equals if they are pointing to the same real number and are in the same precision iteration.
                 *
                 * @param other - A boost::real::real_explicit::const_precision_iterator that is the right side operand
                 * @return a bool that is true if and only if both iterators are equals.
                 */
                bool operator==(const const_precision_iterator& other) const {
                    // uninitialized iterators are never equals
                    if (this->_real_ptr == nullptr || other._real_ptr == nullptr) {
                        return false;
                    }

                    return (other._real_ptr == this->_real_ptr) &&
                            (other._n == this->_n) &&
                            (other.approximation_interval == this->approximation_interval);
                }

                /**
                 * @brief It compare by value not equal; two boost::real::real_explicit::const_precision_iterators.
                 *
                 * @param other - A boost::real::real_explicit::const_precision_iterator that is the right side operand
                 * @return a bool that is true if and only if both iterators are not equals.
                 */
                bool operator!=(const const_precision_iterator& other) const {
                    return !(*this == other);
                }
            };

            /**
             * @brief *Default constructor:* Construct an empty boost::real::real_explicit with
             * undefined representation and behaviour.
             */
            real_explicit() = default;

            /**
             * @brief *Copy constructor:* Creates a copy of the boost::real::real_explicit number other.
             *
             * @param other - the boost::real::real instance to copy.
             */
            real_explicit(const real_explicit& other)  = default;

            /**
             * @brief *String constructor:* Creates a boost::real::real_explicit instance by
             * parsing the string. The string must have a valid number, in other case, the
             * constructor will throw an boost::real::invalid_string_number exception.
             *
             * @param number - a valid string representing a number.
             *
             * @throws boost::real::invalid_string_number exception
             */
            explicit real_explicit(const std::string& number) {
                // Check that is not an empty string
                if (number.length() == 0) {
                    throw boost::real::invalid_string_number_exception();
                }

                // Check that there is no more that one '.' symbol
                unsigned int dot_amount = 0;
                for (const auto& c : number ) {
                    if (c == '.' && dot_amount >= 1) {
                        throw boost::real::invalid_string_number_exception();
                    } else if (c == '.') {
                        dot_amount++;
                    }
                }

                bool there_is_dot = dot_amount > 0;
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
                    if (!there_is_dot || dot_amount > 0) {
                        exponent++; // remove zeros from the integer part increases the exponent
                    }
                }

                // The number is all composed by zeros, then it is zero
                if (last_index == first_index && number.at(last_index) == '0') {
                    this->_digits = {0};
                    this->_exponent = 0;
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
                            throw boost::real::invalid_string_number_exception();
                        }

                    }
                }

                this->_exponent = exponent;
                this->_maximum_precision = (int)this->_digits.size();
            };

            /**
             * @brief *Initializer list constructor with exponent:* Creates a boost::real::real_explicit
             * instance that represents the number where the exponent is used to set the number
             * integer part and the elements of the digits list are the digits the number in the same order.
             * The number is set as positive.
             *
             * @param digits - an initializer_list<int> that represent the number digits.
             * @param exponent - an integer representing the number exponent.
             */
            real_explicit(std::initializer_list<int> digits, int exponent) :
                    _digits(digits),
                    _exponent(exponent),
                    _maximum_precision((int)this->_digits.size())
            {};

            /**
             * @brief *Initializer list constructor with exponent and sign:* Creates a
             * boost::real::real_explicit instance that represents the number where the exponent
             * is used to set the number integer part and the elements of the digit list are the
             * digits the number in the same order. This constructor uses the sign to determine
             * if the number is positive or negative.
             *
             * @param digits - an initializer_list<int> that represent the number digits.
             * @param exponent - an integer representing the number exponent.
             * @param positive - a bool that represent the number sign. If positive is set to true,
             * the number is positive, otherwise is negative.
             */
            real_explicit(std::initializer_list<int> digits, int exponent, bool positive):
                    _digits(digits),
                    _exponent(exponent),
                    _positive(positive),
                    _maximum_precision((int)this->_digits.size())
            {};

            /**
             * @brief Returns te maximum allowed precision, if that precision is reached and an
             * operator need more precision, a precision_exception should be thrown.
             *
             * @return and integer with the maximum allowed precision.
             */
            unsigned int max_precision() const {
                return this->_maximum_precision;
            }

            /**
             * @brief Set a new maximum precision for the instance.
             *
             * @param maximum_precision - an unsigned int to set as the new precision.
             */
            void set_maximum_precision(unsigned int maximum_precision) {
                this->_maximum_precision = maximum_precision;
            }

            /**
             * @return An integer with the number exponent
             */
            int exponent() const {
                return this->_exponent;
            }

            /**
             * @return A bool indicating if the number is positive (true) or negative (false)
             */
            bool positive() const {
                return this->_positive;
            }

            /**
             * @return a const reference to the vector holding the number digits
             */
            const std::vector<int>& digits() const {
                return this->_digits;
            }

            /**
             * @brief Construct a new boost::real::real_explicit::const_precision_iterator that iterates the number
             * approximation intervals in increasing order according to the approximation precision.
             *
             * The iterator starts pointing the interval with the minimum precision.
             *
             * @return a boost::real::real_explicit::const_precision_iterator of the number.
             */
            const_precision_iterator cbegin() const {
                return const_precision_iterator(this);
            }

            /**
             * @brief Construct a new boost::real::real_explicit::const_precision_iterator that iterates the number
             * approximation intervals in increasing order according to the approximation precision.
             *
             * The iterator starts pointing the interval with the maximum allowed precision.
             *
             * @return a boost::real::real_explicit::const_precision_iterator of the number.
             */
            const_precision_iterator cend() const {
                const_precision_iterator it(this);
                it.iterate_n_times((int)this->_digits.size() + 1);
                return it;
            }

            /**
             * @brief Returns the n-th digit the number.
             *
             * @param n - an unsigned int number indicating the index of the requested digit.
             * @return an integer with the value of the number n-th digit.
             */
            int operator[](unsigned int n) const {
                if (n < this->_digits.size()) {
                    return this->_digits.at(n);
                }

                return 0;
            }

            /**
             * @brief It assign a new copy of the other boost::real::real_explicit number in the *this boost::real::real_explicit number.
             *
             * @param other - the boost::real::real_explicit number to copy.
             * @return a reference of *this with the new represented number.
             */
            real_explicit& operator=(const real_explicit& other) = default;
        };
    }
}

/**
 * @bief overload of the << operator for std::ostream and boost::real::real_explicit
 *
 * @param os - The std::ostream object where to print the r number.
 * @param r - the boost::real::real_explicit number to print
 * @return a reference of the modified os object.
 */
std::ostream& operator<<(std::ostream& os, const boost::real::real_explicit& r) {
    auto it = r.cbegin();
    for (unsigned int i = 0; i <= r.max_precision(); i++) {
        ++it;
    }
    os << it.approximation_interval;
    return os;
}


#endif //BOOST_REAL_REAL_EXPLICIT_HPP

#ifndef BOOST_REAL_REAL_ALGORITHM_HPP
#define BOOST_REAL_REAL_ALGORITHM_HPP

#include <real/interval.hpp>

namespace boost {
    namespace real {

        /**
         * @author Laouen Mayal Louan Belloli
         *
         * @brief boost::real::real_algorithm is a C++ class that represents real numbers as a
         * a function that calculates the n-th digit o the number, a sign and an exponent.
         *
         * @details Because a function pointer of lambda function is used to obtain the number
         * digits on demand, numbers with infinite representations as the irrational numbers can be
         * represented using this class.
         */
        class real_algorithm {

            // Number representation as a function that return the number digits
            // an integer part and a sign (+/-)
            int (*_get_nth_digit)(unsigned int);
            int _exponent;
            bool _positive;

            // Precision
            unsigned int _maximum_precision = 0;

        public:

            static unsigned int maximum_precision;

            /**
             * @author Laouen Mayal Louan Belloli
             *
             * @brief is a forward iterator that iterates a boost::real::real_algorithm number approximation
             * intervals. The iterator calculates the initial interval with the initial precision and
             * then it increase the precision in each iteration (++) and recalculate the interval.
             */
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

                /**
                 * @brief **Default constructor:** Constructs an empty
                 * boost::real::real_algorithm::const_precision_iterator that points to nullptr.
                 */
                const_precision_iterator() = default;

                /**
                 * @brief **Copy constructor:**
                 * Construct a new boost::real::real_algorithm::const_precision_iterator which is
                 * a copy of the other iterator.
                 *
                 * @param other - the boost::real::real::const_precision_iterator to copy.
                 */
                const_precision_iterator(const const_precision_iterator& other) = default;

                /**
                 * @brief *Pointer constructor:* Construct a new boost::real::real_algorithm::const_precision_iterator
                 * pointing to the boost::real::real_algorithm number to iterate the number approximation intervals.
                 *
                 * The iterator will start pointing the lowest precision interval.
                 *
                 * @param real_number - the boost::real::real number to iterate.
                 */
                explicit const_precision_iterator(real_algorithm const* real_number) : _n(1), _real_ptr(real_number) {

                    this->approximation_interval.lower_bound.exponent = this->_real_ptr->_exponent;
                    this->approximation_interval.upper_bound.exponent = this->_real_ptr->_exponent;
                    this->approximation_interval.lower_bound.positive = this->_real_ptr->_positive;
                    this->approximation_interval.upper_bound.positive = this->_real_ptr->_positive;

                    int first_digit = (*this->_real_ptr)[0];
                    this->approximation_interval.lower_bound.digits.push_back(first_digit);

                    if (first_digit == 9) {
                        this->approximation_interval.upper_bound.digits.push_back(1);
                        this->approximation_interval.upper_bound.exponent++;
                    } else {
                        this->approximation_interval.upper_bound.digits.push_back(first_digit + 1);
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

                /**
                 * @brief It compare by value equality; two boost::real::real_algorithm::const_precision_iterators
                 * are equals if they are pointing to the same real number and are in the same precision iteration.
                 *
                 * @param other - A boost::real::real_algorithm::const_precision_iterator that is the right side operand
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
                 * @brief It compare by value not equal; two boost::real::real_algorithm::const_precision_iterators.
                 *
                 * @param other - A boost::real::real_algorithm::const_precision_iterator that is the right side operand
                 * @return a bool that is true if and only if both iterators are not equals.
                 */
                bool operator!=(const const_precision_iterator& other) const {
                    return !(*this == other);
                }
            };

            /**
             * @brief *Default constructor:* Construct an empty boost::real::real_algorithm with
             * undefined representation and behaviour.
             */
            real_algorithm() = default;

            /**
             * @brief *Copy constructor:* Creates a copy of the boost::real::real_algorithm number other.
             *
             * @param other - the boost::real::real instance to copy.
             */
            real_algorithm(const real_algorithm& other) = default;

            /**
             * @brief *Lambda function constructor with exponent:* Creates a boost::real::real_algorithm
             * instance that represents the number where the exponent is used to set the number
             * integer part and the lambda function digits is used to know the number digits,
             * this function returns the n-th number digit. The number is positive.
             *
             * @param get_nth_digit - a function pointer or lambda function that given an unsigned
             * int "n" as parameter, it returns the number n-th digit.
             * @param exponent - an integer representing the number exponent.
             */
            explicit real_algorithm(int (*get_nth_digit)(unsigned int), int exponent)
                    : _get_nth_digit(get_nth_digit), _exponent(exponent), _positive(true) {}

            /**
             * @brief *Lambda function constructor with exponent and sign:* Creates a boost::real::real_algorithm instance
             * that represents the number where the exponent is used to set the number integer part
             * and the lambda function digits is used to know the number digit, this function returns
             * the n-th number digit. This constructor uses the sign to determine if the number
             * is positive or negative.
             *
             * @param get_nth_digit - a function pointer or lambda function that given an unsigned
             * int "n" as parameter, it returns the number n-th digit.
             * @param exponent - an integer representing the number exponent.
             * @param positive - a bool that represent the number sign. If positive is set to true,
             * the number is positive, otherwise is negative.
             */
            explicit real_algorithm(int (*get_nth_digit)(unsigned int),
                                    int exponent,
                                    bool positive)
                    : _get_nth_digit(get_nth_digit),
                      _exponent(exponent),
                      _positive(positive) {}

            /**
             * @brief Returns the maximum allowed precision, if that precision is reached and an
             * operator need more precision, a precision_exception should be thrown.
             *
             * @return an integer with the maximum allowed precision.
             */
            unsigned int max_precision() const {
                return boost::real::real_algorithm::maximum_precision;
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
             * @brief Construct a new boost::real::real_algorithm::con_precision_iterator that iterates the number
             * approximation intervals in increasing order according to the approximation precision.
             *
             * The iterator starts pointing the interval with the minimum precision.
             *
             * @return a boost::real::real_algorithm::const_precision_iterator of the number.
             */
            const_precision_iterator cbegin() const {
                return const_precision_iterator(this);
            }

            /**
             * @brief Construct a new boost::real::real_algorithm::con_precision_iterator that iterates the number
             * approximation intervals in increasing order according to the approximation precision.
             *
             * The iterator starts pointing the interval with the maximum allowed precision.
             *
             * @return a boost::real::real_algorithm::const_precision_iterator of the number.
             */
            const_precision_iterator cend() const {
                const_precision_iterator it(this);
                it.iterate_n_times(boost::real::real_algorithm::maximum_precision - 1);
                return it;
            }

            /**
             * @brief Returns the n-th digit the number.
             *
             * @param n - an unsigned int number indicating the index of the requested digit.
             * @return an integer with the value of the number n-th digit.
             */
            int operator[](unsigned int n) const { return this->_get_nth_digit(n); }

            /**
             * @brief It assign a new copy of the other boost::real::real_algorithm number in the *this boost::real::real_algorithm number.
             *
             * @param other - the boost::real::real_algorithm number to copy.
             * @return a reference of *this with the new represented number.
             */
            real_algorithm& operator=(const real_algorithm& other) = default;
        };
    }
}

/**
 * @bief overload of the << operator for std::ostream and boost::real::real_algorithm
 *
 * @param os - The std::ostream object where to print the r number.
 * @param r - the boost::real::real_algorithm number to print
 * @return a reference of the modified os object.
 */
std::ostream& operator<<(std::ostream& os, const boost::real::real_algorithm& r) {
    auto it = r.cbegin();
    for (unsigned int i = 0; i <= r.max_precision(); i++) {
        ++it;
    }
    os << it.approximation_interval;
    return os;
}

#endif //BOOST_REAL_REAL_ALGORITHM_HPP

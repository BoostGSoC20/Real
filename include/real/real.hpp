#ifndef BOOST_REAL_REAL_HPP
#define BOOST_REAL_REAL_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <utility>

#include <real/real_exception.hpp>
#include <real/real_helpers.hpp>
#include <real/real_explicit.hpp>
#include <real/real_algorithm.hpp>


namespace boost {
    namespace real {

        /**
         * @author Laouen Mayal Louan Belloli
         *
         * @brief boost::real::real is a C++ class that represent real numbers as abstract entities that
         * can be dynamically approximated as much as needed (until a set maximum precision) to be
         * able to operate with them. Numbers can be added, subtracted, multiplied and compared by
         * lower than and equality.
         *
         * @details A boost::real::real number is represented by the operations from which the number
         * is created, the entire operation is represented as a binary tree where the leaves are
         * literal numbers and the internal nodes are the operations. Also, boost::real::real allow to
         * represent irrational numbers by taking as parameter a function pointer or lambda function
         * that given un unsigned integer "n", the function returns the n-th digit of the irrational
         * number.
         *
         * A number can be one of the following three kind:
         *
         *  1. Explicit number: A number is a vector of digits sorted as in the number natural
         *  representation. To determine where the integer part ends and the fractional part starts,
         *  an integer is used as the exponent of a floating point number and determines where the
         *  integer part start and the fractional ends. Also a boolean is used to set the number as
         *  positive (True) or negative (False)
         *
         *  2. Algorithmic number: This representation is equal to the Explicit number but instead
         *  of using a vector of digits, a lambda function must be provided. The lambda function
         *  takes an unsigned integer "n" as parameter and returns the n-th digit of the number.
         *
         *  3. A number is a composition of two numbers related by an operator (+, -, *), the number
         *  creates pointers to the operands and each time the number is used, the operation is
         *  evaluated to return the result.
         *
         * Two boost::real::real numbers can be compared by the lower operator "<" and by the equal
         * operator "==" but for those cases where the class is not able to decide the value of the
         * result before reaching the maximum precision, a precision_exception is thrown.
         */
        class real {

            // Available operations
            enum class OPERATION {ADDITION, SUBTRACT, MULTIPLICATION};
            enum class KIND {EXPLICIT, OPERATION, ALGORITHM};

            KIND _kind;

            // Explicit number
            real_explicit _explicit_number;

            // Algorithmic number
            real_algorithm _algorithmic_number;

            // Composed number
            OPERATION _operation;
            real* _lhs_ptr = nullptr;
            real* _rhs_ptr = nullptr;

            // Precision
            unsigned int _maximum_precision = 0;

            void copy_operands(const real& other) {
                if (other._lhs_ptr != nullptr) {
                    this->_lhs_ptr = new real(*other._lhs_ptr);
                }

                if (other._rhs_ptr != nullptr) {
                    this->_rhs_ptr = new real(*other._rhs_ptr);
                }
            }

        public:

            /**
             * @brief Determines the maximum precision to use
             */
            static unsigned int maximum_precision;

            /**
             * @author Laouen Mayal Louan Belloli
             *
             * @brief is a forward iterator that iterates a boost::real::real number approximation
             * intervals. The iterator calculates the initial interval with the initial precision and
             * then it increase the precision in each iteration (++) and recalculate the interval.
             */
            class const_precision_iterator {
            private:

                // Internal number to iterate
                real const* _real_ptr = nullptr;

                // Explicit number iterator
                boost::real::real_explicit::const_precision_iterator _explicit_it;

                // Algorithmic number iterator
                boost::real::real_algorithm::const_precision_iterator _algorithmic_it;

                // If the number is a composition, the const_precision_iterator uses the operand iterators
                const_precision_iterator* _lhs_it_ptr = nullptr;
                const_precision_iterator* _rhs_it_ptr = nullptr;

                void calculate_operation_boundaries() {

                    switch (this->_real_ptr->_operation) {

                        case OPERATION::ADDITION:
                            boost::real::helper::add_boundaries(
                                    this->_lhs_it_ptr->approximation_interval.lower_bound,
                                    this->_rhs_it_ptr->approximation_interval.lower_bound,
                                    this->approximation_interval.lower_bound
                            );

                            boost::real::helper::add_boundaries(
                                    this->_lhs_it_ptr->approximation_interval.upper_bound,
                                    this->_rhs_it_ptr->approximation_interval.upper_bound,
                                    this->approximation_interval.upper_bound
                            );
                            break;


                        case OPERATION::SUBTRACT:
                            boost::real::helper::subtract_boundaries(
                                    this->_lhs_it_ptr->approximation_interval.lower_bound,
                                    this->_rhs_it_ptr->approximation_interval.upper_bound,
                                    this->approximation_interval.lower_bound
                            );

                            boost::real::helper::subtract_boundaries(
                                    this->_lhs_it_ptr->approximation_interval.upper_bound,
                                    this->_rhs_it_ptr->approximation_interval.lower_bound,
                                    this->approximation_interval.upper_bound
                            );
                            break;


                        case OPERATION::MULTIPLICATION: {
                            bool lhs_positive = this->_lhs_it_ptr->approximation_interval.positive();
                            bool rhs_positive = this->_rhs_it_ptr->approximation_interval.positive();
                            bool lhs_negative = this->_lhs_it_ptr->approximation_interval.negative();
                            bool rhs_negative = this->_rhs_it_ptr->approximation_interval.negative();

                            if (lhs_positive && rhs_positive) { // Positive - Positive
                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.lower_bound,
                                        this->_rhs_it_ptr->approximation_interval.lower_bound,
                                        this->approximation_interval.lower_bound
                                );

                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.upper_bound,
                                        this->_rhs_it_ptr->approximation_interval.upper_bound,
                                        this->approximation_interval.upper_bound
                                );

                            } else if (lhs_negative && rhs_negative) { // Negative - Negative
                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.upper_bound,
                                        this->_rhs_it_ptr->approximation_interval.upper_bound,
                                        this->approximation_interval.lower_bound
                                );

                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.lower_bound,
                                        this->_rhs_it_ptr->approximation_interval.lower_bound,
                                        this->approximation_interval.upper_bound
                                );
                            } else if (lhs_negative && rhs_positive) { // Negative - Positive
                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.lower_bound,
                                        this->_rhs_it_ptr->approximation_interval.upper_bound,
                                        this->approximation_interval.lower_bound
                                );

                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.upper_bound,
                                        this->_rhs_it_ptr->approximation_interval.lower_bound,
                                        this->approximation_interval.upper_bound
                                );

                            } else if (lhs_positive && rhs_negative) { // Positive - Negative
                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.upper_bound,
                                        this->_rhs_it_ptr->approximation_interval.lower_bound,
                                        this->approximation_interval.lower_bound
                                );

                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.lower_bound,
                                        this->_rhs_it_ptr->approximation_interval.upper_bound,
                                        this->approximation_interval.upper_bound
                                );

                            } else { // One is around zero all possible combinations are be tested

                                boundary current_boundary;

                                // Lower * Lower
                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.lower_bound,
                                        this->_rhs_it_ptr->approximation_interval.lower_bound,
                                        current_boundary
                                );

                                this->approximation_interval.lower_bound = current_boundary;
                                this->approximation_interval.upper_bound = current_boundary;

                                // Upper * upper
                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.upper_bound,
                                        this->_rhs_it_ptr->approximation_interval.upper_bound,
                                        current_boundary
                                );

                                if (current_boundary < this->approximation_interval.lower_bound) {
                                    this->approximation_interval.lower_bound = current_boundary;
                                }

                                if (this->approximation_interval.upper_bound < current_boundary) {
                                    this->approximation_interval.upper_bound = current_boundary;
                                }

                                // Lower * upper
                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.lower_bound,
                                        this->_rhs_it_ptr->approximation_interval.upper_bound,
                                        current_boundary
                                );

                                if (current_boundary < this->approximation_interval.lower_bound) {
                                    this->approximation_interval.lower_bound = current_boundary;
                                }

                                if (this->approximation_interval.upper_bound < current_boundary) {
                                    this->approximation_interval.upper_bound = current_boundary;
                                }

                                // Upper * lower
                                boost::real::helper::multiply_boundaries(
                                        this->_lhs_it_ptr->approximation_interval.upper_bound,
                                        this->_rhs_it_ptr->approximation_interval.lower_bound,
                                        current_boundary
                                );

                                if (current_boundary < this->approximation_interval.lower_bound) {
                                    this->approximation_interval.lower_bound = current_boundary;
                                }

                                if (this->approximation_interval.upper_bound < current_boundary) {
                                    this->approximation_interval.upper_bound = current_boundary;
                                }
                            }
                            break;
                        }

                        default:
                            throw boost::real::none_operation_exception();
                    }
                }

            public:

                // Number approximation_interval boundaries
                boost::real::interval approximation_interval;

                /**
                 * @brief *Default constructor:*
                 * Constructs an empty boost::real::real::const_precision_iterator that points to nullptr.
                 */
                const_precision_iterator() = default;

                /**
                 * @brief *Copy constructor:* Construct a new boost::real::real::const_precision_iterator
                 * which is a copy of the other iterator.
                 *
                 * @param other - the boost::real::real::const_precision_iterator to copy.
                 */
                const_precision_iterator(const const_precision_iterator& other) = default;

                /**
                 * @brief *Pointer constructor:* Construct a new boost::real::real::const_precision_iterator
                 * pointing to the boost::real::real number to iterate the number approximation intervals.
                 *
                 * The iterator will start pointing the lowest precision interval.
                 *
                 * @param real_number - the boost::real::real number to iterate.
                 */
                explicit const_precision_iterator(real const* real_number) : _real_ptr(real_number) {

                    switch (this->_real_ptr->_kind) {

                        case KIND::EXPLICIT:
                                this->_explicit_it = this->_real_ptr->_explicit_number.cbegin();
                            this->approximation_interval = this->_explicit_it.approximation_interval;
                            break;

                        case KIND::ALGORITHM:
                            this->_algorithmic_it = this->_real_ptr->_algorithmic_number.cbegin();
                            this->approximation_interval = this->_algorithmic_it.approximation_interval;
                            break;

                        case KIND::OPERATION:
                            this->_lhs_it_ptr = new const_precision_iterator(this->_real_ptr->_lhs_ptr->cbegin());
                            this->_rhs_it_ptr = new const_precision_iterator(this->_real_ptr->_rhs_ptr->cbegin());
                            this->calculate_operation_boundaries();
                            break;
                    }
                }

                /**
                 * @brief *Pointer constructor for cend:* Construct a new boost::real::real::const_precision_iterator
                 * pointing to the boost::real::real number real_number to iterate the number
                 * approximation intervals.
                 *
                 * If the cend parameter is set to true, the iterator will point to the highest
                 * precision interval allowed by the maximum precision. If is set to false, this
                 * constructor is equivalent to the Pointer constructor.
                 *
                 * @param real_number - the boost::real::real number to iterate.
                 * @param cend - a bool indicating if the iterator must point the lowest of highest
                 * precision interval.
                 */
                explicit const_precision_iterator(real const* real_number, bool cend) : _real_ptr(real_number) {

                    switch (this->_real_ptr->_kind) {

                        case KIND::EXPLICIT:
                            if (cend) {
                                this->_explicit_it = this->_real_ptr->_explicit_number.cend();
                            } else {
                                this->_explicit_it = this->_real_ptr->_explicit_number.cbegin();
                            }
                            this->approximation_interval = this->_explicit_it.approximation_interval;
                            break;

                        case KIND::ALGORITHM:
                            if (cend) {
                                this->_algorithmic_it = this->_real_ptr->_algorithmic_number.cend();
                            } else {
                                this->_algorithmic_it = this->_real_ptr->_algorithmic_number.cbegin();
                            }
                            this->approximation_interval = this->_algorithmic_it.approximation_interval;
                            break;

                        case KIND::OPERATION:
                            this->_lhs_it_ptr = new const_precision_iterator(this->_real_ptr->_lhs_ptr, cend);
                            this->_rhs_it_ptr = new const_precision_iterator(this->_real_ptr->_rhs_ptr, cend);
                            this->calculate_operation_boundaries();
                            break;
                    }
                }

                /**
                 * @brief It recalculates the approximation interval boundaries increasing the used
                 * precision, the new pointed approximation interval is smaller than the current one.
                 */
                void operator++() {

                    switch (this->_real_ptr->_kind) {

                        case KIND::EXPLICIT:
                            ++this->_explicit_it;
                            this->approximation_interval = this->_explicit_it.approximation_interval;
                            break;

                        case KIND::ALGORITHM:
                            ++this->_algorithmic_it;
                            this->approximation_interval = this->_algorithmic_it.approximation_interval;
                            break;

                        case KIND::OPERATION:
                            // Composed number iteration
                            this->approximation_interval.lower_bound.clear();
                            this->approximation_interval.upper_bound.clear();

                            // Recursive iteration of the operands
                            ++(*this->_lhs_it_ptr);
                            ++(*this->_rhs_it_ptr);

                            // Final bound calculation
                            this->calculate_operation_boundaries();
                            break;
                    }
                };

                /**
                 * @brief It compare by value equality; two boost::real::real::const_precision_iterators
                 * are equals if they are pointing to the same real number and are in the same precision iteration.
                 *
                 * @param other - A boost::real::real::const_precision_iterator that is the right side operand
                 * @return a bool that is true if and only if both iterators are equals.
                 */
                bool operator==(const const_precision_iterator& other) const {
                    // uninitialized iterators are never equals
                    if (this->_real_ptr == nullptr || other._real_ptr == nullptr) {
                        return false;
                    }

                    return (other._real_ptr == this->_real_ptr) && (other.approximation_interval == this->approximation_interval);
                }

                /**
                 * @brief It compare by value not equal; two boost::real::real::const_precision_iterators.
                 *
                 * @param other - A boost::real::real::const_precision_iterator that is the right side operand
                 * @return a bool that is true if and only if both iterators are not equals.
                 */
                bool operator!=(const const_precision_iterator& other) const {
                    return !(*this == other);
                }
            };

            /**
             * @brief *Default constructor:* Constructr a boost::real::real with undefined representation
             * and behaviour.
             *
             * @note This constructor exist to allow working with other libraries as std::map or std::tuple
             */
            real() = default;

            /**
             * @brief *Copy constructor:* Creates a copy of the boost::real::real number other,
             * if the number is an operation, then, the constructor recursively creates new
             * copies of the other operands.
             *
             * @param other - the boost::real::real instance to copy.
             */
            real(const real& other)  :
                    _kind(other._kind),
                    _explicit_number(other._explicit_number),
                    _algorithmic_number(other._algorithmic_number),
                    _operation(other._operation) { this->copy_operands(other); };

            /**
             * @brief *String constructor:* Creates a boost::real::real instance by parsing
             * the string. The string must have a valid number, in other case, the constructor
             * will throw an boost::real::invalid_string_number exception.
             *
             * @param number - a valid string representing a number.
             *
             * @throws boost::real::invalid_string_number exception
             */
            real(const std::string& number)
                    : _kind(KIND::EXPLICIT), _explicit_number(number) {}

            /**
             * @brief *Initializer list constructor:* Creates a boost::real::real_explicit instance
             * that represents an integer number where all the digits parameter numbers are form
             * the integer part in the same order. The number is set as positive.
             *
             * @param digits - a initializer_list<int> that represents the number digits.
             */
            real(std::initializer_list<int> digits)
                    : _kind(KIND::EXPLICIT), _explicit_number(digits, digits.size()) {}


            /**
             * @brief *Signed initializer list constructor:* Creates a boost::real::real
             * instance that represents the number where the positive parameter is used to set the
             * number sign and the elements of the digits parameter list are the number digits in
             * the same order.
             *
             * @param digits - an initializer_list<int> that represent the number digits.
             * @param positive - a bool that represent the number sign. If positive is set to true,
             * the number is positive, otherwise is negative.
             */
            real(std::initializer_list<int> digits, bool positive)
                    : _kind(KIND::EXPLICIT), _explicit_number(digits, digits.size(), positive) {}

            /**
             * @brief *Initializer list constructor with exponent:* Creates a boost::real::real
             * instance that represents the number where the exponent is used to set the number
             * integer part and the elements of the digits list are the digits the number in the same order.
             * The number is set as positive.
             *
             * @param digits - an initializer_list<int> that represent the number digits.
             * @param exponent - an integer representing the number exponent.
             */
            real(std::initializer_list<int> digits, int exponent)
                    : _kind(KIND::EXPLICIT), _explicit_number(digits, exponent) {};

            /**
             * @brief *Initializer list constructor with exponent and sign:* Creates a boost::real::real instance
             * that represents the number where the exponent is used to set the number integer part
             * and the elements of the digit list are the digits the number in the same order.
             * This constructor uses the sign to determine if the number is positive or negative.
             *
             * @param digits - an initializer_list<int> that represent the number digits.
             * @param exponent - an integer representing the number exponent.
             * @param positive - a bool that represent the number sign. If positive is set to true,
             * the number is positive, otherwise is negative.
             */
            real(std::initializer_list<int> digits, int exponent, bool positive)
                    : _kind(KIND::EXPLICIT), _explicit_number(digits, exponent, positive) {};

            /**
             * @brief *Lambda function constructor with exponent:* Creates a boost::real::real
             * instance that represents the number where the exponent is used to set the number
             * integer part and the lambda function digits is used to know the number digits,
             * this function returns the n-th number digit.
             *
             * @param get_nth_digit - a function pointer or lambda function that given an unsigned
             * int "n" as parameter, it returns the number n-th digit.
             * @param exponent - an integer representing the number exponent.
             */
            real(int (*get_nth_digit)(unsigned int), int exponent)
                    : _kind(KIND::ALGORITHM), _algorithmic_number(get_nth_digit, exponent) {}

            /**
             * @brief *Lambda function constructor with exponent and sign:* Creates a boost::real::real instance
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
            real(int (*get_nth_digit)(unsigned int),
                 int exponent,
                 bool positive)
                    : _kind(KIND::ALGORITHM),
                      _algorithmic_number(get_nth_digit, exponent, positive) {}

            /**
             * @brief *Default destructor:* If the number is an operator, the destructor destroys its operands.
             */
            ~real() {
                delete this->_lhs_ptr;
                this->_lhs_ptr = nullptr;

                delete this->_rhs_ptr;
                this->_rhs_ptr = nullptr;
            }

            /**
             * @brief Returns te maximum allowed precision, if that precision is reached and an
             * operator need more precision, a precision_exception should be thrown.
             *
             * @return and integer with the maximum allowed precision.
             */
            unsigned int max_precision() const {
                if (this->_maximum_precision == 0) {
                    return boost::real::real::maximum_precision;
                }

                return this->_maximum_precision;
            }

            /**
             * @brief Set a new maximum precision for the instance.
             *
             * @note Setting zero as the maximum precision causes the instance to use the default
             * static unsigned int boost::real::real::maximum_precision.
             *
             * @param maximum_precision - an unsigned int to set as the new precision.
             */
            void set_maximum_precision(unsigned int maximum_precision) {
                this->_maximum_precision = maximum_precision;
            }

            /**
             * @brief Construct a new boost::real::real::con_precision_iterator that iterates the number
             * approximation intervals from in increasing order according to the approximation precision.
             *
             * The iterator starts pointing the interval with the minimum precision.
             *
             * @return a boost::real::real::const_precision_iterator of the number.
             */
            const_precision_iterator cbegin() const {
                return const_precision_iterator(this);
            }

            /**
             * @brief Construct a new boost::real::real::con_precision_iterator that iterates the number
             * approximation intervals from in increasing order according to the approximation precision.
             *
             * The iterator starts pointing the interval with the maximum allowed precision.
             *
             * @return a boost::real::real::const_precision_iterator of the number.
             */
            const_precision_iterator cend() const {
                return const_precision_iterator(this, true);
            }

            /************** Operators ******************/

            /**
             * @brief If the number is an explicit or algorithm number it returns the n-th digit
             * of the represented number. If the number is an operation it throws an invalid_representation_exception
             *
             * @param n - an unsigned int number indicating the index of the requested digit.
             * @return an integer with the value of the number n-th digit.
             *
             * @throws boost::real::invalid_representation_exception
             */
            int operator[](unsigned int n) const {
                int result;

                switch (this->_kind) {

                    case KIND::EXPLICIT:
                        result = this->_explicit_number[n];
                        break;

                    case KIND::ALGORITHM:
                        result = this->_algorithmic_number[n];
                        break;

                    case KIND::OPERATION:
                        throw boost::real::invalid_representation_exception();
                        break;
                }

                return result;
            };

            /**
             * @brief Convert the number from its current representation to an operation number
             * representation where the operands are copies of the other and this numbers (before the conversion).
             * The new number represent the addition operation between *this and other.
             *
             * @param other - the right side operand boost::real::real number.
             * @return A reference to the new boost::real::real number representation.
             */
            real& operator+=(const real& other) {
                this->_lhs_ptr = new real(*this);
                this->_rhs_ptr = new real(other);
                this->_kind = KIND::OPERATION;
                this->_operation = OPERATION::ADDITION;
                return *this;
            }

            /**
             * @brief Creates a new boost::real::real representing an operation number where the operands
             * are copies of the other and this numbers. The number represent the addition operation
             * between *this and other.
             *
             * @param other - the right side operand boost::real::real number.
             * @return A reference to the new boost::real::real number representation.
             */
            real operator+(const real& other) const {
                real result = *this;
                result += other;
                return result;
            }

            /**
             * @brief Convert the number from its current representation to an operation number
             * representation where the operands are copies of the other and this numbers (before the conversion).
             * The new number representation represent the subtraction operation between *this and other.
             *
             * @param other - the right side operand boost::real::real number.
             * @return A reference to the new boost::real::real number representation.
             */
            real& operator-=(const real& other) {
                this->_lhs_ptr = new real(*this);
                this->_rhs_ptr = new real(other);
                this->_kind = KIND::OPERATION;
                this->_operation = OPERATION::SUBTRACT;
                return *this;
            }

            /**
             * @brief Creates a new boost::real::real representing an operation number where the operands
             * are copies of the other and this numbers. The number represent the subtraction operation
             * between *this and other.
             *
             * @param other - the right side operand boost::real::real number.
             * @return A reference to the new boost::real::real number representation.
             */
            real operator-(const real& other) const {
                real result = *this;
                result -= other;
                return result;
            }

            /**
             * @brief Convert the number from its current representation to an operation number
             * representation where the operands are copies of the other and this numbers (before the conversion).
             * The new number represent the multiplication between *this and other.
             *
             * @param other - the right side operand boost::real::real number.
             * @return A reference to the new boost::real::real number representation.
             */
            real& operator*=(const real& other) {
                this->_lhs_ptr = new real(*this);
                this->_rhs_ptr = new real(other);
                this->_kind = KIND::OPERATION;
                this->_operation = OPERATION::MULTIPLICATION;
                return *this;
            }

            /**
             * @brief Creates a new boost::real::real representing an operation number where the operands
             * are copies of the other and this numbers. The number represent the multiplication
             * operation between *this and other.
             *
             * @param other - the right side operand boost::real::real number.
             * @return A reference to the new boost::real::real number representation.
             */
            real operator*(const real& other) const {
                real result = *this;
                result *= other;
                return result;
            }

            /**
             * @brief It assign a new copy of the other boost::real::real number in the *this boost::real::real number.
             *
             * @param other - the boost::real::real number to copy.
             * @return a reference of *this with the new represented number.
             */
            real& operator=(const real& other) {
                this->_kind = other._kind;
                this->_explicit_number = other._explicit_number;
                this->_operation = other._operation;
                this->copy_operands(other);
                return *this;
            }

            /**
             * @brief It constructs and boost::real::real number from the std::string and assign it
             * in the *this boost::real::real number.
             *
             * @param number - a valid string representing a number.
             * @return a reference of *this with the new represented number.
             */
            real& operator=(const std::string& number) {
                *this = real(number);
                return *this;
            }

            /**
             * @brief Compares the *this boost::real::real number against the other boost::real::real number to
             * determine if the number represented by *this is lower than the number represented by other.
             * If the maximum precision is reached and the operator was not yet able to determine
             * the value of the result, a precision_exception is thrown.
             *
             * @param other - a boost::real::real number to compare against.
             * @return a bool that is true if *this < other and false in other cases.
             *
             * @throws boost::real::precision_exception
             */
            bool operator<(const real& other) const {
                auto this_it = this->cbegin();
                auto other_it = other.cbegin();

                unsigned int current_precision = std::max(this->max_precision(), other.max_precision());
                for (unsigned int p = 0; p < current_precision; ++p) {
                    // Get more precision
                    ++this_it;
                    ++other_it;

                    bool this_full_precision = this_it.approximation_interval.is_a_number();
                    bool other_full_precision = other_it.approximation_interval.is_a_number();
                    if (this_full_precision && other_full_precision) {
                        return this_it.approximation_interval < other_it.approximation_interval;
                    }

                    if (this_it.approximation_interval < other_it.approximation_interval) {
                        return true;
                    }

                    if (other_it.approximation_interval < this_it.approximation_interval) {
                        return false;
                    }
                }

                // If the precision is reached and the number ranges still overlap, then we cannot
                // know if they are equals or other is less than this and we throw an error.
                throw boost::real::precision_exception();
            }

            /**
             * @brief Compares the *this boost::real::real number against the other boost::real::real number to
             * determine if the number represented by *this is greater than the number represented by other.
             * If the maximum precision is reached and the operator was not yet able to determine
             * the value of the result, a precision_exception is thrown.
             *
             * @param other - a boost::real::real number to compare against.
             * @return a bool that is true if *this > other and false in other cases.
             *
             * @throws boost::real::precision_exception
             */
            bool operator>(const real& other) const {
                auto this_it = this->cbegin();
                auto other_it = other.cbegin();

                unsigned int current_precision = std::max(this->max_precision(), other.max_precision());
                for (unsigned int p = 0; p < current_precision; ++p) {
                    // Get more precision
                    ++this_it;
                    ++other_it;

                    bool this_full_precision = this_it.approximation_interval.is_a_number();
                    bool other_full_precision = other_it.approximation_interval.is_a_number();
                    if (this_full_precision && other_full_precision) {
                        return this_it.approximation_interval > other_it.approximation_interval;
                    }

                    if (this_it.approximation_interval > other_it.approximation_interval) {
                        return true;
                    }

                    if (other_it.approximation_interval > this_it.approximation_interval) {
                        return false;
                    }
                }

                // If the precision is reached and the number ranges still overlap, then we cannot
                // know if they are equals or other is less than this and we throw an error.
                throw boost::real::precision_exception();
            }

            /**
             * @brief Compares the *this boost::real::real number against the other boost::real::real number to
             * determine if the number represented by *this is the same than the number represented by other.
             * If the maximum precision is reached and the operator was not yet able to determine
             * the value of the result, a precision_exception is thrown.
             *
             * @param other - a boost::real::real number to compare against.
             * @return a bool that is true if *this < other and false in other cases.
             *
             * @throws boost::real::precision_exception
             */
            bool operator==(const real& other) const {
                auto this_it = this->cbegin();
                auto other_it = other.cbegin();

                unsigned int current_precision = std::max(this->max_precision(), other.max_precision());
                for (unsigned int p = 0; p < current_precision; ++p) {
                    // Get more precision
                    ++this_it;
                    ++other_it;

                    bool this_full_precision = this_it.approximation_interval.is_a_number();
                    bool other_full_precision = other_it.approximation_interval.is_a_number();
                    if (this_full_precision && other_full_precision) {
                        return this_it.approximation_interval == other_it.approximation_interval;
                    }

                    bool this_is_lower = this_it.approximation_interval < other_it.approximation_interval;
                    bool other_is_lower = other_it.approximation_interval < this_it.approximation_interval;
                    if (this_is_lower || other_is_lower) {
                        return false;
                    }
                }

                // If the precision is reached and the numbers full precision is not reached, then
                // we cannot know if they are equals or not.
                throw boost::real::precision_exception();
            }
        };
    }
}

/**
 * @bief overload of the << operator for std::ostream and boost::real::real
 *
 * @param os - The std::ostream object where to print the r number.
 * @param r - the boost::real::real number to print
 * @return a reference of the modified os object.
 */
std::ostream& operator<<(std::ostream& os, const boost::real::real& r) {
    os << r.cend().approximation_interval;
    return os;
}

#endif //BOOST_REAL_REAL_HPP

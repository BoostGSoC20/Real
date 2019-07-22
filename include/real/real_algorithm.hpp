#ifndef BOOST_REAL_REAL_ALGORITHM_HPP
#define BOOST_REAL_REAL_ALGORITHM_HPP

#include <real/real_exception.hpp>

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

            // Number representation as a function that returns the number digits
            // an integer part and a sign (+/-)
            int (*_get_nth_digit)(unsigned int);
            int _exponent;
            bool _positive;

            public:
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
             * int "n" as parameter, returns the number n-th digit.
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
             * int "n" as parameter, returns the number n-th digit.
             * @param exponent - an integer representing the number exponent.
             * @param positive - a bool that represent the number sign. If positive is set to true,
             * the number is positive, otherwise is negative.
             */
            explicit real_algorithm(int (*get_nth_digit)(unsigned int),
                                    int exponent,
                                    bool positive)
                    : _get_nth_digit(get_nth_digit),
                      _exponent(exponent),
                      _positive(positive)
                     {};

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


#endif //BOOST_REAL_REAL_ALGORITHM_HPP
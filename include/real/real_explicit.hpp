#ifndef BOOST_REAL_REAL_EXPLICIT_HPP
#define BOOST_REAL_REAL_EXPLICIT_HPP

#include <vector>
#include <iostream>
#include <initializer_list>
#include <string>
#include <regex>

#include <real/real_exception.hpp>
#include <real/interval.hpp>
#include <real/exact_number.hpp>

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
            // TODO: Add normalizations to the constructors
            exact_number explicit_number;
            
        public:

            /**
             * @brief *Default constructor:* Constructs an empty boost::real::real_explicit with
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
             * parsing the string. The string must have a valid number, otherwise, the
             * constructor will throw an boost::real::invalid_string_number exception.
             *
             * @param number - a valid string representing a number.
             *
             * @throws boost::real::invalid_string_number exception
             */
            explicit real_explicit(const std::string& number) : explicit_number(number) 
            {};

            /**
             * @brief *Initializer list constructor with exponent:* Creates a boost::real::real_explicit
             * instance that represents the number where the exponent is used to set the number
             * integer part and the elements of the digits list are the digits the number in the same order.
             * The number is set as positive.
             *
             * @param digits - an initializer_list<int> that represents the number digits.
             * @param exponent - an integer representing the number exponent.
             */
            real_explicit(std::initializer_list<int> digits, int exponent) : explicit_number(digits, exponent)
            {};

            /**
             * @brief *Initializer list constructor with exponent and sign:* Creates a
             * boost::real::real_explicit instance that represents the number where the exponent
             * is used to set the number integer part and the elements of the digit list are the
             * digits of the number in the same order. This constructor uses the sign to determine
             * if the number is positive or negative.
             *
             * @param digits - an initializer_list<int> that represents the number digits.
             * @param exponent - an integer representing the number exponent.
             * @param positive - a bool that represents the number sign. If positive is set to true,
             * the number is positive, otherwise is negative.
             */
            real_explicit(std::initializer_list<int> digits, int exponent, bool positive) : 
                                                                                explicit_number(digits,exponent,positive)
            {};

            /**
             * @return An integer with the number exponent
             */
            int exponent() const {
                return explicit_number.exponent;
            }

            /**
             * @return A bool indicating if the number is positive (true) or negative (false)
             */
            bool positive() const {
                return explicit_number.positive;
            }

            /**
             * @return a const reference to the vector holding the number digits
             */
            const std::vector<int>& digits() const {
                return explicit_number.digits;
            }

            exact_number get_exact_number() const {
                return explicit_number;
            }

            /**
             * @brief Constructs a new boost::real::real_explicit::const_precision_iterator that iterates the number
             * approximation intervals in increasing order according to the approximation precision.
             *
             * The iterator starts pointing to the interval with the maximum allowed precision.
             *
             * @return a boost::real::real_explicit::const_precision_iterator of the number.
             */

            /**
             * @brief Returns the n-th digit the number.
             *
             * @param n - an unsigned int number indicating the index of the requested digit.
             * @return an integer with the value of the number n-th digit.
             */
            int operator[](unsigned int n) const {
                if (n < explicit_number.digits.size()) {
                    return explicit_number.digits.at(n);
                }
                return 0;
            }

            /**
             * @brief It assigns a new copy of the other boost::real::real_explicit number in the *this boost::real::real_explicit number.
             *
             * @param other - the boost::real::real_explicit number to copy.
             * @return a reference of *this with the new represented number.
             */
            real_explicit& operator=(const real_explicit& other) = default;

            
        };
    }
}



#endif //BOOST_REAL_REAL_EXPLICIT_HPP

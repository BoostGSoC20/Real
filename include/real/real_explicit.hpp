#ifndef BOOST_REAL_REAL_EXPLICIT_HPP
#define BOOST_REAL_REAL_EXPLICIT_HPP

#include <vector>
#include <iostream>
#include <initializer_list>
#include <string>
#include <regex>
#include <limits>

#include <real/real_exception.hpp>
#include <real/interval.hpp>
#include <real/exact_number.hpp>
#include <real/integer_number.hpp>

namespace boost {
    namespace real {

        /**
         * @author Laouen Mayal Louan Belloli
         *
         * @brief boost::real::real_explicit is a C++ class that fully represents real numbers as
         * a vector of digits, a sign and an exponent.
         */
        template <typename T = int>
        class real_explicit {

            // Number representation as a vector of digits with an integer part and a sign (+/-)
            // TODO: Add normalizations to the constructors
        
            exact_number<T> explicit_number;
            
        public:

            /**
             * @brief *Default constructor:* Constructs an empty boost::real::real_explicit with
             * undefined representation and behaviour.
             */
            real_explicit<T>() = default;

            /**
             * @brief *Copy constructor:* Creates a copy of the boost::real::real_explicit number other.
             *
             * @param other - the boost::real::real instance to copy.
             */
            real_explicit<T>(const real_explicit<T>& other)  = default;

            constexpr explicit real_explicit(const std::string_view integer_part, const std::string_view decimal_part, int exponent, bool positive) {
                exact_number<T> op;
                explicit_number.positive = positive;
                if (integer_part.empty() && decimal_part.empty()) {
                    explicit_number.digits = {0};
                    explicit_number.exponent = 0;
                    return;
                }
                explicit_number.exponent = exponent;
                for (const auto& c : integer_part ) {
                    explicit_number.digits.push_back(c - '0');
                }
                for (const auto& c : decimal_part ) {
                    explicit_number.digits.push_back(c - '0');
                }
                //changing base below
                exponent = 0;
                //int b = 30;
                T b = (std::numeric_limits<T>::max() /4)*2;
                std::vector<T> base;
                while (b!=0) {
                    base.push_back(b%10);
                    b /= 10;
                }
                std::reverse(base.begin(), base.end());
                int curr_size = explicit_number.digits.size();
                
                for (int i = 0; i<explicit_number.exponent-curr_size; ++i) {
                    explicit_number.digits.push_back(0);
                }
                
                while (explicit_number.digits.size() > 1) {
                    std::vector<T> quotient;
                    std::vector<T> rem = op.long_divide_vectors(explicit_number.digits, base, quotient, 10);
                    if (rem.empty()) {
                        explicit_number.digits = quotient;
                        ++exponent; 
                    }
                    else
                        break;
                }
                
                std::vector<T> new_digits;
                while (!explicit_number.digits.empty()) {
                    std::vector<T> quotient;
                    //std::vector<T> rem;
                    std::vector<T> rem = op.long_divide_vectors(explicit_number.digits, base, quotient, 10);
                    T result = 0;
                    for (auto d : rem)  
                    {
                        result = result * 10 + d;
                    }
                    
                    new_digits.push_back(result);
                    explicit_number.digits = quotient;
                }
                
                std::reverse (new_digits.begin(), new_digits.end());
                exponent += (int)new_digits.size();
                explicit_number.digits = new_digits;
                explicit_number.exponent = exponent;
            }
            
            constexpr explicit real_explicit(std::string_view number) {
                auto [integer_part, decimal_part, exponent, positive] = exact_number<>::number_from_string((std::string_view)number);
                
                if (integer_part.empty() && decimal_part.empty()) {
                    explicit_number.digits = {0};
                    explicit_number.exponent = 0;
                    return;
                }
                exact_number<T> op;
                explicit_number.exponent = exponent;
                for (const auto& c : integer_part ) {
                    explicit_number.digits.push_back(c - '0');
                }
                for (const auto& c : decimal_part ) {
                    explicit_number.digits.push_back(c - '0');
                }
                explicit_number.positive = positive;

                //changing base below.
                exponent = 0;
                T b = (std::numeric_limits<T>::max() /4)*2;
                std::vector<T> base;
                while (b!=0) {
                    base.push_back(b%10);
                    b /= 10;
                }
                std::reverse(base.begin(), base.end());
                int curr_size = explicit_number.digits.size();
                
                for (int i = 0; i<explicit_number.exponent-curr_size; ++i) {
                    explicit_number.digits.push_back(0);
                }
                
                while (explicit_number.digits.size() > 1) {
                    std::vector<T> quotient;
                    std::vector<T> rem = op.long_divide_vectors(explicit_number.digits, base, quotient, 10);
                    if (rem.empty()) {
                        explicit_number.digits = quotient;
                        ++exponent; 
                    }
                    else
                        break;
                }
                
                std::vector<T> new_digits;
                while (!explicit_number.digits.empty()) {
                    std::vector<T> quotient;
                    //std::vector<T> rem;
                    std::vector<T> rem = op.long_divide_vectors(explicit_number.digits, base, quotient, 10);
                    T result = 0;
                    for (auto d : rem)  
                    {
                        result = result * 10 + d;
                    }
                    
                    new_digits.push_back(result);
                    explicit_number.digits = quotient;
                }
                
                std::reverse (new_digits.begin(), new_digits.end());
                exponent += (int)new_digits.size();
                explicit_number.digits = new_digits;
                explicit_number.exponent = exponent;
               
            }

            // constructor to convert an integer type rational number into an explicit number
            constexpr explicit real_explicit(integer_number<T> num){
                int _exponent = 0;
                std::vector<T> num_vector = num.digits;
                size_t n = num_vector.size();
                if(n==0) return;
                for(size_t i=n-1;true;--i){
                    if(num_vector[i]==0){
                        _exponent++;
                        num_vector.pop_back();
                    }
                    else break;
                    if(i==0){
                        // this means all digits were zero, 
                        // generally, this condition should not occur, but if occured, then 
                        explicit_number.exponent  =0;
                        explicit_number.digits = {0};
                        explicit_number.positive = true;
                        return;
                    }
                }
            
                _exponent += num_vector.size();
                explicit_number.digits = num_vector;
                explicit_number.exponent = _exponent;
                explicit_number.positive = num.positive;

                return;
            }           

            /**
             * @brief *Initializer list constructor with exponent:* Creates a boost::real::real_explicit
             * instance that represents the number where the exponent is used to set the number
             * integer part and the elements of the digits list are the digits the number in the same order.
             * The number is set as positive.
             *
             * @param digits - an initializer_list<T> that represents the number digits.
             * @param exponent - an integer representing the number exponent.
             */
            real_explicit<T>(std::initializer_list<T> digits, int exponent) : explicit_number(digits, exponent)
            {};

            /**
             * @brief *Initializer list constructor with exponent and sign:* Creates a
             * boost::real::real_explicit instance that represents the number where the exponent
             * is used to set the number integer part and the elements of the digit list are the
             * digits of the number in the same order. This constructor uses the sign to determine
             * if the number is positive or negative.
             *
             * @param digits - an initializer_list<T> that represents the number digits.
             * @param exponent - an integer representing the number exponent.
             * @param positive - a bool that represents the number sign. If positive is set to true,
             * the number is positive, otherwise is negative.
             */
            real_explicit<T>(std::initializer_list<T> digits, int exponent, bool positive) : 
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
            const std::vector<T>& digits() const {
                return explicit_number.digits;
            }

            const std::string as_string() const {
                return explicit_number.as_string();
            }

            exact_number<T> get_exact_number() const {
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
            T operator[](unsigned int n) const {
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
            real_explicit<T>& operator=(const real_explicit<T>& other) = default;

            
        };

        namespace literals{
            template<typename T>
            const real_explicit<T> zero_explicit = real_explicit<T>("0");

            template<typename T>
            const real_explicit<T> one_explicit = real_explicit<T>("1");
        }
    }
}



#endif //BOOST_REAL_REAL_EXPLICIT_HPP

#ifndef BOOST_REAL_MATH_HPP
#define BOOST_REAL_MATH_HPP

#include <tuple>
#include "real/exact_number.hpp"
#include "real/real_exception.hpp"

namespace boost{
	namespace real{
		/**
		 *  EXPONENT FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates exponent of a exact_number using taylor expansion
		 * @param: num: the exact number. whose exponent is to be found
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		exact_number<T> exponent(exact_number<T> num, size_t max_error_exponent, bool upper){
			exact_number<T> result("1");
			exact_number<T> term_number("1");
			exact_number<T> factorial("1");
			exact_number<T> cur_term("0");
			exact_number<T> max_error(std::vector<T> {1}, -max_error_exponent, true);
			exact_number<T> x_pow("1");
			do{
				result += cur_term;
				factorial *= term_number;
				term_number = term_number + literals::one_exact<T>;
				x_pow *= num;
				cur_term = x_pow;
				cur_term.divide_vector(factorial, max_error_exponent, upper);
			}while(cur_term.abs() > max_error);
			result = result.up_to(max_error_exponent, upper);
			return result;
		}

		/**
		 *  LOGARITHM(BASE e) FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates log(base e) of a exact_number using taylor expansion
		 * @param: x: the exact number. whose logarithm (ln(x)) is to be found
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		exact_number<T> logarithm(exact_number<T> x, size_t max_error_exponent, bool upper){
			// log is only defined for numbers greater than 0
			static const exact_number<T> two("2");
			if(x == literals::zero_exact<T> || x.positive == false){
				throw logarithm_not_defined_for_non_positive_number();
			}
			exact_number<T> result("0");
			exact_number<T> term_number("1");
			unsigned int term_number_int = 1;
			exact_number<T> cur_term("0");
			exact_number<T> x_pow ("1");
			exact_number<T> max_error(std::vector<T> {1}, -max_error_exponent, true);
			
			if(x > literals::zero_exact<T> && x < two){
				do{
					if(term_number_int %2 == 1)
						result -= cur_term;
					else 
						result += cur_term;	
					x_pow = x_pow * (x - literals::one_exact<T>);
					cur_term = x_pow;
					cur_term.divide_vector(term_number, max_error_exponent, upper);
					++term_number_int;
					term_number = term_number + literals::one_exact<T>;
				}while(cur_term.abs() > max_error);
				return result;
			}

			do{
				result += cur_term;
				x_pow = x_pow * (x - literals::one_exact<T>);
				x_pow.divide_vector(x, max_error_exponent, upper);
				cur_term = x_pow ;
				cur_term.divide_vector(term_number, max_error_exponent, upper);
				++term_number_int;
				term_number = term_number + literals::one_exact<T>;
			}while(cur_term.abs() > max_error);
			result = result.up_to(max_error_exponent, upper);
			return result;
		}
		/**
		 *  LOGARITHM(BASE 10) FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates log(base 10) of a exact_number using taylor expansion
		 * @param: x: the exact number. whose logarithm (log10(x)) is to be found
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Harsh Agarwal
		 **/
		template<typename T>
		exact_number<T> logarithm(exact_number<T> x, size_t max_error_exponent, bool upper){
			// log is only defined for numbers greater than 0
			static const exact_number<T> two("2");
			if(x == literals::zero_exact<T> || x.positive == false){
				throw logarithm base 10_not_defined_for_non_positive_number();
			}
			exact_number<T> result("0");
			exact_number<T> term_number("1");
			unsigned int term_number_int = 1;
			exact_number<T> cur_term("0");
			exact_number<T> x_pow ("1");
			exact_number<T> max_error(std::vector<T> {1}, -max_error_exponent, true);
			
			if(x > literals::zero_exact<T> && x < two){
				do{
					if(term_number_int %2 == 1)
						result -= cur_term;
					else 
						result += cur_term;	
					x_pow = x_pow * (x - literals::one_exact<T>);
					cur_term = x_pow;
					cur_term.divide_vector(term_number, max_error_exponent, upper);
					++term_number_int;
					term_number = term_number + literals::one_exact<T>;
				}while(cur_term.abs() > max_error);
				return result;
			}

			do{
				result += cur_term;
				x_pow = x_pow * (x - literals::one_exact<T>);
				x_pow.divide_vector(x, max_error_exponent, upper);
				cur_term = x_pow ;
				cur_term.divide_vector(term_number, max_error_exponent, upper);
				++term_number_int;
				term_number = term_number + literals::one_exact<T>;
			}while(cur_term.abs() > max_error);
			result = result.up_to(max_error_exponent, upper);
			return result;
		}

		/**
		 *  SINE FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates sin(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number, representing angle in radian
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		exact_number<T> sine(exact_number<T> x, size_t max_error_exponent, bool upper){
			exact_number<T> result("0");
			exact_number<T> term_number("0");
			unsigned int term_number_int = 0;
			exact_number<T> cur_term(x);
			exact_number<T> x_pow(x);
			exact_number<T> factorial("1");
			exact_number<T> tmp;
			exact_number<T> x_square = x*x;
			exact_number<T> max_error(std::vector<T> {1}, -max_error_exponent, true);
			static exact_number<T> two("2");
			
			do{
				if(term_number_int % 2 == 0){ // if this term is even
					result += cur_term;
				}
				else 
					result -= cur_term; // if this term is odd
				++term_number_int;
				term_number = term_number + literals::one_exact<T>;
				x_pow *= x_square; // increasing power by two powers of original x
				factorial = factorial * ( two * term_number) * ( (two * term_number) + literals::one_exact<T>); // increasing the values of factorial by two
				cur_term  = x_pow;
				cur_term.divide_vector(factorial, max_error_exponent, upper);
			}while(cur_term.abs() > max_error);
			result = result.up_to(max_error_exponent, upper);
			return result;
		}

		/**
		 *  COSINE FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates cos(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number, representing angle in radian
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		exact_number<T> cosine(exact_number<T> x, size_t max_error_exponent, bool upper){
			exact_number<T> result("1");
			exact_number<T> cur_term("0");
			exact_number<T> square_x = x*x;
			exact_number<T> cur_power("1");
			exact_number<T> factorial("1");
			static exact_number<T> two("2");
			exact_number<T> term_number("0");
			exact_number<T> max_error(std::vector<T> {1}, -max_error_exponent, true);
			int term_number_int = 0;
			do{
				if(term_number_int % 2 == 0)
					result += cur_term;
				else 
					result -= cur_term;
				
				for(exact_number<T> i = (two * term_number) + literals::one_exact<T> ; i <= two * (term_number + literals::one_exact<T>); i = i + literals::one_exact<T>){
					factorial *= i;
				}
				cur_power *= square_x;
				cur_term = cur_power;
				cur_term.divide_vector(factorial, max_error_exponent, upper);
				++ term_number_int;
				term_number = term_number + literals::one_exact<T>;
				
			}while(cur_term.abs() > max_error);
			result = result.up_to(max_error_exponent, upper);
			return result;
		}

		 
		 /**
		 *  SINE AND COSINE FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates cos(x) and sin(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number, representing angle in radian
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @return: a tuple containing sin(x) and cos(x)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		std::tuple<exact_number<T>, exact_number<T> > sin_cos(exact_number<T> x, size_t max_error_exponent, bool upper){
			exact_number<T> sin_result("0");
			exact_number<T> cos_result("0");
			exact_number<T> cur_sin_term = x;
			exact_number<T> cur_cos_term("1");
			exact_number<T> cur_power = x;
			exact_number<T> factorial("1");
			static exact_number<T> two("2");
			exact_number<T> factorial_number("1");
			unsigned int term_number_int = 0;
			exact_number<T> max_error(std::vector<T> {1}, -max_error_exponent, true);
			do{

				if(term_number_int % 2 == 0){
					sin_result += cur_sin_term;
					cos_result += cur_cos_term;
				}
				else{
					sin_result -= cur_sin_term;
					cos_result -= cur_cos_term;
				}
				++term_number_int;
				factorial_number = factorial_number + literals::one_exact<T>;
				factorial *= factorial_number;
				cur_power *= x;
				cur_cos_term = cur_power;
				cur_cos_term.divide_vector(factorial, max_error_exponent, upper);

				factorial_number = factorial_number + literals::one_exact<T>;
				factorial *= factorial_number;
				cur_power *= x;
				cur_sin_term = cur_power;
				cur_sin_term.divide_vector(factorial, max_error_exponent, upper);
			}while( (cur_cos_term.abs() > max_error) || (cur_sin_term.abs() > max_error) );

			return std::make_tuple(sin_result, cos_result);
		}

		/**
		 *  TANGENT FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates tan(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number, representing angle in radian
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		inline exact_number<T> tangent(exact_number<T> x, size_t max_error_exponent, bool upper){
			auto [result, cos] = sin_cos(x, max_error_exponent, upper);
			result.divide_vector(cos, max_error_exponent, upper);
			result = result.up_to(max_error_exponent, upper);
			return result; 
		}

		/**
		 *  COTANGENT FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates cot(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number, representing angle in radian
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		inline exact_number<T> cotangent(exact_number<T> x, size_t max_error_exponent, bool upper){
			auto [sin, result] = sin_cos(x, max_error_exponent, upper);
			result.divide_vector(sin, max_error_exponent, upper);
			result = result.up_to(max_error_exponent, upper);
			return result; 
		}

		/**
		 *  SECANT FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates sec(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number, representing angle in radian
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		inline exact_number<T> secant(exact_number<T> x, size_t max_error_exponent, bool upper){
			exact_number<T> result("1");
			exact_number<T> cos = cosine(x, max_error_exponent, upper);
			result.divide_vector(cos, max_error_exponent, upper);
			result = result.up_to(max_error_exponent, upper);
			return result;
		}

		/**
		 *  COSECANT FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates cosec(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number, representing angle in radian
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		inline exact_number<T> cosecant(exact_number<T> x, size_t max_error_exponent, bool upper){
			exact_number<T> result("1");
			exact_number<T> sin = sine(x, max_error_exponent, upper);
			result.divide_vector(sin, max_error_exponent, upper);
			result = result.up_to(max_error_exponent, upper);
			return result;
		}

	}
}

#endif//BOOST_REAL_MATH_HPP
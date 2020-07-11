#include "real/real.hpp"

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
			exact_number<T> one("1");
			exact_number<T> term_number("1");
			exact_number<T> factorial("1");
			exact_number<T> cur_term("0");
			exact_number<T> max_error(std::vector<T> {1}, -max_error_exponent, true);
			exact_number<T> x_pow("1");
			do{
				result += cur_term;
				factorial *= term_number;
				term_number += one;
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
			exact_number<T> result("0");
			exact_number<T> term_number("1");
			unsigned int term_number_int = 1;
			exact_number<T> cur_term("0");
			exact_number<T> x_pow ("1");
			exact_number<T> max_error(std::vector<T> {1}, -max_error_exponent, true);
			static exact_number<T> one("1");
			static const exact_number<T> zero("0");
			static const exact_number<T> two("2");
			if(x > zero && x < two){
				do{
					if(term_number_int %2 == 1)
						result -= cur_term;
					else 
						result += cur_term;	
					x_pow = x_pow * (x - one);
					cur_term = x_pow;
					cur_term.divide_vector(term_number, max_error_exponent, upper);
					++term_number_int;
					term_number += one;
				}while(cur_term.abs() > max_error);
				return result;
			}

			do{
				result += cur_term;
				x_pow = x_pow * (x-one);
				x_pow.divide_vector(x, max_error_exponent, upper);
				cur_term = x_pow ;
				cur_term.divide_vector(term_number, max_error_exponent, upper);
				++term_number_int;
				term_number += one;
			}while(cur_term.abs() > max_error);
			result = result.up_to(max_error_exponent, upper);
			return result;
		}

		/**
		 *  SINE FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates sin(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number.
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
			static exact_number<T> one("1");
			static exact_number<T> two("2");
			
			do{
				if(term_number_int % 2 == 0){ // if this term is even
					result += cur_term;
				}
				else 
					result -= cur_term; // if this term is odd
				++term_number_int;
				term_number += one;
				x_pow *= x_square; // increasing power by two powers of original x
				factorial = factorial * ( two * term_number) * ( (two * term_number) + one); // increasing the values of factorial by two
				cur_term  = x_pow;
				cur_term.divide_vector(factorial, max_error_exponent, upper);
			}while(cur_term.abs() > max_error);
			result = result.up_to(max_error_exponent, upper);
			return result;
		}

		/**
		 *  COSINE FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates cos(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number.
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
			static exact_number<T> one("1");
			static exact_number<T> two("2");
			exact_number<T> term_number("0");
			exact_number<T> max_error(std::vector<T> {1}, -max_error_exponent, true);
			int term_number_int = 0;
			do{
				if(term_number_int % 2 == 0)
					result += cur_term;
				else 
					result -= cur_term;
				
				for(exact_number<T> i = (two * term_number) + one ; i <= two * (term_number + one); i += one){
					factorial *= i;
				}
				cur_power *= square_x;
				cur_term = cur_power;
				cur_term.divide_vector(factorial, max_error_exponent, upper);
				++ term_number_int;
				term_number += one;
				
			}while(cur_term.abs() > max_error);
			result = result.up_to(max_error_exponent, upper);
			return result;
		}

		/**
		 *  TANGENT FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates tan(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number.
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		inline exact_number<T> tangent(exact_number<T> x, size_t max_error_exponent, bool upper){
			exact_number<T> result = sine(x, max_error_exponent, upper);
			exact_number<T> cos = cosine(x,  max_error_exponent, upper);
			result.divide_vector(cos, max_error_exponent, upper);
			result = result.up_to(max_error_exponent, upper);
			return result; 
		}

		/**
		 *  COTANGENT FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates cot(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number.
		 * @param: max_error_exponent: Absolute Error in the result should be < 1*base^(-max_error_exponent)
		 * @param:  upper: if true: error lies in [0, +epsilon]
		 *                  else: error lies in [-epsilon, 0], here epsilon = 1*base^(-max_error_exponent)
		 * @author: Vikram Singh Chundawat
		 **/
		template<typename T>
		inline exact_number<T> cotangent(exact_number<T> x, size_t max_error_exponent, bool upper){
			exact_number<T> result = cosine(x, max_error_exponent, upper);
			exact_number<T> sin = sine(x,  max_error_exponent, upper);
			result.divide_vector(sin, max_error_exponent, upper);
			result = result.up_to(max_error_exponent, upper);
			return result; 
		}

		/**
		 *  SECANT FUNCTION USING TAYLOR EXPANSION
		 * @brief: calculates sec(x) of a exact_number using taylor expansion
		 * @param: x: the exact_number.
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
		 * @param: x: the exact_number.
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
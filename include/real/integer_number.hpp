#ifndef BOOST_REAL_INTEGER_NUMBER
#define BOOST_REAL_INTEGER_NUMBER


#include<vector>
#include<limits>
#include<algorithm>
#include<iterator>
#include <real/real_exception.hpp>
#include <real/interval.hpp>
#include<real/exact_number.hpp> //for some methods, that are declared in this file
#include <real/real_exception.hpp>
#include<real/convenience.hpp>

namespace boost{
	namespace real{

		/**
		 * Written by Vikram Singh Chundawat.
		 * This is representation for integer type numbers, for boost::real numbers. 
		 * As there is no need for precision iterator for operations on integer type numbers, So doing calculations 
		 * using precision iterators is unnecessary. So, we are declaring new methods for calculations on these types
		 * of numbers.
		 **/
		template<typename T = int>
		struct integer{
			

			T BASE = ((std::numeric_limits<T>::max()/2) +1);
			std::vector<T> digits = {};
			bool positive = true;

			// method to add two integer type numbers
			// base is not taken as a paramter, because it is already defined up there
			// this function will not take account into the signs of numbers, it will simply add them
			// signs will will taken care of when we will define operator overloading for these numbers
			integer<T> add_integer_number(integer &other)
			{
				int carry = 0;
				T sum = 0;
				size_t n1 = (*this).digits.size();
				size_t n2 = other.digits.size();
				size_t n = std::max(n1, n2);

				std::vector<T> result_vec(n, 0);

				for(size_t i=1;i<=n;i++)
				{
					sum = 0;
					sum+=carry;
					carry = 0;
					if(i <= n1) sum+=(*this).digits[n1-i];
					if(sum>=BASE){
						++carry;
						sum-=BASE;
					}

					if(i <= n2) sum+= other.digits[n2-i];

					if(sum >= BASE)
					{
						++carry;
						sum -= BASE;
					}
					result_vec[n-i] = sum;
				}

				if(carry!=0) result_vec.insert(result_vec.begin(), carry);

				integer<T> result(result_vec);
				return result;
			}

			/**
			 * This function is for subtracting two integer type numbers.
			 * All signs and lengths of vectors will be managed by operator overload function
			 * This function will simply Subtract vector A from B, and A should be bigger than B.
			 * These conditions will be checked by operator overload and this function will be called in an appropriate manner.
			 **/
			integer<T> subtract_integer_number(integer<T> &other)
			{
				// it is assumed that digits in (*this) are greater than digits in other
				int borrow = 0;
				T val = 0;
				size_t n1 = (*this).digits.size();
				size_t n2 = other.digits.size();
				std::vector<T> result_vec(n1);
				for(int i=0;i<n1;i++)
				{
					val += borrow;
					borrow = 0;
					if(i<n2) val += other.digits[n2-i-1];
					if(val > (*this).digits[n1-i-1])
					{
						borrow = 1;
						// equivqlent to (*this).digits[n1-i] + BASE - val
						result_vec[n1-i-1] = (BASE - val) + (*this).digits[n1-i-1];
					}
					else result_vec[n1-i-1] = (*this).digits[n1-i-1] - val;
					val = 0;
				}
				// this function always expects (*this) to bigger than other, so if borrow is not zero at the end
				// there should be error
				if(borrow!=0); 
					//throw subtraction_number_required_lower_exception();

				// now we need to remove extra zeroes, that we may get after subtraction

				typename std::vector<T> :: iterator itr = result_vec.begin();
				while((*itr)==0 && itr!=result_vec.end()) itr++;
				// if initial element was zero, then we need to delete all initial zeroes
				if(result_vec[0]==0)
				{
					//itr--;
					result_vec.erase(result_vec.begin(), itr);
				}
				if(result_vec.size()==0) result_vec.push_back(0);
				integer result(result_vec);
				return result;
			}



			// overloading operators for integer numbers

			bool operator == (const integer<T> other) const{
				if((*this).positive != other.positive) return false;
				if((*this).digits.size()!=other.digits.size()) return false;
				return (*this).digits==other.digits;
			}

			bool operator != (const integer other) const{
				return !((*this)==other);
			}

			// '>' comparison operator for two integer types
			bool operator > (const integer other) const{
				if((*this).positive != other.positive)
					return (*this).positive;

				// if sign of both numbers are positive
				if((*this).positive)
				{
					if((*this).digits.size()!=other.digits.size()) 
						return (*this).digits.size() > other.digits.size();
					return (*this).digits > other.digits;
				}

				// now only case  that is remaining is both numbers are negative
				if((*this).digits.size()!=other.digits.size()) 
						return (*this).digits.size() < other.digits.size();

				return (*this).digits < other.digits;
			}

			// '<=' operator for two integer types
			bool operator >= (const integer other) const{
				return ((*this)>other || (*this)==other);
			}

			bool operator < (const integer other) const{
				return !((*this)>=other);
			}

			bool operator <= (const integer other) const{
				return !((*this)>other);
			}


			// overloading + operator for integer types
			integer<T> operator + (integer<T> other)
			{
				integer<T> result;
				std::vector<char> hululu(10, 'c'), lulu(11, 'b');
				if(hululu==lulu);
				if((*this).positive == other.positive)  // of both signs are same, then simply add two vectors
				{
					result = (*this).add_integer_number(other);
					result.positive = (*this).positive;
					return result;
				}
				// now if signs of both numbers are not same
				else {
					if((*this).digits > other.digits)
					{
						result = (*this).subtract_integer_number(other);
						if(other.positive == false)
						{
							// if other was negative, and also other was small in quantity, then whole number is positive
							result.positive = true;
							return result;
						}
						else
						{
							// if "other" was positive, and smaller than "this", which was negative, then whole number should be negative
							result.positive = false;
							return result;
						}
					}
					else
					{
						result = other.subtract_integer_number((*this));
						// (*this) was negative, or result is zero, then sign should be positive
						if((*this).positive==false || (result.digits.size()==1 && result.digits[0]==0))
						{
							result.positive = true;
							return result;
						}
						else
						{
							result.positive = false;
							return result;
						}
					}
				}
			}

			// overloading "-" operator 
			integer<T> operator - (integer<T> other)
			{
				integer<T> result;
				// if signs of boths numbers are equal
				if((*this).positive == other.positive)
				{
					if((*this).digits>=other.digits)
					{
						result = (*this).subtract_integer_number(other);
						result.positive = true;
						return result;
					}
					else 
					{
						result = other.subtract_integer_number((*this));
						result.positive = false;
						return result;
					}
				}
				else{
					if(other.positive==false)
					{
						result = (*this).add_integer_number(other);
						result.positive = true;
						return result;
					}
					else
					{
						result = (*this).add_integer_number(other);
						result.positive = false;
						return result;
					}
				}
			}

			integer<T> operator * (integer<T> other){
				integer<T> result;
				if((*this)==integer<T>("0") || other==integer<T>("0"))
					return integer<T>("0");
				// if sign of both numbers are same, then number is positive, else negative
				result.positive = !((*this).positive^other.positive);
				result.digits = multiply<T>((*this).digits, other.digits, BASE);
				return result;
			}

			inline void operator *=(integer<T> other){
				auto result = (*this) * other;
				(*this) = result;
				return;
			}

			inline void operator += (integer<T> other){
				auto result = (*this) + other;
				(*this) = result;
				return;
			}

			// default contructor
			integer<T>() = default;

			/**
             * @brief Default asignment operator.
             *
             * @param other - The boost::real::integer to copy.
             */


			integer<T> &operator=(const integer<T>& other) = default;
			integer<T> operator-(void) {
				integer result = (*this);
				// if the number is zero, then no change is needed
				if(result.digits.size()==1 && result.digits.size()==0) return result;
				result.positive = (!result.positive);
				return result;
			}

			integer<T> operator % (integer &other){
				exact_number<T> op;
				std::vector<T> dividend = (*this).digits;
				std::vector<T> divisor = other.digits;
				std::vector<T> quotient;
				std::vector<T> remainder;
				op.knuthDivision(dividend,divisor,quotient,remainder, (*this).BASE);
				integer<T> result(remainder, true);
				// if sign of a in a%b is negative, then we need to add divisor in quantity we got in remainder
				// like remainder of (-7)/5 = -2, but (-7)%5 = 3
				if(!(*this).positive){
					integer<T> tmp(divisor, true);
					result = tmp - result;
				}
				return result;
			}

			integer<T> (std::vector<T> num, bool pos = true) : digits(num), positive(pos) {};

			/**
			 *@brief *Copy Constructor:* It creates an integer type real number that is a copy of 
			 *other integer type real number.
			 *
			 *@param other - The boost::real::integer number to copy.
			 */

			integer<T> (const integer<T> &other) = default;

			/**
			 *It takes an number in form of AeB or simply A, and if that number is representable as an integer,
			 *then a instance of integer type object containing that number is created, else error is throw.
			 */
			constexpr explicit integer(std::string_view number){
				auto [integer_part, decimal_part, exponent, _positive] = exact_number<>::number_from_string((std::string_view)number);
				
				// if our number contains decimal part, then it should not be an integer.
				if(!decimal_part.empty())
				{
					throw integer_contructor_for_non_integer_type();
				}

				//if integer part is empty, then the number is zero.
				if(integer_part.empty())
				{
					digits = {0};
					positive = true;
					return ;
				}

				for(const auto& c : integer_part){
					digits.push_back(c-'0');
				}

				positive = _positive;

				std::vector<T> base;
				T b = BASE;
				while(b!=0)
				{
					base.push_back(b%10);
					b/=10;
				}
				std::reverse(base.begin(), base.end());
				int curr_size = digits.size();

				for (int i = 0; i<exponent-curr_size; ++i) {
                    digits.push_back(0);
                }
                exact_number<T> op;
                std::vector<T> new_digits;
                while (!digits.empty()) {
                    std::vector<T> quotient;
                    //std::vector<T> rem;
                    std::vector<T> rem = op.long_divide_vectors(digits, base, quotient);
                    T result = 0;
                    for (auto d : rem)  
                    {
                        result = result * 10 + d;
                    }
                    
                    new_digits.push_back(result);
                    digits = quotient;
                }
                
                std::reverse (new_digits.begin(), new_digits.end());
                digits = new_digits;

			}

			T &operator[](int n) {
                return this->digits[n];
            }

            // return integer divided by divider
			// Note: result will return a integer. 
			integer<T> divide(integer<T> &divider){
				exact_number<T> op;
				std::vector<T> quotient;
				std::vector<T> remainder;
				// need to change this line after new long divide algo.
				// this will produce wrong result, because this algo will do calculations in decimal base.
				op.knuthDivision((*this).digits, divider.digits, quotient, remainder);
				integer<T> result(quotient, !((*this).positive^divider.positive));
				return result;
			}

		};

		// to find Greatest Common Divisor(GCD) of two integers
		template<typename T>
		integer<T> gcd(integer<T> a, integer<T> b) {
			static integer<T> zero = integer<T>("0"); // to avoid initialization of zero integer for every copy of this function 
    		if (b == zero) 
        		return a; 
    		return gcd(b, a % b);    
		}

		// HCF is same as GCD, only if someone choose to call HCF in place of GCD
		template<typename T>
		inline integer<T> hcf(integer<T> a, integer<T> b){
			return gcd(a,b);
		}

		/* to find Least Common Multiple (LCM) of two numbers
		 * a x b = LCM(a,b) * GCD(a,b)
		 * LCM(a,b) = (a x b)/GCD(a,b)
		 */
		template <typename T>
		integer<T> lcm(integer<T> a, integer<T> b){
			integer<T> mult = a*b;
			integer<T> result;
			integer<T> gcd_value = gcd(a,b);
			result = mult.divide(gcd_value);
			return result;
		}

		// function to get absolute value of some integer
		template<typename T>
		integer<T> abs(integer<T> num){
			// num is passed by value, so we will directly change it and return it.
			num.positive = true;
			return num;
		}



	}
}

#endif
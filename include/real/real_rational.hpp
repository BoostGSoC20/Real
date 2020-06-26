#ifndef BOOST_REAL_RATIONAL_NUMBER
#define BOOST_REAL_RATIONAL_NUMBER

#include<real/integer_number.hpp>
#include<string_view>

namespace boost{
	namespace real{

		/**
		 * Written by Vikram Singh Chundawat
		 * This representation is used to store rational numbers in form of a/b.
		 * This will have a and b as integer type numbers.
		 */
		template<typename T = int>
		struct real_rational{
			// this will number in form of a/b. Where a and b are integer type numbers.
		public:
			integer_number<T> a;
			integer_number<T> b;
			bool positive;
			T BASE;

			// to simply the representation of rational number
			// like 4/8 is converted to 1/2/
			void simplify(){
				if(a == integer_number<T>("0")){
					b = integer_number<T>("1");
					positive = true;
					return;
				}
				integer_number<T> divider = gcd(abs(a),abs(b));
				a = a.divide(divider);
				b = b.divide(divider);
				return ;
			}

			// to add a rational number to other rational number
			void add_rational(real_rational<T> other){
				a *= other.b;
				other.a *= b;
				b = b * other.b;
				a = a + other.a;
				simplify();
				return ;
			}

			void subtract_rational(real_rational<T> other){
				a *= other.b;
				other.a *= b;
				b = b * other.b;
				a = a - other.a;
				simplify();
				return ;
			}

			// to add integer number to rational number
			void add_integer(integer_number<T> &other)
			{
				a += (other*b);
				simplify();
				return;
			}

			// function to return sign of the rational number
			inline bool get_positive(){
				return (positive);
			}

			inline void alter_sign(){
				positive = (!positive);
				return ;
			}

			bool operator > (const real_rational<T> other) const{

				// if numbers have different signs
				if(positive!=other.positive) return positive;
				if(b == other.b) return a > other.a;
				real_rational<T> _this = (*this);
				real_rational<T> _other = other;
				_this.a *= _other.b;
				_other.a *= _this.b;
				// if both number are positive, (cases of different signs are already dealt)
				if(positive)
					return _this.a > _other.a;
				// only case left is both numbers are negative
				return _this.a < _other.a;
			}

			inline bool operator == (const real_rational<T> other) const{
				// since every number is store in its simplifies form, we simply need to check whether both divisor and 
				// divident are same or not
				return (a == other.a && b == other.b && positive == other.positive); 
			}

			inline bool operator >= (const real_rational<T> other) const{
				return ((*this) > other || (*this) == other);
			}

			inline bool operator < (const real_rational<T> other) const{
				return !((*this) >= other);
			}

			inline bool operator <= (const real_rational<T> other) const{
				return !((*this) > other);
			}

			// overloading comparision operators rational numbers and integers
			inline bool operator > (const integer_number<T> other) const{
				real_rational<T> _other(other, integer_number<T>("1"));
				return (*this) > _other;
			}

			// checking whether our number is equal to some integer or not
			inline bool operator == (const integer_number<T> other) const{
				if(b != integer_number<T>("1")) return false;
				return (*this).a == other;
			}

			inline bool operator >= (const integer_number<T> other) const{
				return ((*this) > other || (*this) == other);
			}

			inline bool operator < (const integer_number<T> other) const{
				return !((*this) >= other);
			}

			inline bool operator <= (const integer_number<T> other) const{ 
				return !((*this) > other);
			}

			real_rational<T> &operator = (const real_rational<T>& other) = default;

			real_rational<T> operator + (real_rational<T> other){
				// if both numbers have same sign
				real_rational<T> result;
				if(positive == other.positive){
					result = (*this);
					result.add_rational(other);
				}

				// if sign of the first number is positibe
				else if(positive){
					result = (*this);
					result.subtract_rational(other);
					if(result.a.positive) result.positive = true;
					else
					{
						result.a.positive = true;
						result.positive = false;
					}
				}
				// if second number is positive and first is negative
				else {
					result = other;
					result.subtract_rational((*this));
					if(result.a.positive) result.positive = true;
					else{
						result.a.positive = true;
						result.positive = false;
					}
				}
				// we have covered all possible cases
				return result;
			}

			inline real_rational<T> operator + (integer_number<T> other){
				real_rational<T> result = (*this) + real_rational<T>(other);
				return result;
			}

			inline void operator += (real_rational<T> other){
				real_rational<T> result = (*this) + other;
				(*this) = result;
				return;
			}

			inline void operator += (integer_number<T> other){
				(*this) = (*this) + other;
				return;
			}

			inline real_rational<T> operator - (real_rational<T> other){
				other.positive = (!other.positive);
				return (*this) + other;
			}

			inline real_rational<T> operator - (integer_number<T> other){
				other.positive = (!other.positive);
				return (*this) + other;
			}

			inline void operator -= (real_rational<T> other){
				(*this) = (*this) - other;
				return ;
			}

			inline void operator -= (integer_number<T> other){
				(*this) = (*this) - other;
				return;
			}

			real_rational<T> operator *(real_rational<T> other){
				real_rational<T> result;
				result.a = a * other.a;
				result.b = b * other.b;
				result.simplify();
				result.positive = !((positive) ^ other.positive);
				return result;
			}

			real_rational<T> operator * (integer_number<T> other){
				real_rational<T> result;
				result.a = a * other;
				result.b = b;
				result.simplify();
				result.positive = !(positive ^ other.positive);
				return result;
			}

			real_rational<T> operator - (void){
				real_rational<T> result = (*this);
				if((*this).a == integer_number<T>("0"))
					return result;

				result.positive = (!result.positive);
				return result;
			}


			

			


			// default constructor
			constexpr explicit real_rational(){
				a = integer_number<T> ("0");
				b = integer_number<T> ("1");
				positive = true;
			}
			
			// contructor for integer number, when a and b are provided as real::integer for a/b
			constexpr explicit real_rational(integer_number<T> _a, integer_number<T> _b = integer_number<T>("1")){
				a = abs(_a);
				b = abs(_b);
				if(_b==integer_number<T>("0"))
					throw divide_by_zero();
				positive = !(_a.positive ^ _b.positive);
				simplify();
				return ;
			}

			// copy constructor
			real_rational<T>(const real_rational<T> &other) = default;

			// constructor to generate get number from string
			constexpr explicit real_rational(std::string_view num){
				// searching for "/" in string
				size_t pos;
				bool found = false;
				std::string_view num1, num2;
				pos = num.size();
				for(size_t i=0;i<num.size();++i){
					if(num[i]=='/'){
						found = true;
						pos = i;
						break;
					}
				}
				num1 = num.substr(0, pos);
				if(found) 
					num2 = num.substr(pos+1, num.size());

				a = integer_number<T>(num1);

				if(found)
					b = integer_number<T>(num2);
				else 
					b = integer_number<T>("1");

				if(b == integer_number<T>("0"))
					throw divide_by_zero();

				positive = !(a.positive ^ b.positive);
				a.positive = true;
				b.positive = true;
				simplify();
				return;
			}

		};










		// operator for multiplication of an rational number with integer
		template<typename T>
		inline real_rational<T> operator * (integer_number<T> integer_num, real_rational<T> rational_num){
			return rational_num * integer_num;
		}

		// addition operator when first number is integer in addition
		template<typename T>
		inline real_rational<T> operator + (integer_number<T> integer_num, real_rational<T> rational_num){
			return rational_num + integer_num;
		}

		// subtraction operator when first number is integer in subtraction
		template<typename T>
		inline real_rational<T> operator - (integer_number<T> integer_num, real_rational<T> rational_num){
			return -(rational_num - integer_num);
		}
		

		// overloading comparision operator for comparision of integer with rational number
		// these methods are when first number is integer in comparision and second is rational number
		// a comparison b, where a is integer and b is rational number
		template<typename T>
		inline bool operator == (integer_number<T> int_num, real_rational<T> rat_num){
			return rat_num == int_num;
		}

		template<typename T>
		inline bool operator > (integer_number<T> int_num, real_rational<T> rat_num){
			real_rational<T> _this(int_num);
			return _this > rat_num;
			
		}

		template<typename T>
		inline bool operator >= (integer_number<T> int_num, real_rational<T> rat_num){
			return (int_num > rat_num || int_num == rat_num);
		}

		template<typename T>
		inline bool operator < (integer_number<T> int_num, real_rational<T> rat_num){
			return !(int_num >= rat_num);
		}

		template<typename T>
		inline bool operator <= (integer_number<T> int_num, real_rational<T> rat_num){
			return (int_num < rat_num || int_num == rat_num);
		}



		// function to return the absolute value of a rational number
		template<typename T>
		real_rational<T> abs(real_rational<T> num){
				num.positive = true;
				return num;
		}

		// floor function for rational numbers
		template<typename T>
		integer_number<T> floor(real_rational<T> num){
			// if number is of integer type, (a/1), then return a
			if(num.b == integer_number<T>("1")){
				integer_number<T> result(num.a);
				result.positive = num.positive;
				return result;
			}

			// if number is less than 1
			if(num.b > num.a){
				if(num.positive)
					return integer_number<T>("0");
				else 
					return integer_number<T>("-1");
			}

			// now only case left is number is greater than one in magnitude and not an integer type
			integer_number<T> result = num.a;
			result = result.divide(num.b);
			if(num.positive)
			{
				result.positive = true;
				return result;
			}
			// now only case left is number is negative and less than one
			result += integer_number<T>("1");
			result.positive = false;
			return result;
		}

		// ceiling function for rational numbers
		template<typename T>
		integer_number<T> ceil(real_rational<T> num){
			if(num.b == integer_number<T>("1")){
				integer_number<T> result(num.a);
				result.positive = num.positive;
				return result;
			}

			// if number is less than 1 in magnitude
			if(num.b > num.a){
				if(num.positive)
					return integer_number<T>("1");
				else 
					return integer_number<T>("0");
			}

			// now only case left is number is greater than one in magnitude and not an integer type
			integer_number<T> result = num.a;
			result = result.divide(num.b);
			if(num.positive)
			{
				result.positive = true;
				result += integer_number<T>("1");
				return result;
			}
			// now only case left is number is negative and less than one
			result.positive = false;
			return result;
		}


		// defining division for different scenarios

		// division of one rational number by another
		template<typename T>
		real_rational<T> operator / (real_rational<T> a, real_rational<T> b){
			real_rational<T> result = a;
			result.a *= b.b;
			result.b *= b.a;
			result.simplify();
			result.positive = !(a.positive ^ b.positive);
			return result;
		}

		// division of one integer by another and result is rational number
		template<typename T>
		real_rational<T> operator / (integer_number<T> a, integer_number<T> b){
			return real_rational<T>(a,b);
		}

		// division between rational number and integer and result is a rational number
		template<typename T>
		real_rational<T> operator / (real_rational<T> a, integer_number<T> b){
			a.b *= b;
			a.simplify();
			a.positive = !(a.positive ^ b.positive);
			return a;
		}

		template<typename T>
		real_rational<T> operator / (integer_number<T> a, real_rational<T> b){
			real_rational<T> result;
			result.a = b.b;
			result.b = b.a;
			result.a *= a;
			result.simplify();
			result.positive = !(a.positive ^ b.positive);
			return result;
		}

		// result is integer, and division is between integers
		template<typename T>
		integer_number<T> operator / (integer_number<T> a, integer_number<T> b){
			real_rational<T> rational_form(a,b);
			return floor(rational_form);
		}


	}
}




#endif
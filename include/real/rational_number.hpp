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
		struct rational_number{
			// this will number in form of a/b. Where a and b are integer type numbers.
		public:
			integer<T> a;
			integer<T> b;
			bool positive;
			T BASE;

			// to simply the representation of rational number
			// like 4/8 is converted to 1/2/
			void simplify(){
				if((*this).a==integer<T>("0")){
					(*this).b = integer<T>("1");
					(*this).positive = true;
					return;
				}
				integer<T> divider = gcd(abs((*this).a),abs((*this).b));
				(*this).a = (*this).a.divide(divider);
				(*this).b = (*this).b.divide(divider);
				return ;
			}

			// to add a rational number to other rational number
			void add_rational(rational_number<T> other){
				(*this).a *= other.b;
				other.a *= (*this).b;
				(*this).b = (*this).b * other.b;
				(*this).a = (*this).a + other.a;
				(*this).simplify();
				return ;
			}

			void subtract_rational(rational_number<T> other){
				(*this).a *= other.b;
				other.a *= (*this).b;
				(*this).b = (*this).b * other.b;
				(*this).a = (*this).a - other.a;
				(*this).simplify();
				return ;
			}

			// to add integer number to rational number
			void add_integer(integer<T> &other)
			{
				(*this).a += (other*(*this).b);
				(*this).simplify();
				return;
			}

			// function to return sign of the rational number
			inline bool get_positive(){
				return ((*this).positive);
			}

			inline void alter_sign(){
				(*this).positive = !(*this).positive;
				return ;
			}

			bool operator > (const rational_number<T> other) const{

				// if numbers have different signs
				if((*this).positive!=other.positive) return (*this).positive;
				if((*this).b == other.b) return (*this).a > other.a;
				rational_number<T> _this = (*this);
				rational_number<T> _other = other;
				_this.a *= _other.b;
				_other.a *= _this.b;
				// if both number are positive, (cases of different signs are already dealt)
				if((*this).positive)
					return _this.a > _other.a;
				// only case left is both numbers are negative
				return _this.a < _other.a;
			}

			inline bool operator == (const rational_number<T> other) const{
				// since every number is store in its simplifies form, we simply need to check whether both divisor and 
				// divident are same or not
				return ((*this).a==other.a && (*this).b==other.b && (*this).positive==other.positive); 
			}

			inline bool operator >= (const rational_number<T> other) const{
				return ((*this)>other || (*this)==other);
			}

			inline bool operator < (const rational_number<T> other) const{
				return !((*this)>=other);
			}

			inline bool operator <= (const rational_number<T> other) const{
				return !((*this)>other);
			}

			// overloading comparision operators rational numbers and integers
			inline bool operator > (const integer<T> other) const{
				rational_number<T> _other(other, integer<T>("1"));
				return (*this)>_other;
			}

			// checking whether our number is equal to some integer or not
			inline bool operator == (const integer<T> other) const{
				if((*this).b != integer<T>("1")) return false;
				return (*this).a == other;
			}

			inline bool operator >= (const integer<T> other) const{
				return ((*this)>other || (*this)==other);
			}

			inline bool operator < (const integer<T> other) const{
				return !((*this)>=other);
			}

			inline bool operator <= (const integer<T> other) const{ 
				return !((*this)>other);
			}

			rational_number<T> &operator=(const rational_number<T>& other) = default;

			rational_number<T> operator + (rational_number<T> other){
				// if both numbers have same sign
				rational_number<T> result;
				if((*this).positive==other.positive){
					result = (*this);
					result.add_rational(other);
				}

				// if sign of the first number is positibe
				else if((*this).positive){
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

			inline rational_number<T> operator + (integer<T> other){
				rational_number<T> result = (*this) + rational_number<T>(other);
				return result;
			}

			inline void operator += (rational_number<T> other){
				rational_number<T> result = (*this) + other;
				(*this) = result;
				return;
			}

			inline void operator += (integer<T> other){
				(*this) = (*this) + other;
				return;
			}

			inline rational_number<T> operator - (rational_number<T> other){
				other.positive = (!other.positive);
				return (*this) + other;
			}

			inline rational_number<T> operator - (integer<T> other){
				other.positive = (!other.positive);
				return (*this) + other;
			}

			inline void operator -= (rational_number<T> other){
				(*this) = (*this) - other;
				return ;
			}

			inline void operator -= (integer<T> other){
				(*this) = (*this) - other;
				return;
			}

			rational_number<T> operator *(rational_number<T> other){
				rational_number<T> result;
				result.a = (*this).a * other.a;
				result.b = (*this).b * other.b;
				result.simplify();
				result.positive = !(((*this).positive)^other.positive);
				return result;
			}

			rational_number<T> operator * (integer<T> other){
				rational_number<T> result;
				result.a = (*this).a * other;
				result.b = (*this).b;
				result.simplify();
				result.positive = !((*this).positive^other.positive);
				return result;
			}

			rational_number<T> operator - (void){
				rational_number<T> result = (*this);
				if((*this).a == integer<T>("0"))
					return result;

				result.positive = (!result.positive);
				return result;
			}


			

			


			// default constructor
			constexpr explicit rational_number(){
				(*this).a = integer<T> ("0");
				(*this).b = integer<T> ("1");
				(*this).positive = true;
			}
			
			// contructor for integer number, when a and b are provided as real::integer for a/b
			constexpr explicit rational_number(integer<T> a, integer<T> b = integer<T>("1")){
				(*this).a = abs(a);
				(*this).b = abs(b);
				if(b==integer<T>("0"))
					throw divide_by_zero();
				(*this).positive = !(a.positive^b.positive);
				(*this).simplify();
				return ;
			}

			// copy constructor
			rational_number<T>(const rational_number<T> &other) = default;

			// constructor to generate get number from string
			constexpr explicit rational_number(std::string_view num){
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

				(*this).a = integer<T>(num1);

				if(found)
					(*this).b = integer<T>(num2);
				else 
					(*this).b = integer<T>("1");

				if((*this).b == integer<T>("0"))
					throw divide_by_zero();

				(*this).positive = !((*this).a.positive^(*this).b.positive);
				(*this).a.positive = true;
				(*this).b.positive = true;
				(*this).simplify();
				return;
			}

		};










		// operator for multiplication of an rational number with integer
		template<typename T>
		inline rational_number<T> operator * (integer<T> integer_num, rational_number<T> rational_num){
			return rational_num * integer_num;
		}

		// addition operator when first number is integer in addition
		template<typename T>
		inline rational_number<T> operator + (integer<T> integer_num, rational_number<T> rational_num){
			return rational_num + integer_num;
		}

		// subtraction operator when first number is integer in subtraction
		template<typename T>
		inline rational_number<T> operator - (integer<T> integer_num, rational_number<T> rational_num){
			return -(rational_num - integer_num);
		}
		

		// overloading comparision operator for comparision of integer with rational number
		// these methods are when first number is integer in comparision and second is rational number
		// a comparison b, where a is integer and b is rational number
		template<typename T>
		inline bool operator == (integer<T> int_num, rational_number<T> rat_num){
			return rat_num==int_num;
		}

		template<typename T>
		inline bool operator > (integer<T> int_num, rational_number<T> rat_num){
			rational_number<T> _this(int_num);
			return _this > rat_num;
			
		}

		template<typename T>
		inline bool operator >= (integer<T> int_num, rational_number<T> rat_num){
			return (int_num > rat_num || int_num==rat_num);
		}

		template<typename T>
		inline bool operator < (integer<T> int_num, rational_number<T> rat_num){
			return !(int_num >= rat_num);
		}

		template<typename T>
		inline bool operator <= (integer<T> int_num, rational_number<T> rat_num){
			return (int_num<rat_num || int_num==rat_num);
		}



		// function to return the absolute value of a rational number
		template<typename T>
		rational_number<T> abs(rational_number<T> num){
				num.positive = true;
				return num;
		}

		// floor function for rational numbers
		template<typename T>
		integer<T> floor(rational_number<T> num){
			// if number is of integer type, (a/1), then return a
			if(num.b == integer<T>("1")){
				integer<T> result(num.a);
				result.positive = num.positive;
				return result;
			}

			// if number is less than 1
			if(num.b > num.a){
				if(num.positive)
					return integer<T>("0");
				else 
					return integer<T>("-1");
			}

			// now only case left is number is greater than one in magnitude and not an integer type
			integer<T> result = num.a;
			result = result.divide(num.b);
			if(num.positive)
			{
				result.positive = true;
				return result;
			}
			// now only case left is number is negative and less than one
			result += integer<T>("1");
			result.positive = false;
			return result;
		}

		// ceiling function for rational numbers
		template<typename T>
		integer<T> ceil(rational_number<T> num){
			if(num.b == integer<T>("1")){
				integer<T> result(num.a);
				result.positive = num.positive;
				return result;
			}

			// if number is less than 1 in magnitude
			if(num.b > num.a){
				if(num.positive)
					return integer<T>("1");
				else 
					return integer<T>("0");
			}

			// now only case left is number is greater than one in magnitude and not an integer type
			integer<T> result = num.a;
			result = result.divide(num.b);
			if(num.positive)
			{
				result.positive = true;
				result += integer<T>("1");
				return result;
			}
			// now only case left is number is negative and less than one
			result.positive = false;
			return result;
		}


		// defining division for different scenarios

		// division of one rational number by another
		template<typename T>
		rational_number<T> operator / (rational_number<T> a, rational_number<T> b){
			rational_number<T> result = a;
			result.a *= b.b;
			result.b *= b.a;
			result.simplify();
			result.positive = !(a.positive^b.positive);
			return result;
		}

		// division of one integer by another and result is rational number
		template<typename T>
		rational_number<T> operator / (integer<T> a, integer<T> b){
			return rational_number<T>(a,b);
		}

		// division between rational number and integer and result is a rational number
		template<typename T>
		rational_number<T> operator / (rational_number<T> a, integer<T> b){
			a.b *= b;
			a.simplify();
			a.positive = !(a.positive^b.positive);
			return a;
		}

		template<typename T>
		rational_number<T> operator / (integer<T> a, rational_number<T> b){
			rational_number<T> result;
			result.a = b.b;
			result.b = b.a;
			result.a *= a;
			result.simplify();
			result.positive = !(a.positive^b.positive);
			return result;
		}

		// result is integer, and division is between integers
		template<typename T>
		integer<T> operator / (integer<T> a, integer<T> b){
			rational_number<T> rational_form(a,b);
			return floor(rational_form);
		}


	}
}




#endif
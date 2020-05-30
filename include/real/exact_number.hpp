#ifndef BOOST_REAL_EXACT_NUMBER
#define BOOST_REAL_EXACT_NUMBER

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <type_traits>
#include <limits>
#include <iterator>
#include <cctype>

namespace boost {
    namespace real {
        template <typename T = int>
        struct exact_number {
            using exponent_t = int;

            // TODO: replace all redundant declarations of base with this
            // static const T BASE = ;

            std::vector<T> digits = {};
            exponent_t exponent = 0;
            bool positive = true;

            static bool aligned_vectors_is_lower(const std::vector<T> &lhs, const std::vector<T> &rhs, bool equal = false) {

                // Check if lhs is lower than rhs
                auto lhs_it = lhs.cbegin();
                auto rhs_it = rhs.cbegin();
                while (rhs_it != rhs.end() && lhs_it != lhs.end() && *lhs_it == *rhs_it) {
                    ++lhs_it;
                    ++rhs_it;
                }

                if (rhs_it != rhs.cend() && lhs_it != lhs.cend()) {
                    return *lhs_it < *rhs_it;
                }

                if (equal && rhs_it == rhs.cend() && lhs_it == lhs.cend())
                    return false;

                bool lhs_all_zero = std::all_of(lhs_it, lhs.cend(), [](int i){ return i == 0; });
                bool rhs_all_zero = std::all_of(rhs_it, rhs.cend(), [](int i){ return i == 0; });

                return lhs_all_zero && !rhs_all_zero;
            }

            /// adds other to *this. disregards sign -- that's taken care of in the operators.
            void add_vector(exact_number &other, T base = (std::numeric_limits<T>::max() /4)*2 - 1){
                int carry = 0;
                std::vector<T> temp;
                int fractional_length = std::max((int)this->digits.size() - this->exponent, (int)other.digits.size() - other.exponent);
                int integral_length = std::max(this->exponent, other.exponent);

                // we walk the numbers from the lowest to the highest digit
                for (int i = fractional_length - 1; i >= -integral_length; i--) {

                    T lhs_digit = 0;
                    if (0 <= this->exponent + i && this->exponent + i < (int)this->digits.size()) {
                        lhs_digit = this->digits[this->exponent + i];
                    }

                    T rhs_digit = 0;
                    if (0 <= other.exponent + i && other.exponent + i < (int)other.digits.size()) {
                        rhs_digit = other.digits[other.exponent + i];
                    }
                    
                    T digit;
                    int orig_carry = carry;
                    carry = 0;
                    if ((base - lhs_digit) < rhs_digit) {
                        T min = std::min(lhs_digit, rhs_digit);
                        T max = std::max(lhs_digit, rhs_digit);
                        if (min <= base/2) {
                            T remaining = base/2 - min;
                            digit = (max - base/2) - remaining - 2;
                        } else {
                            digit = (min - base/2) + (max - base/2) - 2;
                        }
                        carry = 1;
                    }
                    else {
                        carry = 0;
                        digit = rhs_digit + lhs_digit;
                    }
                    if (digit < base || orig_carry == 0) {
                        digit += orig_carry;
                    }
                    else {
                        carry = 1;
                        digit = 0;
                    }
                    temp.insert(temp.begin(), digit);
                }
                if (carry == 1) {
                    temp.insert(temp.begin(), 1);
                    integral_length++;
                }
                this->digits = temp;
                this->exponent = integral_length;
                this->normalize();
            }

            /// subtracts other from *this, disregards sign -- that's taken care of in the operators
            void subtract_vector(exact_number &other, T base = (std::numeric_limits<T>::max() /4)*2 - 1) {
                std::vector<T> result;
                int fractional_length = std::max((int)this->digits.size() - this->exponent, (int)other.digits.size() - other.exponent);
                int integral_length = std::max(this->exponent, other.exponent);
                int borrow = 0;
                // we walk the numbers from the lowest to the highest digit
                for (int i = fractional_length - 1; i >= -integral_length; i--) {

                    T digit = 0;

                    T lhs_digit = 0;
                    if (0 <= this->exponent + i && this->exponent + i < (int)this->digits.size()) {
                        lhs_digit = this->digits[this->exponent + i];
                    }

                    T rhs_digit = 0;
                    if (0 <= other.exponent + i && other.exponent + i < (int) other.digits.size()) {
                        rhs_digit = other.digits[other.exponent + i];
                    }

                    if (lhs_digit < borrow) {
                        digit = (base - rhs_digit) + 1 - borrow;
                    } else {
                        lhs_digit -= borrow;
                        borrow = 0;
                        
                        if (lhs_digit < rhs_digit) {
                        ++borrow;
                        digit = (base - (rhs_digit -1)) + lhs_digit;
                        } else {
                            digit = lhs_digit - rhs_digit;
                        }
                        
                    }                    
                    result.insert(result.begin(), digit);
                }
                this->digits = result;
                this->exponent = integral_length;
                this->normalize();
            }

            //Returns (a*b)%mod
            inline T mulmod(T a, T b, T mod) 
            { 
                T res = 0; // Initialize result 
                a = a % mod; 
                while (b > 0) 
                { 
                    // If b is odd, add 'a' to result 
                    if (b % 2 == 1) 
                        res = (res + a) % mod; 
            
                    // Multiply 'a' with 2 
                    a = (a * 2) % mod; 
            
                    // Divide b by 2 
                    b /= 2; 
                } 
            
                return res % mod; 
            }

            //Returns (a*b)/mod
            inline T mult_div(T a, T b, T c) {
                T rem = 0;
                T res = (a / c) * b;
                a = a % c;
                // invariant: a_orig * b_orig = (res * c + rem) + a * b
                // a < c, rem < c.
                while (b != 0) {
                    if (b & 1) {
                        rem += a;
                        if (rem >= c) {
                            rem -= c;
                            res++;
                        }
                    }
                    b /= 2;
                    a *= 2;
                    if (a >= c) {
                        a -= c;
                        res += b;
                    }
                }
                return res;
            } 

            /// multiplies *this by other
            void multiply_vector(exact_number &other, T base = (std::numeric_limits<T>::max() /4)*2) {
                // will keep the result number in vector in reverse order
                // Digits: .123 | Exponent: -3 | .000123 <--- Number size is the Digits size less the exponent
                // Digits: .123 | Exponent: 2  | 12.3
                std::vector<T> temp;
                size_t new_size = this->digits.size() + other.digits.size();
                if (this->exponent < 0) new_size -= this->exponent; // <--- Less the exponent
                if (other.exponent < 0) new_size -= other.exponent; // <--- Less the exponent

                temp.assign(new_size, 0);

                // Below two indexes are used to find positions
                // in result.
                auto i_n1 = (int) temp.size() - 1;
                // Go from right to left in lhs
                for (int i = (int)this->digits.size()-1; i >= 0; i--) {
                    T carry = 0;

                    // To shift position to left after every
                    // multiplication of a digit in rhs
                    int i_n2 = 0;

                    // Go from right to left in rhs
                    for (int j = (int)other.digits.size()-1; j>=0; j--) {

                        // Multiply current digit of second number with current digit of first number
                        // and add result to previously stored result at current position.
                        T rem = mulmod(this->digits[i], other.digits[j], base);
                        T rem_s;
                        T q = mult_div(this->digits[i], other.digits[j], base);
                        if ( temp[i_n1 - i_n2] >= base - carry ) {
                            rem_s = carry - (base - temp[i_n1 - i_n2]);
                            ++q;
                        }
                        else
                            rem_s = temp[i_n1 - i_n2] + carry;
                        if ( rem >= base - rem_s ) {
                            rem -= (base - rem_s);
                            ++q;
                        }
                        else
                            rem += rem_s;

                        // Carry for next iteration
                        carry = q;

                        // Store result
                        temp[i_n1 - i_n2] = rem;

                        i_n2++;
                    }

                    // store carry in next cell
                    if (carry > 0) {
                        temp[i_n1 - i_n2] += carry;
                    }

                    // To shift position to left after every
                    // multiplication of a digit in lhs.
                    i_n1--;
                }

                int fractional_part = ((int)this->digits.size() - this->exponent) + ((int)other.digits.size() - other.exponent);
                int result_exponent = (int)temp.size() - fractional_part;
                
                digits = temp;
                exponent = result_exponent;
                this->positive = this->positive == other.positive;
                this->normalize();
            }

            //Performs long division on dividend by divisor and returns result in quotient
            std::vector<T> long_divide_vectors(
                    const std::vector<T>& dividend,
                    const std::vector<T>& divisor,
                    std::vector<T>& quotient
            ) {
                
                exact_number<T> tmp;
                std::vector<T> aligned_dividend = dividend;
                std::vector<T> aligned_divisor = divisor;
                size_t idx = 0;
                while(idx < aligned_dividend.size() && aligned_dividend[idx] == 0)
                    idx++;
                aligned_dividend.erase(aligned_dividend.begin(), aligned_dividend.begin() + idx);

                if(aligned_dividend.empty()) {
                    quotient.clear();
                    return std::vector<T>();
                }
                if ((aligned_dividend.size() == aligned_divisor.size() && 
                        tmp.aligned_vectors_is_lower(aligned_dividend, aligned_divisor)) || 
                            aligned_dividend.size() < aligned_divisor.size()) {
                    quotient.clear();
                    return aligned_dividend;
                }

                std::vector<T> current_dividend(
                        aligned_dividend.begin(),
                        aligned_dividend.begin() + aligned_divisor.size()
                );
                auto next_digit = aligned_dividend.begin() + aligned_divisor.size();
                std::vector<T> residual = aligned_dividend;

                while (true) {
                    // Obtain the smaller part of the dividend that is greater than the divisor

                    // Obtaining the greater digit by which the divisor can be multiplied and still be lower than the dividend
                    bool flg = false;
                    if (next_digit == aligned_dividend.end())
                        flg = true;
                    std::vector<T> closest;
                    T digit = 0;
                    do {
                        digit++;
                        std::vector<T> multiplier = {digit};
                        tmp = (exact_number<T>(aligned_divisor).base10_mult(exact_number<T>(multiplier)));
                        closest = tmp.digits;
                        while (tmp.exponent - (int)tmp.digits.size() > 0) {
                            closest.push_back(0);
                            tmp.exponent--;
                        }
                        size_t idx = 0;
                        while(idx < closest.size() && closest[idx]==0) 
                            ++idx;
                        closest.erase(closest.begin(), closest.begin() + idx);

                    } while(
                            closest.size() < current_dividend.size() ||
                            (
                                    closest.size() == current_dividend.size() &&
                                    !tmp.aligned_vectors_is_lower(
                                    current_dividend, closest, true)
                            ) // closes <= current_dividend
                    );

                    // i should be in [1, 10] and i - 1 in [0, 9]
                    // The found digit is the next digit in the quotient result
                    quotient.push_back(digit-1);

                    // Update the residual for the next iteration where more digits of the dividend will be considered
                    std::vector<T> multiplier = {digit-1};
                    tmp = (exact_number<T>(aligned_divisor).base10_mult(exact_number<T>(multiplier)));
                    closest = tmp.digits;
                    while (tmp.exponent - (int)tmp.digits.size() > 0) {
                        closest.push_back(0);
                        tmp.exponent--;
                    }
                    residual.clear();
                    tmp = (exact_number<T>(current_dividend).base10_subtract(exact_number<T>(closest)));
                    residual = tmp.digits;
                    while (tmp.exponent - (int)tmp.digits.size() > 0) {
                        residual.push_back(0);
                        tmp.exponent--;
                    }
                    size_t idx = 0;
                    while(idx < residual.size() && residual[idx]==0)
                        ++idx;
                    residual.erase(residual.begin(), residual.begin() + idx);
                    current_dividend = residual;
                    if (flg)
                        break;
                    current_dividend.push_back(*next_digit);
                    ++next_digit;
                }
                idx = 0;
                while(idx < quotient.size() && quotient[idx] == 0)
                    idx++;
                quotient.erase(quotient.begin(), quotient.begin() + idx);
                return residual;
            }

            /// calculates *this / divisor 
            /// 
            ///  @brief a binary-search type method for dividing exact_numbers.
            ///  @param is_upper true: returns result with an error of +epsilon, while
            ///                  false: returns result with an error of -epsilon
            void divide_vector(exact_number<T> divisor, unsigned int maximum_precision) {
                /// @TODO: replace this with something more efficient, like newton-raphson method
                // it also completely recalculates on each precision increase
                // instead, could use previous information to make better "guesses"
                // for our iteration scheme.

                boost::real::exact_number<T> numerator;
                boost::real::exact_number<T> left;
                boost::real::exact_number<T> right;
                boost::real::exact_number<T> residual;
                boost::real::exact_number<T> tmp;
                boost::real::exact_number<T> half;
                boost::real::exact_number<T> distance;
                boost::real::exact_number<T> min_boundary_n;
                boost::real::exact_number<T> min_boundary_p;

                bool positive = ((*this).positive == divisor.positive);
                numerator = (*this).abs();
                divisor = divisor.abs();

                // ensuring that assignment from -1 * (maximum_precision) to exponent will not
                // overflow
                if (maximum_precision > (unsigned int) std::abs(std::numeric_limits<exponent_t>::min())) {
                    throw exponent_overflow_exception();
                }

                min_boundary_n.digits = {1};
                min_boundary_n.exponent = -1 * (maximum_precision);
                min_boundary_n.positive = false;

                min_boundary_p.digits = {1};
                min_boundary_p.exponent = -1 * (maximum_precision);

                T base = (std::numeric_limits<T>::max() /4)*2 - 1;
                T H = base/2 + 1;
                half.digits = {H};
                half.exponent = 0;

                // we ignore exponents, then set them in the end.
                // (a * 10^x) / (b*10^y) = (a*10 / b*10) * 10^((x-1)-(y-1))
                // 100/20 -> 1/2 * (10)
                int exponent_dif = (numerator.exponent - 1) - (divisor.exponent - 1);

                numerator.exponent = 1;
                divisor.exponent = 1;
                tmp.digits = {1};
                tmp.exponent = 1;

                exact_number<T> zero = exact_number<T>(); 

                if (divisor == tmp) {
                    this->exponent = exponent_dif + 1;
                    this->positive = positive;
                    return;
                }

                if (divisor == (*this)) { 
                    (*this) = tmp;
                    (*this).positive = positive;
                    return;
                }

                if ((*this) == zero)
                    return;
                    
                if (divisor == zero)
                    throw(boost::real::divide_by_zero());

                // N < D --> 0 < abs(Q) < 1
                if (numerator < divisor) {
                        left = exact_number<T>(); // 0
                        right = tmp; // 1
                    } else { // assuming D > 1. N > D ---> 1 < N / D < N
                        left = tmp; // 1
                        right = numerator;
                    }

                // distance = (right - left) / 2
                distance = (right - left) * half;
                (*this) = left + distance;
                // N/D = Q -> QD -N = 0
                residual = (*this) * divisor - numerator;
                if (residual == zero) {
                    this->exponent += exponent_dif;
                    this->positive = positive;
                    return;
                }

                // calculate the result
                // continue the loop while we are still inaccurate (up to max precision)
                while ((residual.abs() > min_boundary_p) && 
                       (distance.exponent >= min_boundary_p.exponent)) {
                    // result too small, try halfway between left and (*this) 
                    if (residual < min_boundary_n) {
                        left = (*this);
                    }
                    // distance is halved
                    distance = half * distance;
                    distance.normalize();

                    // truncate insignificant digits of distance
                    while (distance.size() > maximum_precision + 1) {
                        distance.digits.pop_back();
                    }

                    // iterate (*this)
                    (*this) = left + distance;

                    // truncate insignificant digits of (*this)
                    while ((*this).size() > maximum_precision + 1) {
                        (*this).digits.pop_back();
                    }

                    // recalculate residual  N/D = Q ---> QD - N = residual
                    residual = ((*this) * divisor) - numerator;
                    residual.normalize();
                }
                
                // truncate (*this)
                this->normalize();

                while ((*this).size() > maximum_precision)
                    (*this).digits.pop_back();


                // recalculate residual for the final (*this) value
                exact_number<T> residual_o = ((*this) * divisor) - numerator;

                // note we have to normalize before comparison, because -0.0 != zero ..
                residual_o.normalize();

                if (residual_o != zero) { // then, we are not fully accurate
                    // we try seeing if we can make the residual equal zero by adding/subtracting epsilon
                    exact_number<T> tmp_lower = (*this);
                    tmp_lower.round_down(base);
                    exact_number<T> tmp_upper = (*this);
                    tmp_upper.round_up(base);

                    residual = tmp_lower * divisor - numerator;
                    residual.normalize();

                    if (residual == zero) {
                        (*this) = tmp_lower;

                        if (positive)
                            (*this).positive = true;
                        else
                            (*this).positive = false;

                        (*this).normalize();
                        this->exponent += exponent_dif;
                        return;
                    } 

                    residual = tmp_upper * divisor - numerator;
                    residual.normalize();

                    if (residual == zero) {
                        (*this) = tmp_upper;

                        if (positive)
                            (*this).positive = true;
                        else
                            (*this).positive = false;

                        (*this).normalize();
                        this->exponent += exponent_dif;
                        return;
                    }
                    // at this point, it is impossible to make the residual 0
                } // else old residual == 0

                if (positive)
                    (*this).positive = true;
                else
                    (*this).positive = false;

                this->exponent += exponent_dif;
                (*this).normalize();
            }

            void round_up_abs(T base) {
                int index = digits.size() - 1;
                bool keep_carrying = true;

                while((index > 0) && keep_carrying) { // bring the carry back
                    if(this->digits[index] != base) {
                        ++this->digits[index];
                        keep_carrying = false;
                    } else { // digits[index] == 9, we keep carrying
                        this->digits[index] = 0;
                    }
                    --index;
                }

                if ((index == 0) && keep_carrying) { // i.e., .999 should become 1.000
                    if(this->digits[index] == base) {
                        this->digits[index] = 0;
                        this->push_front(1);
                        ++this->exponent;
                    } else {
                        ++this->digits[index];
                    }
                }
            }

            void round_up(T base) {
                if (positive)
                    this->round_up_abs(base);
                else
                    this->round_down_abs(base);
            }

            void round_down(T base) {
                if (positive)
                    this->round_down_abs(base);
                else
                    this->round_up_abs(base);
            }

            void round_down_abs(T base) {
                int index = digits.size() - 1;
                bool keep_carrying = true;

                while((index > 0) && keep_carrying) { // bring the carry back
                    if(this->digits[index] != 0) {
                        --this->digits[index];
                        keep_carrying = false;
                    } else // digits[index] == 0, we keep carrying
                        this->digits[index] = base;
                    --index;
                }
                // we should be ok at this point because the first number in digits should != 0
                if (index == 0 && keep_carrying)
                    --this->digits[index];
            }

            /**
             * @brief *default constructor*: It constructs a representation of the number zero.
             */
            exact_number<T>() = default;

            /// ctor from vector of digits, integer exponent, and optional bool positive
            exact_number<T>(std::vector<T> vec, int exp, bool pos = true) : digits(vec), exponent(exp), positive(pos) {};

            exact_number<T>(std::vector<T> vec, bool pos = true) : digits(vec), exponent(vec.size()), positive(pos) {};

            /// ctor from any integral type
            /// @TODO: use whichever base.
            // template<typename I, typename std::enable_if_t<std::is_integral<I>::value>>
            // exact_number(I x) {
                // if (x < 0)
                    // positive = false;
                // else
                    // positive = true;
                
                // exponent = 0;
                // while (((x % BASE) != 0) || (x != 0)) {
                    // exponent++;
                    // push_front(std::abs(x%BASE));
                    // x /= BASE;
                // }
            // }
        
            // returns {integer_part, decimal_part, exponent, is_positive}
            constexpr static std::tuple<std::string_view, std::string_view, exponent_t, bool> number_from_string(std::string_view number) {
                std::string_view integer_part;
                std::string_view decimal_part;

                int exponent = 0;
                bool exp_positive = true;
                bool positive = true;

                bool has_exponent = false;
                bool has_decimal = false;
                bool has_sign = false;

                size_t index = 0;

                size_t integer_count = 0;

                size_t decimal_start_index = 0; // pos of first number past '.'
                size_t decimal_count = 0;

                size_t integer_rhs_zeros = 0;
                size_t integer_lhs_zeros = 0;
                size_t decimal_lhs_zeros = 0;
                size_t decimal_rhs_zeros = 0;

                if (number[index] == '-') {
                    positive = false;
                    has_sign = true;
                    index++;
                } else if (number[index] == '+') {
                    // is already positive
                    has_sign = true;
                    index++;
                }

                // first digit must be nonzero.

                for (; index < number.size(); index++) {
                    // we should not have any characters in the input except 'e' and '.', and
                    // '.' can only come before e, and these characters can only occur once

                    // handle '.' and 'e'
                    if (!has_exponent) {
                        if(number[index] == 'e') {
                            has_exponent = true;

                            if (number[index+1] == '-') {
                                exp_positive = false;
                                index++;
                            } else if (number[index+1] == '+') {
                                index++;
                            }
                            continue;

                        } else if (!has_decimal) {
                            if(number[index] == '.') {
                                has_decimal = true;
                                decimal_start_index = index + 1;
                                continue;
                            }
                        } 
                    }

                    // handle other characters, and numbers
                    if (!std::isdigit(number[index])) {
                        // if the first number was 0, it may have been octal
                        if(number[has_sign] == '0') {
                            throw octal_input_not_supported_exception();
                        } else {
                            throw invalid_string_number_exception();
                        }
                    } else { // number[index] is a digit
                        if (has_exponent) {
                            exponent *= 10;
                            exponent += number[index] - '0';
                            if (exponent < 0) {
                                throw exponent_overflow_exception();
                            }
                            continue;

                        } else if (has_decimal) {
                            if (number[index] == '0') {
                                if (decimal_count == 0) {
                                    decimal_lhs_zeros++;
                                    continue;
                                } else {
                                    decimal_rhs_zeros++;
                                    continue;
                                }
                            } else {
                                decimal_count++;
                                decimal_count += decimal_rhs_zeros; 
                                decimal_rhs_zeros = 0;
                                continue;
                            }
                        } else { // we're on the integral part
                            if (number[index] == '0') {
                                if (integer_count == 0) {
                                    integer_lhs_zeros++;
                                    continue;
                                } else {
                                    integer_rhs_zeros++;
                                    continue;
                                }
                            } else {
                                integer_count++;
                                integer_count += integer_rhs_zeros;
                                integer_rhs_zeros = 0;
                                continue;
                            }
                        }
                    }
                }

                if (!exp_positive) {
                    exponent *= -1;
                }

                exponent += integer_count;

                if (integer_count == 0) {
                    decimal_start_index += decimal_lhs_zeros;
                    exponent -= decimal_lhs_zeros;
                } else {
                    exponent += integer_rhs_zeros;
                    integer_count += integer_rhs_zeros;
                    decimal_count += decimal_lhs_zeros;
                }

                integer_part = number.substr(has_sign + integer_lhs_zeros, integer_count);
                decimal_part = number.substr(decimal_start_index, decimal_count);

                return {integer_part, decimal_part, exponent, positive};
            }

            /**
             * Takes a number of the form sign AeB, or A, where A is the desired number in base 10 and 
             * B is the integral exponent, and sign is + or -, and constructs an exact_number
             */
            constexpr explicit exact_number (const std::string& number) {
                auto [integer_part, decimal_part, exponent, positive] = number_from_string((std::string_view)number);

                if (integer_part.empty() && decimal_part.empty()) {
                    digits = {0};
                    exponent = 0;
                    return;
                }
                for (const auto& c : integer_part ) {
                    digits.push_back(c - '0');
                }
                for (const auto& c : decimal_part ) {
                    digits.push_back(c - '0');
                }
            }
            

            /**
             * @brief *Copy constructor:* It constructs a new boost::real::exact_number that is a copy of the
             * other boost::real::exact_number.
             *
             * @param other - The boost::real::exact_number to copy.
             */
            exact_number<T>(const exact_number<T> &other) = default;

            /// TODO: move ctor

            /**
             * @brief Default asignment operator.
             *
             * @param other - The boost::real::exact_number to copy.
             */
            exact_number<T> &operator=(const exact_number<T>& other) = default;

            /**
             * @brief *Lower comparator operator:* It compares the *this boost::real::exact_number with the other
             * boost::real::exact_number to determine if *this is lower than other.
             *
             * @param other - The right side operand boost::real::exact_number to compare with *this.
             * @return a bool that is true if and only if *this is lower than other.
             */
            bool operator<(const exact_number& other) const {
                std::vector<T> zero = {0};
                if (this->digits == zero || this->digits.empty()) {
                    return !(other.digits == zero || !other.positive || other.digits.empty());
                } else {
                    if ((other.digits == zero || other.digits.empty()) && !this->positive)
                        return true;
                }
                if (this->positive != other.positive) {
                    return !this->positive;
                }

                if (this->positive) {
                    if (this->exponent == other.exponent) {
                        return aligned_vectors_is_lower(this->digits, other.digits);
                    }

                    return this->exponent < other.exponent;
                }

                if (this->exponent == other.exponent) {
                    return aligned_vectors_is_lower(other.digits, this->digits);
                }

                return other.exponent < this->exponent;
            }

            /**
             * @brief *Greater comparator operator:* It compares the *this boost::real::exact_number with the other
             * boost::real::exact_number to determine if *this is greater than other.
             *
             * @param other - The right side operand boost::real::exact_number to compare with *this.
             * @return a bool that is true if and only if *this is greater than other.
             */
            bool operator>(const exact_number& other) const {
                std::vector<T> zero = {0};
                if (this->digits == zero || this->digits.empty()) {
                    return !(other.digits == zero || other.positive || other.digits.empty());
                } else {
                    if ((other.digits == zero) && this->positive)
                        return true;
                } 
                if (this->positive != other.positive) {
                    return this->positive;
                }

                if (this->positive) {
                    if (this->exponent == other.exponent) {
                        return aligned_vectors_is_lower(other.digits, this->digits);
                    }

                    return this->exponent > other.exponent;
                }

                if (this->exponent == other.exponent) {
                    return aligned_vectors_is_lower(this->digits, other.digits);
                }

                return other.exponent > this->exponent;
            }

            bool operator>=(const exact_number& other) const {
                return (!((*this) < other));
            }

            bool operator<=(const exact_number& other) const {
                return (!((*this) > other));
            }

            /**
             * @brief *Equality comparator operator:* It compares the *this boost::real::exact_number with the other
             * boost::real::exact_number to determine if *this and other are equals or not.
             *
             * @param other - The right side operand boost::real::exact_number to compare with *this.
             * @return a bool that is true if and only if *this is equal to other.
             */
            bool operator==(const exact_number<T>& other) const {
                return !(*this < other || other < *this);
            }

            bool operator!=(const exact_number<T>& other) const {
                return !(*this == other);
            }

            exact_number<T> abs() {
                exact_number<T> result = (*this);
                result.positive = true;
                return result;
            }

            exact_number<T> operator+(exact_number<T> other) {
                exact_number<T> result;

                if (this->positive == other.positive) {
                        result = *this;
                        result.add_vector(other);
                } else if (other.abs() < this->abs()) {
                        result = *this;
                        result.subtract_vector(other);
                        result.positive = this->positive;
                } else {
                    result = other;
                    result.subtract_vector(*this);
                    result.positive = !this->positive;
                }
                return result;
            }

            void operator+=(exact_number<T> &other) {
                *this = *this + other;
            }

            //Add exact numbers assuming base 10
            exact_number<T> base10_add (exact_number<T> other) {
                exact_number<T> result;

                if (positive == other.positive) {
                        result = *this;
                        result.add_vector(other, 9);
                        result.positive = this->positive;
                } else if (other.abs() < (*this).abs()) {
                        result = *this;
                        result.subtract_vector(other, 9);
                        result.positive = this->positive;
                } else {
                    result = other;
                    result.subtract_vector((*this), 9);
                    result.positive = !this->positive;
                }
                return result;
            }

            exact_number<T> operator-(exact_number<T> other) {
                exact_number<T> result;

                if (this->positive != other.positive) {
                    result = *this;
                    result.add_vector(other);
                    result.positive = this->positive;
                } else {
                    if (other.abs() < this->abs()) {
                        result = *this;
                        result.subtract_vector(other);
                        result.positive = this->positive;
                    } else {
                        result = other;
                        result.subtract_vector(*this);
                        result.positive = !this->positive;
                    }
                }

                return result;
            }

            void operator-=(exact_number<T> &other) {
                *this = *this - other;
            }

            //Subtract exact numbers assuming base 10
            exact_number<T> base10_subtract(exact_number<T> other) {
                exact_number<T> result;

                if (this->positive != other.positive) {
                    result = *this;
                    result.add_vector(other, 9);
                    result.positive = this->positive;
                } else {
                    if (other.abs() < (*this).abs()) {
                        result = *this;
                        result.subtract_vector(other, 9);
                        result.positive = this->positive;
                    } else {
                        result = other;
                        result.subtract_vector(*this, 9);
                        result.positive = !this->positive;
                    }
                }

                return result;
            }

            exact_number<T> operator*(exact_number<T> other) {
                exact_number<T> result = *this;
                result.multiply_vector(other);
                result.positive = (this->positive == other.positive);
                return result;
            }

            void operator*=(exact_number<T> &other) {
                *this = *this * other;
            }

            //Multiply exact numbers assuming base 10
            exact_number<T> base10_mult(exact_number<T> other) {
                exact_number<T> result = *this;
                result.multiply_vector(other, 10);
                result.positive = (this->positive == other.positive);
                return result;
            }

            /**
             * @brief Generates a string representation of the boost::real::exact_number.
             *
             * @return a string that represents the state of the boost::real::exact_number
             */
            std::string as_string() const {
                std::string result = "";   
                exact_number<T> tmp;         

                // If the number is too large, scientific notation is used to print it.
                /* @TODO add back later
                if ((this->exponent < -10) || (this->exponent > (int)this->digits.size() + 10)) {
                    result += "0|.";
                    for (const auto& d: this->digits) {
                        result += std::to_string(d);
                        result += "|";
                    }
                    result += "e" + std::to_string(this->exponent);
                    return result;
                }
                */

                if (this->exponent <= 0) {
                    result += ".";

                    for (int i = this->exponent; i < (int) this->digits.size(); ++i) {
                        if (i < 0) {
                            result += "0";
                            result += " ";
                        } else {
                            result += std::to_string(this->digits[i]);
                            result += " ";
                        }
                    }
                } else {
                    int digit_amount = std::max(this->exponent, (int) this->digits.size());

                    for (int i = 0; i < digit_amount; ++i) {

                        if (i == this->exponent) {
                            result += ".";
                        }

                        if (i < (int) this->digits.size()) {
                            result += std::to_string(this->digits[i]);
                            result += " ";
                        } else {
                            result += "0";
                            result += " ";
                        }
                    }

                    if (result.back() == '.') {
                        result.pop_back();
                    }
                }

                //Use "return result" here for actual internal representation output for debugging

                //Form new string below in base 10.
                std::vector<T> new_result = {0};
                std::size_t dot_pos = result.find('.');
                std::string integer_part;
                std::string decimal_part;
                if (dot_pos == std::string::npos) {
                    integer_part = result;
                    decimal_part = "";
                } else {
                    integer_part = result.substr(0, dot_pos);
                    decimal_part = result.substr(dot_pos + 1);
                }
                std::stringstream ss1(integer_part);
                std::istream_iterator<std::string> begin1(ss1);
                std::istream_iterator<std::string> end1;
                std::vector<std::string> integer(begin1, end1);
                std::stringstream ss2(decimal_part);
                std::istream_iterator<std::string> begin2(ss2);
                std::istream_iterator<std::string> end2;
                std::vector<std::string> decimal(begin2, end2);
                std::reverse (decimal.begin(), decimal.end()); 

                //integer and decimal are string vectors with the "digits" in diff base
                T b = (std::numeric_limits<T>::max() /4)*2;
                std::vector<T> base;
                while (b!=0) {
                    base.push_back(b%10);
                    b /=10;
                }
                std::reverse(base.begin(), base.end());
                while(!integer.empty()) {
                    std::vector<T> temp;
                    std::string num = integer.back();
                    integer.pop_back();
                    for (auto j : num) {
                        temp.push_back(j - '0');
                    }
                    tmp = (exact_number<T>(new_result).base10_add(exact_number<T>(temp)));
                    new_result = tmp.digits;
                    while (tmp.exponent - (int)tmp.digits.size() > 0) {
                        new_result.push_back(0);
                        tmp.exponent--;
                    }
                    for (size_t i = 0; i < integer.size(); ++i) {
                        std::vector<T> temp;
                        std::string tempstr = integer[i];
                        for (size_t j = 0; j < tempstr.length(); ++j) {
                            temp.push_back(tempstr[j] - '0'); 
                        }
                        tmp = (exact_number<T>(temp).base10_mult(exact_number<T>(base)));
                        temp = tmp.digits;
                        while (tmp.exponent - (int)tmp.digits.size() > 0) {
                            temp.push_back(0);
                            tmp.exponent--;
                        }
                        size_t idx = 0;
                        while(idx < temp.size() && temp[idx]==0) 
                            ++idx;
                        temp.erase(temp.begin(), temp.begin() + idx);
                        std::stringstream ss;
                        std::copy( temp.begin(), temp.end(), std::ostream_iterator<T>(ss, ""));
                        std::string str = ss.str();
                        integer[i] = str;
                    }
                }

                std::stringstream ss;
                std::copy( new_result.begin(), new_result.end(), std::ostream_iterator<T>(ss, ""));
                std::string res_decimal = ss.str();
                std::vector<T> new_base = base;
                std::vector<std::vector<T>> powers = {base};
                for (size_t i = 0; i<decimal.size(); ++i) {
                    tmp = (exact_number<T>(new_base).base10_mult(exact_number<T>(base)));
                    new_base = tmp.digits;
                    while (tmp.exponent - (int)tmp.digits.size() > 0) {
                        new_base.push_back(0);
                        tmp.exponent--;
                    }
                    size_t idx = 0;
                    while(idx < new_base.size() && new_base[idx]==0) 
                        ++idx;
                    new_base.erase(new_base.begin(), new_base.begin() + idx);
                    powers.push_back(new_base);
                }
                size_t precision = powers.back().size() + 1;
                std::string zeroes = "";
                for (size_t i = 0; i<precision; ++i)
                    zeroes = zeroes + "0";
                std::vector<T> fraction = {0};
                auto pwr = powers.cbegin();
                while(!decimal.empty()) {
                    std::string tempstr = decimal.back();
                    decimal.pop_back();
                    tempstr = tempstr + zeroes;
                    std::vector<T> temp;
                    for (size_t j = 0; j<tempstr.length(); ++j) {
                        temp.push_back(tempstr[j] - '0'); 
                    }
                    std::vector<T> k = *pwr++;
                    std::vector<T> q;
                    tmp.long_divide_vectors(temp, k, q);
                    tmp = (exact_number<T>(fraction).base10_add(exact_number<T>(q)));
                    fraction = tmp.digits;
                    while (tmp.exponent - (int)tmp.digits.size() > 0) {
                        fraction.push_back(0);
                        tmp.exponent--;
                    }
                }
                std::stringstream sslast;
                while (!fraction.empty() && fraction.back() == 0) {
                    fraction.pop_back();
                    --precision;
                }
                std::copy( fraction.begin(), fraction.end(), std::ostream_iterator<T>(sslast, ""));
                std::string fractionstr = sslast.str();
                while (fractionstr.length() < precision)
                    fractionstr = "0" + fractionstr;
                
                if (fraction.empty())
                    return (positive ? "" : "-") + res_decimal;
                else
                    return (positive ? "" : "-") + res_decimal + "." + fractionstr;
            }

            /**
             * @brief Swaps the boost::real::exact_number value with the value of the other boost::real::exact_number.
             * This operation is a more preformant form of swapping to boost::real::boundaries.
             *
             * @param other - The boost::real::exact_number to swap with *this.
             */
            void swap(exact_number<T> &other) {
                this->digits.swap(other.digits);
                std::swap(this->exponent, other.exponent);
                std::swap(this->positive, other.positive);
            }

            /**
             * @brief add the digit parameter as a new digit of the boost::real::exact_number. The digit
             * is added in the right side of the number.
             *
             * @param digit - The new digit to add.
             */
            void push_back(T digit) {
                this->digits.push_back(digit);
            }

            /**
             * @brief add the digit parameter as a new digit of the boost::real::exact_number. The digit
             * is added in the left side of the number.
             *
             * @param digit - The new digit to add.
             */
            void push_front(T digit) {
                this->digits.insert(this->digits.cbegin(), digit);
            }

            /**
             * @brief Removes extra zeros at the sides to convert the number representation into a
             * normalized representation.
             */
            void normalize() {
                while (this->digits.size() > 1 && this->digits.front() == 0) {
                    this->digits.erase(this->digits.cbegin());
                    this->exponent--;
                }

                while (this->digits.size() > 1 && this->digits.back() == 0) {
                    this->digits.pop_back();
                }

                // Zero could have many representation, and the normalized is the next one.
                if (this->digits.size() == 1 && this->digits.front() == 0) {
                    this->exponent = 0;
                    this->positive = true;
                }
            }

            /**
             * @brief Removes extra zeros at the left side to convert the number representation
             * into a semi normalized representation.
             */
            void normalize_left() {
                while (this->digits.size() > 1 && this->digits.front() == 0) {
                    this->digits.erase(this->digits.cbegin());
                    this->exponent--;
                }
            }

            /**
             * @brief ir clears the number digits.
             */
            void clear() {
                this->digits.clear();
            }

            /**
             * @brief Returns the n-th digit of the boost::real::exact_number.
             *
             * @param n - an int number indicating the index of the requested digit.
             * @return an integer with the value of the number n-th digit.
             */
            T &operator[](int n) {
                return this->digits[n];
            }

            /**
             * @brief It returns the number of digits of the boost::real::exact_number
             *
             * @return an unsigned long representing the number of digits of the boost::real::exact_number
             */
            unsigned long size() {
                return this->digits.size();
            }

            /// returns an exact_number that has the precision given
            exact_number<T> up_to(size_t precision, bool upper) {
                T base = (std::numeric_limits<T>::max() /4)*2 - 1;
                if (precision >= digits.size())
                    return *this;

                exact_number<T> ret = *this;
                ret.digits = std::vector<T>(digits.begin(), digits.begin() + precision);

                bool round = (precision < digits.size());
                if (round) {
                    if(upper) {
                        ret.round_up(base);
                    } else {
                        ret.round_down(base);
                    }
                }

                return ret;
            }

            bool is_integral() { 
                if (exponent < 0) {
                    return false;
                } else {
                    // note, at this point, exponent >= 0.
                    return digits.size() <= (size_t) exponent;
                }
            }
        };

        template<> inline int exact_number<int>::mulmod (int a, int b, int c)
        {
            return ((long long)a * (long long)b )%c;
        }

        template<> inline int exact_number<int>::mult_div(int a, int b, int c)
        {
            return ((long long)a * (long long)b)/c;
        }
    }
}

#endif // BOOST_REAL_EXACT_NUMBER

#ifndef BOOST_REAL_CONVENIENCE_HPP
#define BOOST_REAL_CONVENIENCE_HPP

#include <vector>
#include <iostream>
#include <real/real_exception.hpp>
#include <real/interval.hpp>
#include <real/exact_number.hpp> //for some methods, that are declared in this file
#include <real/real_exception.hpp>
#include <real/details.hpp>


/* APPEND DIGIT IN NEW BASE
 * @brief: to append digit of different base in a number of different base.
 * @param: number: number in which digit is going to be appended.
 * @param: num_base: the base of number.
 * @param: digit: the digit which is to be appended in the number.
 * @digit_base: the base of the digit which is going to appended.
 * @author: Vikram Singh Chundawat
 **/

template<typename T1, typename T2>
void append_digits(std::vector<T1> &number, T1 num_base, T2 digit, T2 digit_base)
{
    /*
     * Warning: this function will misbehave if num_base > numeric_limits<T1>::max()/2 or digit_base > numeric_limits<T2>::max()/2
     * , or num_base < digit_base.
     * This function was is built to help digit by digit base conversions for real::algorithm type of numbers.
     * The internal base representation of all number in real for any type T is not greater numeric_limits<T>::max()/2, so it should work perfectly fine
     * for the type of conversions it is mainly build, but may misbehave in case larger bases.
     */
    if(number.size() == 0) number.push_back(0);
    size_t n = number.size();

    // to append a digit of base = base_digit, we will first multiply number by digit_base
    // and then we will add digit in that number
    T1 carry = 0; // carry we got by previous multiplication

    // multiplying the number by digit_base
    T2 tmp_digit_base; // we will use this variable for multiplication
    T1 tmp_carry; // to store current carry, getting created by multiplication
    T1 result; // to store value of result

    for(T1 &digit: boost::real::detail::reverse(number))
    {
    	tmp_digit_base = digit_base;
    	tmp_carry = 0;
    	result = 0;
    	while(tmp_digit_base != 0)
    	{
    	    // tmp_digit_base is a even number, multiply it by 2 and divide tmp_digit_base by 2
    	    if(tmp_digit_base%2 == 1)
    	    {
        		result = result + digit;
        		// if result becomes greater than num_base
        		if(result >= num_base)
        		{
        		    ++tmp_carry;
        		    result -= num_base;
        		}
        		tmp_digit_base -= 1;
    	    }
    	    // else multiply number[i] with 2
    	    else
    	    {
                
        	    digit = digit*2;
                tmp_digit_base = tmp_digit_base/2;
        	    if(digit >= num_base) 
        	    {
            		tmp_carry += tmp_digit_base;
            		digit -= num_base;
        	    }
        	    
        	    // divide by 2
        	    
    	    }

    	}

    	result += carry;
    	if(result >= num_base)
    	{
    	    ++tmp_carry;
    	    result -= num_base;
    	}
	   // done all required calculation, now assigning all required values
    	digit = result;
    	carry = tmp_carry;
    }

    // if carry is not zero, add it to begining of vector
    if(carry != 0)
    {
	   number.insert(number.begin(),carry);
    }

    // completed multiplication, now we will add the digit to number
    n = number.size();
    number[--n] += digit;
    carry = number[n] / num_base;
    number[n] %= num_base;
    while(carry != 0 && n != 0)
    {
    	number[--n] += carry;
    	carry = number[n] / num_base;
    	number[n] %= num_base;
    }

    if(carry != 0) number.insert(number.begin(), carry);
    return;
}




/*
 * Specializing the above function to have a better performance in case of integers
 * We are using some ineffiecient methods for multiplication to avoid overflows
 * but in case of integers, the values can be stores in unsigned long long to avoid overflows
 * and we can replace that multiplication system with faster one,
 * so a new specilized function for integers is created.
 */
template<>
void append_digits(std::vector<int> &number, int num_base, int digit, int digit_base)
{
    /*
     * Warning: this function will misbehave if num_base > numeric_limits<T1>::max()/2 or digit_base > numeric_limits<T2>::max()/2
     * , or num_base < digit_base.
     * This function was is built to help digit by digit base conversions for real::algorithm type of numbers.
     * The internal base representation of all number in real for any type T is not greater numeric_limits<T>::max()/2, so it should work perfectly fine
     * for the type of conversions it is mainly build, but may misbehave in case of larger bases.
     */
    if(number.size() == 0) number.push_back(0);
    size_t n = number.size();

    // to append a digit of base = base_digit, we will first multiply number by digit_base
    // and then we will add digit in that number
    int carry = 0; // carry we got by previous multiplication

    // multiplying the number by digit_base
    int tmp_carry; // to store current carry, getting created by multiplication
    unsigned long long result; // to store value of result

    for(size_t i = n-1; i >= 0; --i)
    {
		tmp_carry = 0;
		result = number[i]*digit_base;
		if(result >= num_base) 
		{
		    tmp_carry += result/num_base;
		    result %= num_base;
		}
		result += carry;
		if(result >= num_base)
		{
	    	tmp_carry += result/num_base;
	    	result %= num_base;
		}
		// done all required calculation, now assigning all required values
		number[i] = result;
		carry = tmp_carry;
		if(i == 0) break;
    }

    // if carry is not zero, add it to begining of vector
    if(carry != 0)
    {
		number.insert(number.begin(),carry);
    }


    // completed multiplication, now we will add the digit to number
    n = number.size();
    number[--n] += digit;
    carry = number[n] / num_base;
    number[n] %= num_base;
    while(carry != 0 && n != 0)
    {
    	number[--n] += carry;
    	carry = number[n] / num_base;
    	number[n] %= num_base;
    }

    if(carry!=0) number.insert(number.begin(), carry);

    return;
}


/* APPEND MULTIPLE DIGITS IN NEW BASE
 * @brief: to add multiple digits of different base in a number.
 * @param: number: the number in which digits are going to be appended.
 * @param: num_base: base in which number is store
 * @digits: vector containing multiple digits, which needs to be appended in number.
 * @digit_base: The base in which digits are stored.
 * @author: Vikram Singh Chundawat.
 **/


/*
 * Now creating a function to add multiple digits, it is a simple exptension of above function.
 * This function can also be used for a complete base coversion.
 * Just give a empty number in place of number and give whole number in digits, and you will
 * get whole conversion in number.
 */
 
template<typename T1, typename T2>
void append_digits(std::vector<T1> &number, T1 num_base, std::vector<T2> &digits, T2 digit_base)
{
    for(auto &digit: digits){
        add_digits(number, num_base, digit, digit_base); 
    }
    return ;
}


/*
 *  MULTIPLY TWO NUMBERS STORED IN VECTOR
 * @brief: method to multiply two vectors
 * @param: a: first number, vector of digits(no reverse order)
 * @param: b: second number, vector of digits(no reverse order)
 * @param: base: the base in which numbers are stored
 * @author: Vikram Singh Chundawat
 **/
// Algorithm to multiply two vectors.
template<typename T>
std::vector<T> multiply(std::vector<T> &a, std::vector<T> &b, T base = (std::numeric_limits<T>::max() / 4) * 2 -1)
{
    std::vector<T> temp;
    size_t new_size = a.size() + b.size();
    temp.assign(new_size, 0);
    boost::real::exact_number<T> op;

    // Below two indexes are used to find positions
    // in result.
    size_t i_n1 = (int) temp.size() - 1;
    // Go from right to left in lhs
    for (size_t i = a.size()-1; true; --i) {
        T carry = 0;
        // To shift position to left after every
        // multiplication of a digit in rhs
        size_t i_n2 = 0;

        // Go from right to left in rhs
        //checking is done at the end of loop, size_t can not be zero, so we can not check for negative values of size_t
        for (size_t j = b.size() - 1; true; --j) {

            // Multiply current digit of second number with current digit of first number
            // and add result to previously stored result at current position.
            T rem = op.mulmod(a[i], b[j], base);
            T rem_s;
            T q = op.mult_div(a[i], b[j], base);
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

            if(j == 0) break;
        }

        // store carry in next cell
        if (carry > 0) {
            temp[i_n1 - i_n2] += carry;
        }

        // To shift position to left after every
        // multiplication of a digit in lhs.
        i_n1--;

        if(i == 0) break;
    }

    typename std::vector<T> :: iterator itr = temp.begin();
    while((*itr) == 0) itr++;
    // if initial element was zero, then we need to delete all initial zeroes
    if(temp[0] == 0)
    {
        //itr--;
        temp.erase(temp.begin(), itr);
    }
    if(temp.size() == 0) temp.push_back(0);

                
    return temp;
}       
    
#endif //BOOST_REAL_CONVENIENCE_HPP
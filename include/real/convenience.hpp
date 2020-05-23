#include<vector>
#include<iostream>



template<typename T1, typename T2>
void add_digits(std::vector<T1> &number, T1 num_base, T2 digit, T2 digit_base)
{
    /*
     * Warning: this function will misbehave if num_base > numeric_limits<T1>::max()/2 or digit_base > numeric_limits<T2>::max()/2
     * , or num_base < digit_base.
     * This function was is built to help digit by digit base conversions for real::algorithm type of numbers.
     * The internal base representation of all number in real for any type T is not greater numeric_limits<T>::max()/2, so it should work perfectly fine
     * for the type of conversions it is mainly build, but may misbehave in case larger bases.
     */
    if(number.size()==0) number.push_back(0);
    size_t n = number.size();

    // to append a digit of base = base_digit, we will first multiply number by digit_base
    // and then we will add digit in that number
    T1 carry = 0; // carry we got by previous multiplication

    // multiplying the number by digit_base
    T2 tmp_digit_base; // we will use this variable for multiplication
    T1 tmp_carry; // to store current carry, getting created by multiplication
    T1 result; // to store value of result

    for(size_t i = n-1; i>=0; --i)
    {
    	tmp_digit_base = digit_base;
    	tmp_carry = 0;
    	result = 0;
    	while(tmp_digit_base!=0)
    	{
    	    // tmp_digit_base is a even number, multiply it by 2 and divide tmp_digit_base by 2
    	    if(tmp_digit_base%2==1)
    	    {
    		result = result + number[i];
    		// if result becomes greater than num_base
    		if(result >= num_base)
    		{
    		    ++tmp_carry;
    		    result -= num_base;
    		}
    		tmp_digit_base-=1;
    	    }
    	    // else multiply number[i] with 2
    	    else
    	    {
    	    number[i] = number[i]*2;
    	    if(number[i] >= num_base) 
    	    {
    		++tmp_carry;
    		result -= num_base;
    	    }
    	    
    	    // divide by 2
    	    tmp_digit_base = tmp_digit_base/2;
    	    }
    	}

    	result += carry;
    	if(result >= num_base)
    	{
    	    ++tmp_carry;
    	    result -= num_base;
    	}
	   // done all required calculation, now assigning all required values
    	number[i] = result;
    	carry = tmp_carry;
    	if(i==0) break;
    }

    // if carry is not zero, add it to begining of vector
    if(carry!=0)
    {
	   number.insert(number.begin(),carry);
    }

    // completed multiplication, now we will add the digit to number
    n = number.size();
    number[--n] += digit;
    carry = number[n]/num_base;
    number[n] %= num_base;
    while(carry!=0 && n!=0)
    {
    	number[--n] += carry;
    	carry = number[n]/num_base;
    	number[n] %= num_base;
    }

    if(carry!=0) number.insert(number.begin(), carry);
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
void add_digits(std::vector<int> &number, int num_base, int digit, int digit_base)
{
    /*
     * Warning: this function will misbehave if num_base > numeric_limits<T1>::max()/2 or digit_base > numeric_limits<T2>::max()/2
     * , or num_base < digit_base.
     * This function was is built to help digit by digit base conversions for real::algorithm type of numbers.
     * The internal base representation of all number in real for any type T is not greater numeric_limits<T>::max()/2, so it should work perfectly fine
     * for the type of conversions it is mainly build, but may misbehave in case of larger bases.
     */
    if(number.size()==0) number.push_back(0);
    size_t n = number.size();

    // to append a digit of base = base_digit, we will first multiply number by digit_base
    // and then we will add digit in that number
    int carry = 0; // carry we got by previous multiplication

    // multiplying the number by digit_base
    int tmp_carry; // to store current carry, getting created by multiplication
    unsigned long long result; // to store value of result

    for(size_t i = n-1; i>=0; --i)
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
		if(i==0) break;
    }

    // if carry is not zero, add it to begining of vector
    if(carry!=0)
    {
		number.insert(number.begin(),carry);
    }


    // completed multiplication, now we will add the digit to number
    n = number.size();
    number[--n] += digit;
    carry = number[n]/num_base;
    number[n] %= num_base;
    while(carry!=0 && n!=0)
    {
    	number[--n] += carry;
    	carry = number[n]/num_base;
    	number[n] %= num_base;
    }

    if(carry!=0) number.insert(number.begin(), carry);

    return;
}



/*
 * Now creating a function to add multiple digits, it is a simple exptension of above function.
 * This function can also be used for a complete base coversion.
 * Just give a empty number in place of number and give whole number in digits, and you will
 * get whole conversion in number.
 */
 
template<typename T1, typename T2>
void add_digits(std::vector<T1> &number, T1 num_base, std::vector<T2> &digits, T2 digit_base)
{
    size_t n = digits.size();
    for(size_t i=0;i<n;i++)
    {
	add_digits(number, num_base, digits[i], digit_base);
    }
    return ;
}



#include <catch2/catch.hpp>
#include <real/real_algorithm.hpp>
#include <test_helpers.hpp>
#include<vector>
#include<iostream>
#include<cassert>
#include<limits>
#include <real/convenience.hpp>
#include<real/integer_number.hpp>
using namespace std;

TEST_CASE("convenience function") {
    SECTION("appending digit") {
        vector<int> num_int = {1,2,3,4};
        add_digits(num_int, 10, 0, 2);
        vector<int> result_int = {2,4,6,8};
        assert(num_int==result_int);

        num_int = {1,2,3,4};
        add_digits(num_int, 10, 1, 2);
        result_int = {2,4,6,9};
        assert(num_int==result_int);

        num_int = {1,2,3,4};
        add_digits(num_int, 10, 1, 10);
        result_int = {1,2,3,4,1};
        assert(num_int==result_int);

        vector<long> num_long;
        vector<long> result_long;

        num_long = {(numeric_limits<long>::max()/4)-1}; // check this one
        add_digits(num_long, (numeric_limits<long>::max()/4)*2, 4, 10);
        result_long = {4,4611686018427387896};
        assert(num_long==result_long);


        num_int = {11, 53451888}; // 1234567890 in decimal base , [11, 53451888] in base 107374182
        //adding 8 in decimal base
        add_digits(num_int, 107374182, 9, 10);
        result_int = {114, 105022161}; // 12345678909 in decimal base, and "result" in base 107374182
        assert(num_int==result_int);


        // adding 7 in prev num_int
        add_digits(num_int, 107374182, 7 , 10);
        result_int = {1149, 83853979};
        assert(num_int==result_int);

        num_long = {136, 53900345}; // number 123456789097 in decimal base, converted to base 907374182
        add_digits(num_long, (long)907374182, 5, 10);
        result_long = {1360, 539003455}; // number 1234567890975 in decimal base
        assert(num_long==result_long);
    }
}

TEMPLATE_TEST_CASE("VECTOR MULTIPLICATION TEST multiply()","[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
    using integer = boost::real::integer_number<TestType>;
    SECTION("TESTING VECTOR MULTIPLICATION"){
        vector<TestType> a,b,c,d;
        TestType base = integer().BASE;
        a = integer("1111111111111111111111").digits;
        b = integer("2").digits;
        c = integer("2222222222222222222222").digits;
        d = multiply(a,b,base);
        CHECK(c==d);

        b = integer("0").digits;
        d = multiply(a,b,base);
        CHECK(b==d);
    }
}

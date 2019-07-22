#include <catch2/catch.hpp>

#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("Operator / boost::real::const_precision_iterator") { // assumes max precision is 10.

        SECTION("144/12") {             
        boost::real::real a("144"); // [100, 200]
        boost::real::real b("12");  // [10 , 20]
        boost::real::real result = a/b; // [100, 200] / [10, 20] = [100/20, 200/10] = [5, 20]

            auto result_it = result.get_real_itr().cbegin();

            boost::real::interval expected_interval({});
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 2;
            expected_interval.lower_bound.digits = {5};
            expected_interval.upper_bound.digits = {2};
            CHECK(expected_interval == result_it.get_interval());

            ++result_it; // [140, 150] / [12, 12] = [140/12, 150/12] = [11.666...6, 12.5]
            expected_interval.lower_bound.exponent = 2;
            expected_interval.upper_bound.exponent = 2;
            expected_interval.lower_bound.digits = {1,1,6,6,6,6,6,6,6,6};
            expected_interval.upper_bound.digits = {1,2,5};
            CHECK(expected_interval == result_it.get_interval());

            ++result_it; // [144, 144] / [12, 12] = 12
            expected_interval.lower_bound.exponent = 2;
            expected_interval.upper_bound.exponent = 2;
            expected_interval.lower_bound.digits = {1,2};
            expected_interval.upper_bound.digits = {1,2};
            CHECK(expected_interval == result_it.get_interval());
        }

        SECTION("12/144") { // currently doesn't work for intermediate steps. We can fix it later. it gets close 
                            // to expected, but not exact
            boost::real::real a("144"); // [100, 200]
            boost::real::real b("12");  // [10 , 20]
            boost::real::real result = b/a; 
            // 12 / 144 
            // [10, 20] / [100, 200] = [10/200, 20/100] = [.05, .2]
            auto result_it = result.get_real_itr().cbegin();

            boost::real::interval expected_interval({});
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = -1;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {5};
            expected_interval.upper_bound.digits = {2};
            CHECK(expected_interval == result_it.get_interval()); 

            result_it = result.get_real_itr().cend();
            // [12, 12] / [144, 144] = [.08333...3, .0833...4]
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = -1;
            expected_interval.upper_bound.exponent = -1;
            expected_interval.lower_bound.digits = {8,3,3,3,3,3,3,3,3,3};
            expected_interval.upper_bound.digits = {8,3,3,3,3,3,3,3,3,4};
            CHECK(expected_interval == result_it.get_interval());
        }

        SECTION("1/3") {             
        boost::real::real a("1"); // [1, 1]
        boost::real::real b("3");  // [3, 3]
        boost::real::real result = a/b; // [1,1] / [3,3]

            auto result_it = result.get_real_itr().cbegin(); // same as .cend(), in this case

            boost::real::interval expected_interval({});
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {3,3,3,3,3,3,3,3,3,3};
            expected_interval.upper_bound.digits = {3,3,3,3,3,3,3,3,3,4};
            CHECK(expected_interval == result_it.get_interval());
        }

        SECTION("-1/3") {             
            boost::real::real a("-1"); // [1, 1]
            boost::real::real b("3");  // [3, 3]
            boost::real::real result = a/b; // [1,1] / [3,3]

                auto result_it = result.get_real_itr().cbegin(); // same as .cend(), in this case

                boost::real::interval expected_interval({});
                expected_interval.lower_bound.positive = false;
                expected_interval.upper_bound.positive = false;
                expected_interval.lower_bound.exponent = 0;
                expected_interval.upper_bound.exponent = 0;
                expected_interval.lower_bound.digits = {3,3,3,3,3,3,3,3,3,4};
                expected_interval.upper_bound.digits = {3,3,3,3,3,3,3,3,3,3};
                CHECK(expected_interval == result_it.get_interval());
            }

        SECTION("-15/10") {             
        boost::real::real a("-15"); // [-1, -2]
        boost::real::real b("10");  // [1, 2]
        boost::real::real result = a/b; // [-1,-2] / [1,2] -> [-2, -1]

            auto result_it = result.get_real_itr().cbegin();

            boost::real::interval expected_interval({});
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {1};
            CHECK(expected_interval == result_it.get_interval());

            ++result_it;
            expected_interval.lower_bound.digits = {1,5};
            expected_interval.upper_bound.digits = {1,5};
            CHECK(expected_interval == result_it.get_interval());
        }

        SECTION("1/2") {             
        boost::real::real a("1"); // [1, 1]
        boost::real::real b("2");  // [3, 3]
        boost::real::real result = a/b; // [1,1] / [3,3]

            auto result_it = result.get_real_itr().cbegin(); // same as .cend(), in this case

            boost::real::interval expected_interval({});
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {5};
            expected_interval.upper_bound.digits = {5};
            CHECK(expected_interval == result_it.get_interval());
        }
}
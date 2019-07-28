#include <catch2/catch.hpp>

#include <real/real.hpp>
#include <test_helpers.hpp>

using real=boost::real::real<>;

TEST_CASE("Operator / boost::real::const_precision_iterator") { // assumes max precision is 10.

        boost::real::exact_number length;
        
        SECTION("13251306276306304250236049144144144492977320/38409583409583490580394345345345346356456") {             
        real a("13251306276306304250236049144144144492977320");
        real b("38409583409583490580394345345345346356456");
        real result = a/b; // [100, 200] / [10, 20] = [100/20, 200/10] = [5, 20]

            auto result_it = result.get_real_itr().cbegin();

            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            CHECK(result_it.get_interval().lower_bound == result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().lower_bound.as_string() == "345");
        }

        SECTION("12/144") { 
            real a("144"); // [100, 200]
            real b("12");  // [10 , 20]
            real result = b/a; 
            // 12 / 144 
            // [10, 20] / [100, 200] = [10/200, 20/100] = [.05, .2]
            auto result_it = result.get_real_itr().cbegin();

            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;
        }

        SECTION("1/3") {             
        real a("1"); // [1, 1]
        real b("3");  // [3, 3]
        real result = a/b; // [1,1] / [3,3]

            auto result_it = result.get_real_itr().cbegin(); // same as .cend(), in this case

            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;
        }

        SECTION("-1/3") {             
            real a("-1"); // [1, 1]
            real b("3");  // [3, 3]
            real result = a/b; // [1,1] / [3,3]

                auto result_it = result.get_real_itr().cbegin(); // same as .cend(), in this case

                length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;
                CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
                CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
                length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

                ++result_it;
                CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
                CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
                length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

                ++result_it;
                CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
                CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
                length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;
            }

        SECTION("-13251306276306304250236049144144144492977320/38409583409583490580394345345345346356456") {             
        real a("-13251306276306304250236049144144144492977320"); // [-1, -2]
        real b("38409583409583490580394345345345346356456");  // [1, 2]
        real result = a/b; // [-1,-2] / [1,2] -> [-2, -1]

            auto result_it = result.get_real_itr().cbegin();

            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            ++result_it;
            CHECK(result_it.get_interval().lower_bound <= result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound - result_it.get_interval().lower_bound <= length);
            length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;

            CHECK(result_it.get_interval().lower_bound == result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().lower_bound.as_string() == "-345");
        }

        SECTION("1/2") {
            real a("1"); // [1, 1]
            real b("2");  // [3, 3]
            real result = a/b; // [1,1] / [3,3]

            auto result_it = result.get_real_itr().cbegin(); // same as .cend(), in this case

            CHECK(result_it.get_interval().lower_bound == result_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().lower_bound.as_string() == "0.5");
        }
}
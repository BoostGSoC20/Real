#include <catch2/catch.hpp>
#include <map>

#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("Operators + + boost::real::const_precision_iterator") {

    boost::real::interval expected_interval({});

    SECTION("With carry") {

        // Explicit numbers
        boost::real::real a("1.19");
        boost::real::real b("1.19");
        boost::real::real c("1.19");

        SECTION("(a + b) + c") {
            boost::real::real result = (a + b) + c;

            auto result_it = result.get_real_itr().cbegin();

            // ([1, 2] + [1, 2]) + [1, 2]
            // [2, 4] + [1, 2]
            // [3, 6]
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {6};
            CHECK(expected_interval == result_it.get_interval());

            // ([1.1, 1.2] + [1.1, 1.2]) + [1.1, 1.2]
            // [2.2, 2.4] + [1.1, 1.2]
            // [3.3, 3.6]
            ++result_it;
            expected_interval.lower_bound.digits = {3,3};
            expected_interval.upper_bound.digits = {3,6};
            CHECK(expected_interval == result_it.get_interval());

            // ([1.19, 1.19] + [1.19, 1.19]) + [1.19, 1.19]
            // [3.38, 3.38] + [1.19, 1.19]
            // [3.57, 3.57]
            ++result_it;
            expected_interval.lower_bound.digits = {3,5,7};
            expected_interval.upper_bound.digits = {3,5,7};
            CHECK(expected_interval == result_it.get_interval());

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.get_interval());
        }

        SECTION("a + (b + c)") {
            boost::real::real result = a + (b + c);

            auto result_it = result.get_real_itr().cbegin();

            // [1, 2] + ([1, 2] + [1, 2])
            // [1, 2] + [2, 4]
            // [3, 6]
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {6};
            CHECK(expected_interval == result_it.get_interval());

            // [1.1, 1.2] + ([1.1, 1.2] + [1.1, 1.2])
            // [1.1, 1.2] + [2.2, 2.4]
            // [3.3, 3.6]
            ++result_it;
            expected_interval.lower_bound.digits = {3,3};
            expected_interval.upper_bound.digits = {3,6};
            CHECK(expected_interval == result_it.get_interval());

            // [1.19, 1.19] + ([1.19, 1.19] + [1.19, 1.19])
            // [1.19, 1.19] + [3.8, 3.8]
            // [3.57, 3.57]
            ++result_it;
            expected_interval.lower_bound.digits = {3,5,7};
            expected_interval.upper_bound.digits = {3,5,7};
            CHECK(expected_interval == result_it.get_interval());

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.get_interval());
        }
    }

    SECTION("Without carry") {

        // Explicit numbers
        boost::real::real a("1.11");
        boost::real::real b("1.11");
        boost::real::real c("1.11");

        SECTION("(a + b) + c") {
            boost::real::real result = (a + b) + c;

            auto result_it = result.get_real_itr().cbegin();

            // ([1, 2] + [1, 2]) + [1, 2]
            // [2, 4] + [1, 2]
            // [3, 6]
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {6};
            CHECK(expected_interval == result_it.get_interval());

            // ([1.1, 1.2] + [1.1, 1.2]) + [1.1, 1.2]
            // [2.2, 2.4] + [1.1, 1.2]
            // [3.3, 3.6]
            ++result_it;
            expected_interval.lower_bound.digits = {3,3};
            expected_interval.upper_bound.digits = {3,6};
            CHECK(expected_interval == result_it.get_interval());

            // ([1.11, 1.11] + [1.11, 1.11]) + [1.11, 1.11]
            // [2.22, 2.22] + [1.11, 1.11]
            // [3.33, 3.33]
            ++result_it;
            expected_interval.lower_bound.digits = {3,3,3};
            expected_interval.upper_bound.digits = {3,3,3};
            CHECK(expected_interval == result_it.get_interval());

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.get_interval());
        }

        SECTION("a + (b + c)") {
            boost::real::real result = a + (b + c);

            auto result_it = result.get_real_itr().cbegin();

            // [1, 2] + ([1, 2] + [1, 2])
            // [1, 2] + [2, 4]
            // [3, 6]
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {6};
            CHECK(expected_interval == result_it.get_interval());

            // [1.1, 1.2] + ([1.1, 1.2] + [1.1, 1.2])
            // [1.1, 1.2] + [2.2, 2.4]
            // [3.3, 3.6]
            ++result_it;
            expected_interval.lower_bound.digits = {3,3};
            expected_interval.upper_bound.digits = {3,6};
            CHECK(expected_interval == result_it.get_interval());

            // [1.11, 1.11] + ([1.11, 1.11] + [1.11, 1.11])
            // [1.11, 1.11] + [2.22, 2.22]
            // [3.33, 3.33]
            ++result_it;
            expected_interval.lower_bound.digits = {3,3,3};
            expected_interval.upper_bound.digits = {3,3,3};
            CHECK(expected_interval == result_it.get_interval());

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.get_interval());
        }
    }
}
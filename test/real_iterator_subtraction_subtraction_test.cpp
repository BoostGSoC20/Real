#include <catch2/catch.hpp>
#include <map>

#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("Operators - - boost::real::const_precision_iterator") {
    boost::real::interval expected_interval({});

    SECTION("With carry") {

        // Explicit numbers
        boost::real::real a("1.19");
        boost::real::real b("1.19");
        boost::real::real c("1.19");

        SECTION("(a - b) - c") {
            boost::real::real result = (a - b) - c;

            auto result_it = result.cbegin();

            // ([1, 2] - [1, 2]) - [1, 2]
            // [-1, 1] - [1, 2]
            // [-3, 0]
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {0};
            CHECK(expected_interval == result_it.approximation_interval);

            // ([1.1, 1.2] - [1.1, 1.2]) - [1.1, 1.2]
            // [-0.1, 0.1] - [1.1, 1.2]
            // [-1.3, -1]
            ++result_it;
            expected_interval.upper_bound.positive = false;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1,3};
            expected_interval.upper_bound.digits = {1};
            CHECK(expected_interval == result_it.approximation_interval);

            // ([1.19, 1.19] - [1.19, 1.19]) - [1.19, 1.19]
            // [0, 0] - [1.19, 1.19]
            // [-1.19, -1.19]
            ++result_it;
            expected_interval.lower_bound.digits = {1,1,9};
            expected_interval.upper_bound.digits = {1,1,9};
            CHECK(expected_interval == result_it.approximation_interval);

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.approximation_interval);
        }

        SECTION("a - (b - c)") {
            boost::real::real result = a - (b - c);

            auto result_it = result.cbegin();

            // [1, 2] - ([1, 2] - [1, 2])
            // [1, 2] - [-1, 1]
            // [0, 3]
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {0};
            expected_interval.upper_bound.digits = {3};
            CHECK(expected_interval == result_it.approximation_interval);

            // [1.1, 1.2] - ([1.1, 1.2] - [1.1, 1.2])
            // [1.1, 1.2] - [-0.1, 0.1]
            // [1, 1.3]
            ++result_it;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1,3};
            CHECK(expected_interval == result_it.approximation_interval);

            // [1.19, 1.19] - ([1.19, 1.19] - [1.19, 1.19])
            // [1.19, 1.19] - [0, 0]
            // [1.19, 1.19]
            ++result_it;
            expected_interval.lower_bound.digits = {1,1,9};
            expected_interval.upper_bound.digits = {1,1,9};
            CHECK(expected_interval == result_it.approximation_interval);

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.approximation_interval);
        }
    }
}
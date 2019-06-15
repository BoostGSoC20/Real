#include <catch2/catch.hpp>
#include <map>

#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("Operators - * boost::real::const_precision_iterator") {
    boost::real::interval expected_interval({});

    SECTION("With carry") {

        // Explicit numbers
        boost::real::real a("1.19");
        boost::real::real b("1.19");
        boost::real::real c("1.19");

        SECTION("(a - b) * c") {
            boost::real::real result = (a - b) * c;

            auto result_it = result.get_real_itr().cbegin();

            // ([1, 2] - [1, 2]) * [1, 2]
            // [-1, 1] * [1, 2]
            // [-2, 2]
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {2};
            CHECK(expected_interval == result_it.get_interval());

            // ([1.1, 1.2] - [1.1, 1.2]) * [1.1, 1.2]
            // [-0.1, 0.1] * [1.1, 1.2]
            // [-0.12, 0.12]
            ++result_it;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {1,2};
            expected_interval.upper_bound.digits = {1,2};
            CHECK(expected_interval == result_it.get_interval());

            // ([1.19, 1.19] - [1.19, 1.19]) * [1.19, 1.19]
            // [0, 0] * [1.19, 1.19]
            // [0, 0]
            ++result_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.lower_bound.digits = {0};
            expected_interval.upper_bound.digits = {0};
            CHECK(expected_interval == result_it.get_interval());

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.get_interval());
        }

        SECTION("a - (b * c)") {
            boost::real::real result = a - (b * c);

            auto result_it = result.get_real_itr().cbegin();

            // [1, 2] - ([1, 2] * [1, 2])
            // [1, 2] - [1, 4]
            // [-3, 1]
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {1};
            CHECK(expected_interval == result_it.get_interval());

            // [1.1, 1.2] - ([1.1, 1.2] * [1.1, 1.2])
            // [1.1, 1.2] - [1.21, 1.44]
            // [-0.34, -0.01]
            ++result_it;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = -1;
            expected_interval.lower_bound.digits = {3,4};
            expected_interval.upper_bound.digits = {1};
            CHECK(expected_interval == result_it.get_interval());

            // [1.19, 1.19] - ([1.19, 1.19] * [1.19, 1.19])
            // [1.19, 1.19] * [1,4161, 1,4161]
            // [-0.2261, -0.2261]
            ++result_it;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {2,2,6,1};
            expected_interval.upper_bound.digits = {2,2,6,1};
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

        SECTION("(a - b) * c") {
            boost::real::real result = (a - b) * c;

            auto result_it = result.get_real_itr().cbegin();

            // ([1, 2] - [1, 2]) * [1, 2]
            // [-1, 1] * [1, 2]
            // [-2, 2]
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {2};
            CHECK(expected_interval == result_it.get_interval());

            // ([1.1, 1.2] - [1.1, 1.2]) * [1.1, 1.2]
            // [-0.1, 0.1] * [1.1, 1.2]
            // [-0.12, 0.12]
            ++result_it;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {1,2};
            expected_interval.upper_bound.digits = {1,2};
            CHECK(expected_interval == result_it.get_interval());

            // ([1.11, 1.11] - [1.11, 1.11]) * [1.11, 1.11]
            // [0, 0] * [1.11, 1.11]
            // [0, 0]
            ++result_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.lower_bound.digits = {0};
            expected_interval.upper_bound.digits = {0};
            CHECK(expected_interval == result_it.get_interval());

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.get_interval());
        }

        SECTION("a - (b * c)") {
            boost::real::real result = a - (b * c);

            auto result_it = result.get_real_itr().cbegin();

            // [1, 2] - ([1, 2] * [1, 2])
            // [1, 2] - [1, 4]
            // [-3, 1]
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {1};
            CHECK(expected_interval == result_it.get_interval());

            // [1.1, 1.2] - ([1.1, 1.2] * [1.1, 1.2])
            // [1.1, 1.2] - [1.21, 1.44]
            // [-0.34, -0.01]
            ++result_it;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = -1;
            expected_interval.lower_bound.digits = {3,4};
            expected_interval.upper_bound.digits = {1};
            CHECK(expected_interval == result_it.get_interval());

            // [1.11, 1.11] - ([1.11, 1.11] * [1.11, 1.11])
            // [1.11, 1.11] - [1,2321, 1,2321]
            // [-0.1221, -0.1221]
            ++result_it;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {1,2,2,1};
            expected_interval.upper_bound.digits = {1,2,2,1};
            CHECK(expected_interval == result_it.get_interval());

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.get_interval());
        }
    }
}
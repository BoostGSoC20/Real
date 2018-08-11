#include <catch2/catch.hpp>
#include <map>

#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("Operators + * boost::real::const_precision_iterator") {
    boost::real::interval expected_interval({});

    SECTION("With carry") {

        // Explicit numbers
        boost::real::real a("1.19");
        boost::real::real b("1.19");
        boost::real::real c("1.19");

        SECTION("(a + b) * c") {
            boost::real::real result = (a + b) * c;

            auto result_it = result.cbegin();

            // ([1, 2] + [1, 2]) * [1, 2]
            // [2, 4] * [1, 2]
            // [2, 8]
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {8};
            CHECK(expected_interval == result_it.approximation_interval);

            // ([1.1, 1.2] + [1.1, 1.2]) * [1.1, 1.2]
            // [2.2, 2.4] * [1.1, 1.2]
            // [2.42, 2.88]
            ++result_it;
            expected_interval.lower_bound.digits = {2,4,2};
            expected_interval.upper_bound.digits = {2,8,8};
            CHECK(expected_interval == result_it.approximation_interval);

            // ([1.19, 1.19] + [1.19, 1.19]) * [1.19, 1.19]
            // [2.38, 2.38] * [1.19, 1.19]
            // [2.8322, 2.8322]
            ++result_it;
            expected_interval.lower_bound.digits = {2,8,3,2,2};
            expected_interval.upper_bound.digits = {2,8,3,2,2};
            CHECK(expected_interval == result_it.approximation_interval);

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.approximation_interval);
        }

        SECTION("a + (b * c)") {
            boost::real::real result = a + (b * c);

            auto result_it = result.cbegin();

            // [1, 2] + ([1, 2] * [1, 2])
            // [1, 2] + [1, 4]
            // [2, 6]
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {6};
            CHECK(expected_interval == result_it.approximation_interval);

            // [1.1, 1.2] + ([1.1, 1.2]) * [1.1, 1.2])
            // [1.1, 1.2] + [1.21, 1.44]
            // [2.31, 2.64]
            ++result_it;
            expected_interval.lower_bound.digits = {2,3,1};
            expected_interval.upper_bound.digits = {2,6,4};
            CHECK(expected_interval == result_it.approximation_interval);

            // [1.19, 1.19] + ([1.19, 1.19] * [1.19, 1.19])
            // [1.19, 1.19] + [1.4161, 1.4161]
            // [2.6061, 2.6061]
            ++result_it;
            expected_interval.lower_bound.digits = {2,6,0,6,1};
            expected_interval.upper_bound.digits = {2,6,0,6,1};
            CHECK(expected_interval == result_it.approximation_interval);

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.approximation_interval);
        }
    }

    SECTION("Without carry") {

        // Explicit numbers
        boost::real::real a("1.11");
        boost::real::real b("1.11");
        boost::real::real c("1.11");

        SECTION("(a + b) * c") {
            boost::real::real result = (a + b) * c;

            auto result_it = result.cbegin();

            // ([1, 2] + [1, 2]) * [1, 2]
            // [2, 4] * [1, 2]
            // [2, 8]
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {8};
            CHECK(expected_interval == result_it.approximation_interval);

            // ([1.1, 1.2] + [1.1, 1.2]) * [1.1, 1.2]
            // [2.2, 2.4] * [1.1, 1.2]
            // [2.42, 2.88]
            ++result_it;
            expected_interval.lower_bound.digits = {2,4,2};
            expected_interval.upper_bound.digits = {2,8,8};
            CHECK(expected_interval == result_it.approximation_interval);

            // ([1.11, 1.11] + [1.11, 1.11]) * [1.11, 1.11]
            // [2.22, 2.22] * [1.11, 1.11]
            // [2.4642, 2.4642]
            ++result_it;
            expected_interval.lower_bound.digits = {2,4,6,4,2};
            expected_interval.upper_bound.digits = {2,4,6,4,2};
            CHECK(expected_interval == result_it.approximation_interval);

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.approximation_interval);
        }

        SECTION("a + (b * c)") {
            boost::real::real result = a + (b * c);

            auto result_it = result.cbegin();

            // [1, 2] + ([1, 2] * [1, 2])
            // [1, 2] + [1, 4]
            // [2, 6]
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {6};
            CHECK(expected_interval == result_it.approximation_interval);

            // [1.1, 1.2] + ([1.1, 1.2]) * [1.1, 1.2])
            // [1.1, 1.2] + [1.21, 1.44]
            // [2.31, 2.64]
            ++result_it;
            expected_interval.lower_bound.digits = {2,3,1};
            expected_interval.upper_bound.digits = {2,6,4};
            CHECK(expected_interval == result_it.approximation_interval);

            // [1.11, 1.11] + ([1.11, 1.11] * [1.11, 1.11])
            // [1.11, 1.11] + [1.2321, 1.2321]
            // [2.3421, 2.3421]
            ++result_it;
            expected_interval.lower_bound.digits = {2,3,4,2,1};
            expected_interval.upper_bound.digits = {2,3,4,2,1};
            CHECK(expected_interval == result_it.approximation_interval);

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(expected_interval == result_it.approximation_interval);
        }
    }
}
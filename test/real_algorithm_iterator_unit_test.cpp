#include <catch2/catch.hpp>
#include <iostream>

#include <real/real_algorithm.hpp>

TEST_CASE("Iterate boost::real_algorithm::const_precision_iterator until full precision is reached") {

    SECTION("Positive numbers") {

        SECTION("Without carry in the boundary calculations") {

            SECTION("Testing for number 0.333333...") {

                boost::real::real_algorithm a([](unsigned int n) { return 3; }, 0);
                boost::real::real_algorithm::const_precision_iterator approximation_it = a.cbegin();
                boost::real::interval expected_interval;
                expected_interval.lower_bound.exponent = a.exponent();
                expected_interval.lower_bound.positive = a.positive();
                expected_interval.upper_bound.exponent = a.exponent();
                expected_interval.upper_bound.positive = a.positive();
                for (int i = 0; i < 11; i++) {

                    if (i > 0) {
                        expected_interval.upper_bound.digits.back()--;
                    }
                    expected_interval.lower_bound.push_back(a[i]);
                    expected_interval.upper_bound.push_back(a[i] + 1);

                    CHECK( approximation_it.approximation_interval == expected_interval );
                    ++approximation_it;
                }
            }
        }

        SECTION("With carry in the upper boundary calculation, number 1.99999999989999999998999...") {
            boost::real::real_algorithm a(
                    [](unsigned int n) {
                        if (n == 0) return 1;
                        else if (n == 10 || n == 20) return 8;
                        else return 9;
                    }, 3);
            boost::real::real_algorithm::const_precision_iterator approximation_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = a.exponent();
            expected_interval.lower_bound.positive = a.positive();
            expected_interval.upper_bound.exponent = a.exponent();
            expected_interval.upper_bound.positive = a.positive();
            expected_interval.upper_bound.push_back(2);
            for (int i = 0; i < 10; i++) {
                expected_interval.lower_bound.push_back(a[i]);
                CHECK( approximation_it.approximation_interval == expected_interval );
                ++approximation_it;
            }

            expected_interval.upper_bound = expected_interval.lower_bound;
            expected_interval.upper_bound.push_back(9);

            for (int i = 10; i < 20; i++) {
                expected_interval.lower_bound.push_back(a[i]);
                CHECK( approximation_it.approximation_interval == expected_interval );
                ++approximation_it;
            }

            expected_interval.upper_bound = expected_interval.lower_bound;
            expected_interval.upper_bound.push_back(9);

            for (int i = 20; i < 50; i++) {
                expected_interval.lower_bound.push_back(a[i]);
                CHECK( approximation_it.approximation_interval == expected_interval );
                ++approximation_it;
            }
        }
    }

    SECTION("Negative numbers") {

        SECTION("Testing for number -0.333333...") {

            boost::real::real_algorithm a([](unsigned int n) { return 3; }, 0, false);
            boost::real::real_algorithm::const_precision_iterator approximation_it = a.cbegin();
            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = a.exponent();
            expected_interval.lower_bound.positive = a.positive();
            expected_interval.upper_bound.exponent = a.exponent();
            expected_interval.upper_bound.positive = a.positive();
            for (int i = 0; i < 11; i++) {

                if (i > 0) {
                    expected_interval.lower_bound.digits.back()--;
                }
                expected_interval.upper_bound.push_back(a[i]);
                expected_interval.lower_bound.push_back(a[i] + 1);

                CHECK( approximation_it.approximation_interval == expected_interval );
                ++approximation_it;
            }
        }

        SECTION("With carry in the upper boundary calculation, number -1.99999999989999999998999...") {
            boost::real::real_algorithm a(
                    [](unsigned int n) {
                        if (n == 0) return 1;
                        else if (n == 10 || n == 20) return 8;
                        else return 9;
                    }, 3, false);
            boost::real::real_algorithm::const_precision_iterator approximation_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = a.exponent();
            expected_interval.lower_bound.positive = a.positive();
            expected_interval.upper_bound.exponent = a.exponent();
            expected_interval.upper_bound.positive = a.positive();

            expected_interval.lower_bound.push_back(2);
            for (int i = 0; i < 10; i++) {
                expected_interval.upper_bound.push_back(a[i]);
                CHECK( approximation_it.approximation_interval == expected_interval );
                ++approximation_it;
            }

            expected_interval.lower_bound = expected_interval.upper_bound;
            expected_interval.lower_bound.push_back(9);

            for (int i = 10; i < 20; i++) {
                expected_interval.upper_bound.push_back(a[i]);
                CHECK( approximation_it.approximation_interval == expected_interval );
                ++approximation_it;
            }

            expected_interval.lower_bound = expected_interval.upper_bound;
            expected_interval.lower_bound.push_back(9);

            for (int i = 20; i < 50; i++) {
                expected_interval.upper_bound.push_back(a[i]);
                CHECK( approximation_it.approximation_interval == expected_interval );
                ++approximation_it;
            }
        }
    }
}

TEST_CASE("Iterator cend") {

    boost::real::real_algorithm a([](unsigned int n) { return 3; }, 0);
    boost::real::real_algorithm::const_precision_iterator approximation_it = a.cbegin();
    boost::real::real_algorithm::const_precision_iterator end_it = a.cend();

    SECTION("Iterate until the maximum set precision returns the end of the iterator") {

        for(int i = 0; i < 9; i++) {
            CHECK_FALSE( approximation_it == end_it );
            ++approximation_it;
        }

        CHECK( approximation_it == end_it );
    }

    SECTION("Iterate cend() returns an interval with the lower boundary digit amount as the maximum precision") {

        CHECK( end_it.approximation_interval.lower_bound.digits.size() == a.max_precision() );
        CHECK( end_it.approximation_interval.lower_bound.positive == a.positive() );
        CHECK( end_it.approximation_interval.lower_bound.exponent == a.exponent() );
    }
}

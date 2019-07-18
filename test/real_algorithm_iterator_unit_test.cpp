#include <catch2/catch.hpp>
#include <iostream>

#include <real/real_algorithm.hpp>
#include <test_helpers.hpp>


TEST_CASE("Iterate boost::real_algorithm::const_precision_iterator until full precision is reached") {
    SECTION("Positive numbers") {

        SECTION("Without carry in the boundary calculations") {

            SECTION("Testing for number 0.333333...") {
                boost::real::real<> a([](unsigned int n) -> int { return 3; }, 0);
                auto approximation_it = a.get_real_itr().cbegin();

                boost::real::interval expected_interval;
                expected_interval.lower_bound.exponent = approximation_it.get_interval().lower_bound.exponent;
                expected_interval.lower_bound.positive = approximation_it.get_interval().lower_bound.positive;
                expected_interval.upper_bound.exponent = approximation_it.get_interval().upper_bound.exponent;
                expected_interval.upper_bound.positive = approximation_it.get_interval().upper_bound.positive;
                for (int i = 0; i < 11; i++) {

                    if (i > 0) {
                        expected_interval.upper_bound.digits.back()--;
                    }
                    expected_interval.lower_bound.push_back(a[i]);
                    expected_interval.upper_bound.push_back(a[i] + 1);

                    CHECK( approximation_it.get_interval() == expected_interval );
                    ++approximation_it;
                }
            }
        }

        SECTION("With carry in the upper boundary calculation, number 1.99999999989999999998999...") {
            boost::real::real<> a(
                    [](unsigned int n) -> int {
                        if (n == 0) return 1;
                        else if (n == 10 || n == 20) return 8;
                        else return 9;
                    }, 3);
            auto approximation_it = boost::real::real(a).get_real_itr().cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = approximation_it.get_interval().lower_bound.exponent;
            expected_interval.lower_bound.positive = approximation_it.get_interval().lower_bound.positive;
            expected_interval.upper_bound.exponent = approximation_it.get_interval().upper_bound.exponent;
            expected_interval.upper_bound.positive = approximation_it.get_interval().upper_bound.positive;
            expected_interval.upper_bound.push_back(2);
            for (int i = 0; i < 10; i++) {
                expected_interval.lower_bound.push_back(a[i]);
                CHECK( approximation_it.get_interval() == expected_interval );
                ++approximation_it;
            }

            expected_interval.upper_bound = expected_interval.lower_bound;
            expected_interval.upper_bound.push_back(9);

            for (int i = 10; i < 20; i++) {
                expected_interval.lower_bound.push_back(a[i]);
                CHECK( approximation_it.get_interval() == expected_interval );
                ++approximation_it;
            }

            expected_interval.upper_bound = expected_interval.lower_bound;
            expected_interval.upper_bound.push_back(9);

            for (int i = 20; i < 50; i++) {
                expected_interval.lower_bound.push_back(a[i]);
                CHECK( approximation_it.get_interval() == expected_interval );
                ++approximation_it;
            }
        }
    }

    SECTION("Negative numbers") {

        SECTION("Testing for number -0.333333...") {

            boost::real::real<> a([](unsigned int n) -> int { return 3; }, 0, false);
            auto approximation_it = boost::real::real(a).get_real_itr().cbegin();
            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = approximation_it.get_interval().lower_bound.exponent;
            expected_interval.lower_bound.positive = approximation_it.get_interval().lower_bound.positive;
            expected_interval.upper_bound.exponent = approximation_it.get_interval().upper_bound.exponent;
            expected_interval.upper_bound.positive = approximation_it.get_interval().upper_bound.positive;
            for (int i = 0; i < 11; i++) {

                if (i > 0) {
                    expected_interval.lower_bound.digits.back()--;
                }
                expected_interval.upper_bound.push_back(a[i]);
                expected_interval.lower_bound.push_back(a[i] + 1);

                CHECK( approximation_it.get_interval() == expected_interval );
                ++approximation_it;
            }
        }

        SECTION("With carry in the upper boundary calculation, number -1.99999999989999999998999...") {
            boost::real::real<> a(
                    [](unsigned int n) -> int {
                        if (n == 0) return 1;
                        else if (n == 10 || n == 20) return 8;
                        else return 9;
                    }, 3, false);
            auto approximation_it = boost::real::real(a).get_real_itr().cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = approximation_it.get_interval().lower_bound.exponent;
            expected_interval.lower_bound.positive = approximation_it.get_interval().lower_bound.positive;
            expected_interval.upper_bound.exponent = approximation_it.get_interval().upper_bound.exponent;
            expected_interval.upper_bound.positive = approximation_it.get_interval().upper_bound.positive;

            expected_interval.lower_bound.push_back(2);
            for (int i = 0; i < 10; i++) {
                expected_interval.upper_bound.push_back(a[i]);
                CHECK( approximation_it.get_interval() == expected_interval );
                ++approximation_it;
            }

            expected_interval.lower_bound = expected_interval.upper_bound;
            expected_interval.lower_bound.push_back(9);

            for (int i = 10; i < 20; i++) {
                expected_interval.upper_bound.push_back(a[i]);
                CHECK( approximation_it.get_interval() == expected_interval );
                ++approximation_it;
            }

            expected_interval.lower_bound = expected_interval.upper_bound;
            expected_interval.lower_bound.push_back(9);

            for (int i = 20; i < 50; i++) {
                expected_interval.upper_bound.push_back(a[i]);
                CHECK( approximation_it.get_interval() == expected_interval );
                ++approximation_it;
            }
        }
    }
}

TEST_CASE("Iterator cend") {

    boost::real::real<> a([](unsigned int n) -> int { return 3; }, 0);
    auto approximation_it = boost::real::real(a).get_real_itr().cbegin();
    auto end_it = boost::real::real(a).get_real_itr().cend();

    SECTION("Iterate until the maximum set precision returns the end of the iterator") {

        for(int i = 0; i < 9; i++) {
            CHECK_FALSE( approximation_it == end_it );
            ++approximation_it;
        }

        CHECK( approximation_it == end_it );
    }

    SECTION("Iterate cend() returns an interval with the lower boundary digit amount as the maximum precision") {

        CHECK( end_it.get_interval().lower_bound.digits.size() == boost::real::real(a).max_precision() );
        CHECK( end_it.get_interval().lower_bound.positive == approximation_it.get_interval().lower_bound.positive);
        CHECK( end_it.get_interval().lower_bound.exponent == approximation_it.get_interval().lower_bound.exponent);
    }
}

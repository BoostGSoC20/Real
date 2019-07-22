#include <catch2/catch.hpp>
#include <iostream>

#include <real/real_algorithm.hpp>
#include <test_helpers.hpp>


TEST_CASE("Iterate boost::real_algorithm::const_precision_iterator until full precision is reached") {
    boost::real::exact_number length;
    SECTION("Positive numbers") {

        SECTION("Without carry in the boundary calculations") {

            SECTION("Testing for number 0.333333...") {
                boost::real::real<> a([](unsigned int n) -> int { return 3; }, 0);
                auto approximation_it = a.get_real_itr().cbegin();
                
                length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;
                for (int i = 0; i < 11; i++) {
                    CHECK(approximation_it.get_interval().lower_bound <= approximation_it.get_interval().upper_bound);
                    CHECK(approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound <= length);
                    length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;
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

            length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;
                for (int i = 0; i < 20; i++) {
                    CHECK(approximation_it.get_interval().lower_bound <= approximation_it.get_interval().upper_bound);
                    CHECK(approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound <= length);
                    length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;
                }
        }
    }

    SECTION("Negative numbers") {

        SECTION("Testing for number -0.333333...") {

            boost::real::real<> a([](unsigned int n) -> int { return 3; }, 0, false);
            auto approximation_it = boost::real::real(a).get_real_itr().cbegin();

            length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;
                for (int i = 0; i < 11; i++) {
                    CHECK(approximation_it.get_interval().lower_bound <= approximation_it.get_interval().upper_bound);
                    CHECK(approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound <= length);
                    length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;
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

            length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;
                for (int i = 0; i < 20; i++) {
                    CHECK(approximation_it.get_interval().lower_bound <= approximation_it.get_interval().upper_bound);
                    CHECK(approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound <= length);
                    length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;
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

        boost::real::exact_number a("0.33333332");
        boost::real::exact_number b("0.33333334");

        CHECK( end_it.get_interval().lower_bound >= a);
        CHECK( end_it.get_interval().upper_bound <= b);
    }
}

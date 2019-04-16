#include <catch2/catch.hpp>
#include <real/real_explicit.hpp>
#include <test_helpers.hpp>

TEST_CASE("Iterate boost::real_explicit::const_precision_iterator until full precision is reached") {

    SECTION("Positive numbers") {

        SECTION("Without carry in the boundary calculations") {

            std::vector<std::string> numbers = {
                    "0.011111111",
                    "0.001111111",
                    "1.111111111",
                    "11.11111111",
                    "111.1111111"
            };

            for (auto number : numbers) {
                SECTION("Testing for number " + number) {

                    boost::real::real_explicit a(number);
                    boost::real::real_explicit::const_precision_iterator approximation_it = a.cbegin();
                    boost::real::interval expected_interval;
                    expected_interval.lower_bound.exponent = a.exponent();
                    expected_interval.lower_bound.positive = a.positive();
                    expected_interval.upper_bound.exponent = a.exponent();
                    expected_interval.upper_bound.positive = a.positive();
                    for (int i = 0; i < 11; i++) {
                        expected_interval.upper_bound.clear();
                        for (auto d : expected_interval.lower_bound.digits) {
                            expected_interval.upper_bound.push_back(d);
                        }

                        if (i < (int)a.digits().size() - 1) {
                            expected_interval.lower_bound.push_back(a[i]);
                            expected_interval.upper_bound.push_back(a[i] + 1);
                        } else if (i == (int)a.digits().size() - 1) {
                            expected_interval.lower_bound.push_back(a[i]);
                            expected_interval.upper_bound.push_back(a[i]);
                        }

                        CHECK( approximation_it.approximation_interval == expected_interval );
                        ++approximation_it;
                    }
                }
            }
        }

        SECTION("With carry in the upper boundary calculation") {
            boost::real::real_explicit a("1.99999998");
            boost::real::real_explicit::const_precision_iterator approximation_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = a.exponent();
            expected_interval.lower_bound.positive = a.positive();
            expected_interval.upper_bound.exponent = a.exponent();
            expected_interval.upper_bound.positive = a.positive();
            expected_interval.upper_bound.push_back(2);
            for (int i = 0; i < 11; i++) {

                if (i < (int)a.digits().size()) {
                    expected_interval.lower_bound.push_back(a[i]);
                }

                if (i == (int)a.digits().size() - 1) {
                    expected_interval.upper_bound.clear();
                    for (auto d : expected_interval.lower_bound.digits) {
                        expected_interval.upper_bound.push_back(d);
                    }
                }

                CHECK( approximation_it.approximation_interval == expected_interval );
                ++approximation_it;
            }
        }
    }


    SECTION("Negative numbers") {

        SECTION("Without carry in the boundary calculations") {

            std::vector<std::string> numbers = {
                    "-0.011111111",
                    "-0.001111111",
                    "-1.111111111",
                    "-11.11111111",
                    "-111.1111111"
            };

            for (auto number : numbers) {
                SECTION("Testing for number " + number) {

                    boost::real::real_explicit a(number);
                    boost::real::real_explicit::const_precision_iterator approximation_it = a.cbegin();
                    boost::real::interval expected_interval;
                    expected_interval.lower_bound.exponent = a.exponent();
                    expected_interval.lower_bound.positive = a.positive();
                    expected_interval.upper_bound.exponent = a.exponent();
                    expected_interval.upper_bound.positive = a.positive();

                    // Boundaries are mirrored
                    for (int i = 0; i < 11; i++) {
                        expected_interval.lower_bound.clear();
                        for (auto d : expected_interval.upper_bound.digits) {
                            expected_interval.lower_bound.push_back(d);
                        }

                        if (i < (int)a.digits().size() - 1) {
                            expected_interval.upper_bound.push_back(a[i]);
                            expected_interval.lower_bound.push_back(a[i] + 1);
                        } else if (i == (int)a.digits().size() - 1) {
                            expected_interval.upper_bound.push_back(a[i]);
                            expected_interval.lower_bound.push_back(a[i]);
                        }

                        CHECK( approximation_it.approximation_interval == expected_interval );
                        ++approximation_it;
                    }
                }
            }
        }

        SECTION("With carry in the upper boundary calculation") {
            boost::real::real_explicit a("-1.99999998");
            boost::real::real_explicit::const_precision_iterator approximation_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = a.exponent();
            expected_interval.lower_bound.positive = a.positive();
            expected_interval.upper_bound.exponent = a.exponent();
            expected_interval.upper_bound.positive = a.positive();
            expected_interval.lower_bound.push_back(2);
            for (int i = 0; i < 11; i++) {

                if (i < (int)a.digits().size()) {
                    expected_interval.upper_bound.push_back(a[i]);
                }

                if (i == (int)a.digits().size() - 1) {
                    expected_interval.lower_bound.clear();
                    for (auto d : expected_interval.upper_bound.digits) {
                        expected_interval.lower_bound.push_back(d);
                    }
                }

                CHECK( approximation_it.approximation_interval == expected_interval );
                ++approximation_it;
            }
        }
    }
}

TEST_CASE("Iterator cend") {

    boost::real::real_explicit a("-1.99999998");
    boost::real::real_explicit::const_precision_iterator approximation_it = a.cbegin();
    boost::real::real_explicit::const_precision_iterator end_it = a.cend();

    SECTION("Iterate until the full explicit number digit amount returns the end of the iterator") {

        for(int i = 0; i < 7; i++) {
            CHECK_FALSE( approximation_it == end_it );
            ++approximation_it;
        }

        ++approximation_it;

        CHECK( approximation_it == end_it );
    }

    SECTION("Iterate cend() returns an interval with both boundaries equal to the number") {

        CHECK( end_it.approximation_interval.lower_bound == end_it.approximation_interval.upper_bound );
        CHECK( end_it.approximation_interval.lower_bound.digits == a.digits() );
        CHECK( end_it.approximation_interval.lower_bound.positive == a.positive() );
        CHECK( end_it.approximation_interval.lower_bound.exponent == a.exponent() );
    }
}
#include <catch2/catch.hpp>
#include <map>

#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("Operators + + boost::real::const_precision_iterator") {

    boost::real::interval expected_interval({});

    SECTION("With carry") {

        // Explicit numbers
        boost::real::real a("9999999999999999999999999999999");
        boost::real::real b("9999999999999999999999999999999");
        boost::real::real c("9999999999999999999999999999999");

        SECTION("(a + b) + c") {
            boost::real::real result = (a + b) + c;
            boost::real::real result2 = (a + b) + c;
            auto end_it = result2.get_real_itr().cend();
            CHECK(end_it.get_interval().lower_bound == end_it.get_interval().upper_bound);

            auto result_it = result.get_real_itr().cbegin();

            CHECK(result_it.get_interval().lower_bound < end_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound > end_it.get_interval().upper_bound);

            ++result_it;
            CHECK(result_it.get_interval().lower_bound < end_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound > end_it.get_interval().upper_bound);

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(end_it.get_interval() == result_it.get_interval());
        }

        SECTION("a + (b + c)") {
            boost::real::real result = a + (b + c);
            boost::real::real result2 = a + (b + c);
            auto end_it = result2.get_real_itr().cend();
            CHECK(end_it.get_interval().lower_bound == end_it.get_interval().upper_bound);

            auto result_it = result.get_real_itr().cbegin();

            CHECK(result_it.get_interval().lower_bound < end_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound > end_it.get_interval().upper_bound);

            ++result_it;
            CHECK(result_it.get_interval().lower_bound < end_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound > end_it.get_interval().upper_bound);

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(end_it.get_interval() == result_it.get_interval());
        }
    }

    SECTION("Without carry") {

        // Explicit numbers
        boost::real::real a("123");
        boost::real::real b("123");
        boost::real::real c("123");

        SECTION("(a + b) + c") {
            boost::real::real result = (a + b) + c;
            boost::real::real result2 = (a + b) + c;
            auto end_it = result2.get_real_itr().cend();
            CHECK(end_it.get_interval().lower_bound == end_it.get_interval().upper_bound);

            auto result_it = result.get_real_itr().cbegin();

            CHECK(result_it.get_interval().lower_bound < end_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound > end_it.get_interval().upper_bound);

            ++result_it;
            CHECK(result_it.get_interval().lower_bound < end_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound > end_it.get_interval().upper_bound);

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(end_it.get_interval() == result_it.get_interval());
        }

        SECTION("a + (b + c)") {
            boost::real::real result = a + (b + c);
            boost::real::real result2 = a + (b + c);
            auto end_it = result2.get_real_itr().cend();
            CHECK(end_it.get_interval().lower_bound == end_it.get_interval().upper_bound);

            auto result_it = result.get_real_itr().cbegin();

            CHECK(result_it.get_interval().lower_bound < end_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound > end_it.get_interval().upper_bound);

            ++result_it;
            CHECK(result_it.get_interval().lower_bound < end_it.get_interval().upper_bound);
            CHECK(result_it.get_interval().upper_bound > end_it.get_interval().upper_bound);

            // Full precision reached, no more changes are made
            ++result_it;
            CHECK(end_it.get_interval() == result_it.get_interval());
        }
    }
}
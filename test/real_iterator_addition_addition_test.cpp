#include <catch2/catch.hpp>
#include <map>

#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("Operators + + boost::real::const_precision_iterator") {

    // Explicit numbers
    boost::real::real a("9999999999999999999999999999999");
    boost::real::real b("9999999999999999999999999999999");
    boost::real::real c("9999999999999999999999999999999");

    SECTION("(a + b) + c") {
        boost::real::real result = (a + b) + c;
        auto end_it = result.get_real_itr().cend();

        auto result_it = result.get_real_itr().cbegin();

        boost::real::exact_number length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;
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

        // Full precision reached, no more changes are made
        ++result_it;
        CHECK(end_it == result_it);
    }

    SECTION("a + (b + c)") {
        boost::real::real result = a + (b + c);
        auto end_it = result.get_real_itr().cend();

        auto result_it = result.get_real_itr().cbegin();

        boost::real::exact_number length = result_it.get_interval().upper_bound - result_it.get_interval().lower_bound;
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

        // Full precision reached, no more changes are made
        ++result_it;
        CHECK(end_it == result_it);
    }
}
#include <catch2/catch.hpp>
#include <map>

#include <real/real.hpp>
#include <test_helpers.hpp>

TEMPLATE_TEST_CASE("Operators + * boost::real::const_precision_iterator", "[template]", int, long, long long) {

    using real=boost::real::real<TestType>;

    // Explicit numbers
    real a("9999999999999999999999999999999");
    real b("9999999999999999999999999999999");
    real c("9999999999999999999999999999999");

    SECTION("(a + b) * c") {
        real result = (a + b) * c;
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

    SECTION("a + (b * c)") {
        real result = a + (b * c);
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

        ++result_it;
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
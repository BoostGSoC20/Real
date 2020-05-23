#include <catch2/catch.hpp>
#include <test_helpers.hpp>
#include <real/real.hpp>
#include <real/exact_number.hpp>

TEST_CASE("number from string function") {
    SECTION("a == b") {
    	boost::real::real a("123000.00012e5");
        boost::real::real b("12300000012");
        CHECK(a==b);

    }
    SECTION("a == b") {
        boost::real::real a ("100.1e1");
        boost::real::real b ("1001");
        CHECK( a == b );
    }
    SECTION("a == b") {
        boost::real::real a ("154000.32e2");
        boost::real::real b ("15400032");
        CHECK( a == b );
    }
    SECTION("a == b") {
        boost::real::real a ("123000.123e3");
        boost::real::real b ("123000123");
        CHECK( a == b );
    }
}

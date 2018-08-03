#include <catch2/catch.hpp>
#include <real/real.hpp>

TEST_CASE("Create boost::real_explicit from strings") {

    SECTION("Test with positive integer numbers") {
        boost::real::real_explicit a("11");

        CHECK( a.exponent() == 2 );
        CHECK( a.digits() == std::vector<int>({1,1}) );
    }
}
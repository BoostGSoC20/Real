#include <catch2/catch.hpp>
#include <real/real.hpp>
#include <real/utils.hpp>

SCENARIO("Real numbers addition is commutative" ) {

    GIVEN("Two real numbers") {
        boost::real::real c({0,9,9,9,9,9,9}, 1);
        boost::real::real d({0,9,9,9,9,9,9}, 1);

        THEN(" c + d is equal to d + c when printed with the numbers maximum precision") {
            boost::real::real e1 = c + d;
            boost::real::real e2 = d + c;

            CHECK(boost::real::to_string(e1) == boost::real::to_string(e2));
        }
    }


}
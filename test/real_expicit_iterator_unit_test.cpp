#include <catch2/catch.hpp>
#include <real/real.hpp>

TEST_CASE("Iterate boost::real_explicit::const_precision_iterator until full precision is reached") {

    boost::real::real_explicit a("12.111111111");
    boost::real::real_explicit b("1.999999998");

    SECTION("Number with all ones upper boundary has 2 as last digit") {

        boost::real::real_explicit::const_precision_iterator approximation_it = a.cbegin();

        std::cout << approximation_it.approximation_interval << std::endl;

        CHECK(true);
        for (int i = 0; i < 10; i++) {
            ++approximation_it;
            std::cout << approximation_it.approximation_interval << std::endl;

        }
    }


}
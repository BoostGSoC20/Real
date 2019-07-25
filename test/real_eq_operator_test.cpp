#include <catch2/catch.hpp>
#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("Operator ==") {

    SECTION("Explicit == Explicit") {
        boost::real::real a("-13251306276306304250236049144144144492977320");
        boost::real::real b("38409583409583490580394345345345346356456");
        boost::real::real c = a/b;

        boost::real::const_precision_iterator result_it = c.get_real_itr().cbegin();
        for (int i = 0; i<5; ++i) {
            std::cout<<"\n"<<result_it.get_interval();
            ++result_it;
        }
    }
}

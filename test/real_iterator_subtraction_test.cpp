#include <catch2/catch.hpp>
#include <map>

#include <real/real.hpp>
#include <test_helpers.hpp>


TEST_CASE("Operator - boost::real::const_precision_iterator") {

    boost::real::exact_number length;
    std::map<std::string, boost::real::real<int>> numbers;

    // Explicit numbers
    numbers.emplace("E(+1.9)", "1.9");
    numbers.emplace("E(-1.9)", "-1.9");
    numbers.emplace("E(+1.1)", "1.1");
    numbers.emplace("E(-1.1)", "-1.1");

    // Algorithmic numbers
    numbers.emplace("A(+1.99..)", boost::real::real(one_and_max, 1));
    numbers.emplace("A(-1.99..)", boost::real::real(one_and_max, 1, false));
    numbers.emplace("A(+1.11..)", boost::real::real(ones, 1));
    numbers.emplace("A(-1.11..)", boost::real::real(ones, 1, false));

    SECTION("sign +,+") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["A(+1.99..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["E(+1.1)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["E(+1.9)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [No, No]") {

            boost::real::real a = numbers["E(+1.1)"] - numbers["E(+1.1)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["E(+1.1)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["A(+1.99..)"] - numbers["A(+1.99..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["A(+1.11..)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["A(+1.99..)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }
    }


    SECTION("sign -,-") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["A(-1.99..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["E(-1.1)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }


        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["E(-1.9)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [No, No]") {

            boost::real::real a = numbers["E(-1.1)"] - numbers["E(-1.1)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["E(-1.1)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["A(-1.99..)"] - numbers["A(-1.99..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["A(-1.11..)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["A(-1.99..)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }
    }

    SECTION("sign -,+") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["A(+1.99..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["E(-1.1)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["E(+1.9)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [No, No]") {

            boost::real::real a = numbers["E(-1.1)"] - numbers["E(+1.1)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["E(+1.1)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["A(-1.99..)"] - numbers["A(+1.99..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["A(-1.11..)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["A(-1.99..)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }
    }


    SECTION("sign +,-") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["A(-1.99..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["E(+1.1)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["E(-1.9)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [No, No]") {

            boost::real::real a = numbers["E(+1.1)"] - numbers["E(-1.1)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["E(-1.1)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["A(+1.99..)"] - numbers["A(-1.99..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["A(+1.11..)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["A(+1.99..)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();

            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;

            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;

            ++a_it;
            
            CHECK(a_it.get_interval().lower_bound <= a_it.get_interval().upper_bound);
            CHECK(a_it.get_interval().upper_bound - a_it.get_interval().lower_bound <= length);
            length = a_it.get_interval().upper_bound - a_it.get_interval().lower_bound;
        }
    }
}
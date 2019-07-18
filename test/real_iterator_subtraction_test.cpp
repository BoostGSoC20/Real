#include <catch2/catch.hpp>
#include <map>

#include <real/real.hpp>
#include <test_helpers.hpp>


TEST_CASE("Operator - boost::real::const_precision_iterator") {

    std::map<std::string, boost::real::real<int>> numbers;

    // Explicit numbers
    numbers.emplace("E(+1.9)", "1.9");
    numbers.emplace("E(-1.9)", "-1.9");
    numbers.emplace("E(+1.1)", "1.1");
    numbers.emplace("E(-1.1)", "-1.1");

    // Algorithmic numbers
    numbers.emplace("A(+1.99..)", boost::real::real(one_and_nines, 1));
    numbers.emplace("A(-1.99..)", boost::real::real(one_and_nines, 1, false));
    numbers.emplace("A(+1.11..)", boost::real::real(ones, 1));
    numbers.emplace("A(-1.11..)", boost::real::real(ones, 1, false));

    SECTION("sign +,+") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["A(+1.99..)"];

            auto a_it = a.get_real_itr().cbegin();

            boost::real::interval expected_interval({});

            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {0};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.upper_bound.positive = false;
            expected_interval.upper_bound.exponent = -1;
            expected_interval.upper_bound.digits = {9};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {9,9};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["E(+1.1)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            // 1.1 - [1.1, 1.2]
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {0};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            // 1.1 - [1.11, 1.12]
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = -1;
            expected_interval.upper_bound.exponent = -1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            // 1.1 - [1.111, 1.112]
            expected_interval.lower_bound.exponent = -1;
            expected_interval.upper_bound.exponent = -1;
            expected_interval.lower_bound.digits = {1,2};
            expected_interval.upper_bound.digits = {1,1};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {7};
            expected_interval.upper_bound.digits = {8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {7,8};
            expected_interval.upper_bound.digits = {7,9};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {7,8,8};
            expected_interval.upper_bound.digits = {7,8,9};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["E(+1.9)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {0};
            expected_interval.upper_bound.digits = {0};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [No, No]") {

            boost::real::real a = numbers["E(+1.1)"] - numbers["E(+1.1)"];

            auto a_it = a.get_real_itr().cbegin();

            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {0};
            expected_interval.upper_bound.digits = {0};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["E(+1.1)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {8};
            expected_interval.upper_bound.digits = {8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["A(+1.99..)"] - numbers["A(+1.99..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {1};
            expected_interval.lower_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;

            expected_interval.lower_bound.exponent = -1;
            expected_interval.upper_bound.exponent = -1;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = -2;
            expected_interval.upper_bound.exponent = -2;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["A(+1.11..)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = -1;
            expected_interval.upper_bound.exponent = -1;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = -2;
            expected_interval.upper_bound.exponent = -2;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["A(+1.99..)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {7};
            expected_interval.upper_bound.digits = {9};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {8,7};
            expected_interval.upper_bound.digits = {8,9};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {8,8,7};
            expected_interval.upper_bound.digits = {8,8,9};
            CHECK(a_it.get_interval() == expected_interval);
        }
    }


    SECTION("sign -,-") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["A(-1.99..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;

            expected_interval.lower_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {0};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = -1;
            expected_interval.lower_bound.digits = {9};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {9,9};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["E(-1.1)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {0};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = -1;
            expected_interval.upper_bound.exponent = -1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {1,1};
            expected_interval.upper_bound.digits = {1,2};
            CHECK(a_it.get_interval() == expected_interval);
        }


        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {8};
            expected_interval.upper_bound.digits = {7};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {7,9};
            expected_interval.upper_bound.digits = {7,8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {7,8,9};
            expected_interval.upper_bound.digits = {7,8,8};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["E(-1.9)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {0};
            expected_interval.upper_bound.digits = {0};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [No, No]") {

            boost::real::real a = numbers["E(-1.1)"] - numbers["E(-1.1)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {0};
            expected_interval.upper_bound.digits = {0};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["E(-1.1)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {8};
            expected_interval.upper_bound.digits = {8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["A(-1.99..)"] - numbers["A(-1.99..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.digits = {1};
            expected_interval.lower_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = -1;
            expected_interval.upper_bound.exponent = -1;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = -2;
            expected_interval.upper_bound.exponent = -2;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["A(-1.11..)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.digits = {1};
            expected_interval.lower_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = -1;
            expected_interval.upper_bound.exponent = -1;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = -2;
            expected_interval.upper_bound.exponent = -2;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["A(-1.99..)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.digits = {1};
            expected_interval.lower_bound.digits = {1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {9};
            expected_interval.upper_bound.digits = {7};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {8,9};
            expected_interval.upper_bound.digits = {8,7};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {8,8,9};
            expected_interval.upper_bound.digits = {8,8,7};
            CHECK(a_it.get_interval() == expected_interval);
        }
    }

    SECTION("sign -,+") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["A(+1.99..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {4};
            expected_interval.upper_bound.digits = {2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3, 9};
            expected_interval.upper_bound.digits = {3, 8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3, 8, 9};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3, 8, 9, 9};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["E(-1.1)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {4};
            expected_interval.upper_bound.digits = {2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2, 3};
            expected_interval.upper_bound.digits = {2, 2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2, 2, 2};
            expected_interval.upper_bound.digits = {2, 2, 1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2, 2, 1, 2};
            expected_interval.upper_bound.digits = {2, 2, 1, 1};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {4};
            expected_interval.upper_bound.digits = {2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,1};
            expected_interval.upper_bound.digits = {3};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,0,2};
            expected_interval.upper_bound.digits = {3,0,1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,0,1,2};
            expected_interval.upper_bound.digits = {3,0,1,1};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["E(+1.9)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {4};
            expected_interval.upper_bound.digits = {2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,8};
            expected_interval.upper_bound.digits = {3,8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [No, No]") {

            boost::real::real a = numbers["E(-1.1)"] - numbers["E(+1.1)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {4};
            expected_interval.upper_bound.digits = {2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2};
            expected_interval.upper_bound.digits = {2,2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(-1.9)"] - numbers["E(+1.1)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {4};
            expected_interval.upper_bound.digits = {2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {3};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["A(-1.99..)"] - numbers["A(+1.99..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {4};
            expected_interval.upper_bound.digits = {2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3,8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3,9,8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3,9,9,8};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["A(-1.11..)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {4};
            expected_interval.upper_bound.digits = {2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,4};
            expected_interval.upper_bound.digits = {2,2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2,4};
            expected_interval.upper_bound.digits = {2,2,2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2,2,4};
            expected_interval.upper_bound.digits = {2,2,2,2};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["A(-1.99..)"] - numbers["A(+1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = false;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {4};
            expected_interval.upper_bound.digits = {2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,2};
            expected_interval.upper_bound.digits = {3};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,1,2};
            expected_interval.upper_bound.digits = {3,1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,1,1,2};
            expected_interval.upper_bound.digits = {3,1,1};
            CHECK(a_it.get_interval() == expected_interval);
        }
    }


    SECTION("sign +,-") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["A(-1.99..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3, 8};
            expected_interval.upper_bound.digits = {3, 9};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3, 8, 9};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3, 8, 9, 9};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["E(+1.1)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2, 2};
            expected_interval.upper_bound.digits = {2, 3};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2, 2, 1};
            expected_interval.upper_bound.digits = {2, 2, 2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2, 2, 1, 1};
            expected_interval.upper_bound.digits = {2, 2, 1, 2};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {3,1};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,0,1};
            expected_interval.upper_bound.digits = {3,0,2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,0,1,1};
            expected_interval.upper_bound.digits = {3,0,1,2};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["E(-1.9)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,8};
            expected_interval.upper_bound.digits = {3,8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [No, No]") {

            boost::real::real a = numbers["E(+1.1)"] - numbers["E(-1.1)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2};
            expected_interval.upper_bound.digits = {2,2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E(+1.9)"] - numbers["E(-1.1)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {3};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["A(+1.99..)"] - numbers["A(-1.99..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,9,8};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,9,9,8};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["A(+1.11..)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2};
            expected_interval.upper_bound.digits = {2,4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2,2};
            expected_interval.upper_bound.digits = {2,2,4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2,2,2};
            expected_interval.upper_bound.digits = {2,2,2,4};
            CHECK(a_it.get_interval() == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["A(+1.99..)"] - numbers["A(-1.11..)"];

            auto a_it = a.get_real_itr().cbegin();
            boost::real::interval expected_interval({});


            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {3,2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,1};
            expected_interval.upper_bound.digits = {3,1,2};
            CHECK(a_it.get_interval() == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,1,1};
            expected_interval.upper_bound.digits = {3,1,1,2};
            CHECK(a_it.get_interval() == expected_interval);
        }
    }
}
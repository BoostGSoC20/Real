#include <catch2/catch.hpp>
#include <map>
#include <iostream>

#include <real/real.hpp>

int one_and_nines(unsigned int n) {
    if (n == 0) {
        return 1;
    }
    return 9;
}

int ones(unsigned int n) {
    return 1;
}

TEST_CASE("Iteration of addition") {

    std::map<std::string, boost::real::real> numbers;

    // Explicit numbers
    numbers.emplace("E_+_O", "1.9");
    numbers.emplace("E_-_O", "-1.9");
    numbers.emplace("E_+", "1.1");
    numbers.emplace("E_-", "-1.1");

    // Algorithmic numbers
    numbers.emplace("A_+_O", boost::real::real(one_and_nines, 1));
    numbers.emplace("A_-_O", boost::real::real(one_and_nines, 1, false));
    numbers.emplace("A_+", boost::real::real(ones, 1));
    numbers.emplace("A_-", boost::real::real(ones, 1, false));

    SECTION("sign +,+") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E_+_O"] + numbers["A_+_O"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = true;

            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3, 8};
            expected_interval.upper_bound.digits = {3, 9};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3, 8, 9};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3, 8, 9, 9};
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["E_+"] + numbers["A_+"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = true;

            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2, 2};
            expected_interval.upper_bound.digits = {2, 3};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2, 2, 1};
            expected_interval.upper_bound.digits = {2, 2, 2};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2, 2, 1, 1};
            expected_interval.upper_bound.digits = {2, 2, 1, 2};
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E_+_O"] + numbers["E_+"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = true;

            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {3};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E_+_O"] + numbers["E_+"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = true;

            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {3};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [No, No]") {

            boost::real::real a = numbers["E_+"] + numbers["E_+"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = true;

            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2};
            expected_interval.upper_bound.digits = {2,2};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E_+_O"] + numbers["E_+_O"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = true;

            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,8};
            expected_interval.upper_bound.digits = {3,8};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["A_+_O"] + numbers["A_+"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = true;

            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3};
            expected_interval.upper_bound.digits = {3,2};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,1};
            expected_interval.upper_bound.digits = {3,1,2};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,1,1};
            expected_interval.upper_bound.digits = {3,1,1,2};
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["A_+"] + numbers["A_+"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = true;

            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2};
            expected_interval.upper_bound.digits = {2,4};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2,2};
            expected_interval.upper_bound.digits = {2,2,4};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {2,2,2,2};
            expected_interval.upper_bound.digits = {2,2,2,4};
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["A_+_O"] + numbers["A_+_O"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = true;

            expected_interval.lower_bound.digits = {2};
            expected_interval.upper_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,8};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,9,8};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {3,9,9,8};
            CHECK(a_it.approximation_interval == expected_interval);
        }
    }


    SECTION("sign -,-") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E_-_O"] + numbers["A_-_O"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = false;

            expected_interval.upper_bound.digits = {2};
            expected_interval.lower_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3, 8};
            expected_interval.lower_bound.digits = {3, 9};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3, 8, 9};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3, 8, 9, 9};
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Explicit, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["E_-"] + numbers["A_-"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = false;

            expected_interval.upper_bound.digits = {2};
            expected_interval.lower_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {2, 2};
            expected_interval.lower_bound.digits = {2, 3};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {2, 2, 1};
            expected_interval.lower_bound.digits = {2, 2, 2};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {2, 2, 1, 1};
            expected_interval.lower_bound.digits = {2, 2, 1, 2};
            CHECK(a_it.approximation_interval == expected_interval);
        }


        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E_-_O"] + numbers["E_-"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = false;

            expected_interval.upper_bound.digits = {2};
            expected_interval.lower_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3};
            expected_interval.lower_bound.digits = {3};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, No]") {

            boost::real::real a = numbers["E_-_O"] + numbers["E_-"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = false;

            expected_interval.upper_bound.digits = {2};
            expected_interval.lower_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3};
            expected_interval.lower_bound.digits = {3};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [No, No]") {

            boost::real::real a = numbers["E_-"] + numbers["E_-"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = false;

            expected_interval.upper_bound.digits = {2};
            expected_interval.lower_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {2,2};
            expected_interval.lower_bound.digits = {2,2};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Explicit, Explicit] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E_-_O"] + numbers["E_-_O"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = false;

            expected_interval.upper_bound.digits = {2};
            expected_interval.lower_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3,8};
            expected_interval.lower_bound.digits = {3,8};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, No]") {

            boost::real::real a = numbers["A_-_O"] + numbers["A_-"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = false;

            expected_interval.upper_bound.digits = {2};
            expected_interval.lower_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3};
            expected_interval.lower_bound.digits = {3,2};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3,1};
            expected_interval.lower_bound.digits = {3,1,2};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3,1,1};
            expected_interval.lower_bound.digits = {3,1,1,2};
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [No, No]") {

            boost::real::real a = numbers["A_-"] + numbers["A_-"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = false;

            expected_interval.upper_bound.digits = {2};
            expected_interval.lower_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {2,2};
            expected_interval.lower_bound.digits = {2,4};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {2,2,2};
            expected_interval.lower_bound.digits = {2,2,4};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {2,2,2,2};
            expected_interval.lower_bound.digits = {2,2,2,4};
            CHECK(a_it.approximation_interval == expected_interval);
        }

        SECTION("Type: [Algorithm, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["A_-_O"] + numbers["A_-_O"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.exponent = 1;
            expected_interval.upper_bound.positive = false;

            expected_interval.upper_bound.digits = {2};
            expected_interval.lower_bound.digits = {4};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3,8};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3,9,8};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.upper_bound.digits = {3,9,9,8};
            CHECK(a_it.approximation_interval == expected_interval);
        }
    }

    SECTION("sign -,+") {
        SECTION("Type: [Explicit, Algorithm] - overflow: [Yes, Yes]") {

            boost::real::real a = numbers["E_-_O"] + numbers["A_+_O"];

            auto a_it = a.cbegin();

            boost::real::interval expected_interval;
            expected_interval.lower_bound.positive = false;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 1;
            expected_interval.upper_bound.exponent = 1;

            expected_interval.lower_bound.digits = {1};
            expected_interval.upper_bound.digits = {1};

            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.positive = true;
            expected_interval.upper_bound.positive = true;
            expected_interval.lower_bound.exponent = 0;
            expected_interval.upper_bound.exponent = 0;
            expected_interval.lower_bound.digits = {0};
            expected_interval.upper_bound.digits = {1};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.exponent = -1;
            expected_interval.lower_bound.digits = {9};
            CHECK(a_it.approximation_interval == expected_interval);

            ++a_it;
            expected_interval.lower_bound.digits = {9,9};
            CHECK(a_it.approximation_interval == expected_interval);
        }
    }
}
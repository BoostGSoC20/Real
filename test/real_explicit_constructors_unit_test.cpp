#include <catch2/catch.hpp>
#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("Create boost::real_explicit from strings") {

    std::vector<std::string> all_signs= {"+", "-", ""};

    for (auto sign : all_signs) {

        SECTION("using the sign: " + sign) {

            std::string number_str = "";
            std::string zeros_str = "";
            bool positive = (sign != "-");

            SECTION("Test with positive integer numbers") {

                SECTION("Without zeros to take out") {

                    for (int i = 1; i < 10; i++) {
                        number_str += "1";
                        boost::real::real_explicit a(sign + number_str);
                        CHECK( a.as_string() == ((sign == "+") ? "" : sign) + number_str);
                        CHECK( a.positive() == positive );
                    }
                }

                SECTION("With zeros to take out form the right") {

                    number_str = "";
                    zeros_str = "";
                    for (int i = 1; i < 10; i++) {
                        number_str += "1";
                        zeros_str += "0";
                        boost::real::real_explicit a(sign + number_str + '.' + zeros_str);
                        CHECK( a.as_string() == ((sign == "+") ? "" : sign) + number_str);
                        CHECK( a.positive() == positive );
                    }
                }

                SECTION("With zeros to take out form the left side") {

                    number_str = "";
                    zeros_str = "";
                    for (int i = 1; i < 10; i++) {
                        number_str += "1";
                        zeros_str += "0";
                        boost::real::real_explicit a(sign + zeros_str + number_str);
                        CHECK( a.as_string() == ((sign == "+") ? "" : sign) + number_str);
                        CHECK( a.positive() == positive );
                    }
                }

                SECTION("With zeros to take out form the both sides") {

                    number_str = "";
                    zeros_str = "";
                    for (int i = 1; i < 10; i++) {
                        number_str += "1";
                        zeros_str += "0";
                        boost::real::real_explicit a(sign + zeros_str + number_str + '.' + zeros_str);
                        CHECK( a.as_string() == ((sign == "+") ? "" : sign) + number_str);
                        CHECK( a.positive() == positive );
                    }
                }

                SECTION("With exponent") {

                    number_str = "1111";
                    zeros_str = "";
                    for (int i = 0; i < 10; i++) {
                        boost::real::real_explicit a(sign + "0000" + number_str + '.' + zeros_str + 'e' + std::to_string(i));
                        CHECK( a.as_string() == ((sign == "+") ? "" : sign) + number_str + zeros_str);
                        CHECK( a.positive() == positive );
                        zeros_str += "0";
                    }
                }
            }
        }
    }

    SECTION("Invalid string") {
        //CHECK_THROWS_AS( boost::real::real_explicit a("12e23.2"));
    }
}
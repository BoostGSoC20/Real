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
                        CHECK( a.exponent() == i );
                        CHECK( a.positive() == positive );
                    }
                }

                SECTION("With zeros to take out form the right") {

                    for (int i = 1; i < 10; i++) {
                        number_str += "1";
                        zeros_str += "0";
                        boost::real::real_explicit a(sign + zeros_str + number_str);
                        CHECK( a.exponent() == i );
                        CHECK( a.positive() == positive );
                    }
                }

                SECTION("With zeros to take out form the left side") {

                    for (int i = 1; i < 10; i++) {
                        number_str += "1";
                        zeros_str += "0";
                        boost::real::real_explicit a(sign + number_str + zeros_str);
                        CHECK( a.exponent() == 2*i );
                        CHECK( a.positive() == positive );
                    }
                }

                SECTION("With zeros to take out form the both sides") {

                    for (int i = 1; i < 10; i++) {
                        number_str += "1";
                        zeros_str += "0";
                        boost::real::real_explicit a(sign + zeros_str + number_str + zeros_str);
                        CHECK( a.exponent() == 2*i );
                        CHECK( a.positive() == positive );
                    }
                }
            }


            SECTION("Positive numbers not integers") {

                SECTION("Without zeros to take out") {

                    SECTION("positive exponent") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            boost::real::real_explicit a(sign + number_str + number_str);
                            CHECK( a.exponent() == i );
                            CHECK( a.positive() == positive );
                        }
                    }

                    SECTION("exponent zero") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            boost::real::real_explicit a(sign + number_str);
                            CHECK( a.exponent() == 0 );
                            CHECK( a.positive() == positive );
                        }
                    }

                    SECTION("negative exponent") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            zeros_str += "0";
                            boost::real::real_explicit a(sign + zeros_str + number_str);
                            CHECK( a.exponent() == -i );
                            CHECK( a.positive() == positive );
                        }
                    }
                }


                SECTION("With zeros to take out from the right") {

                    SECTION("positive exponent") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            zeros_str += "0";
                            boost::real::real_explicit a(sign + number_str + number_str + zeros_str);
                            CHECK( a.exponent() == i );
                            CHECK( a.positive() == positive );
                        }
                    }

                    SECTION("exponent zero") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            zeros_str += "0";
                            boost::real::real_explicit a(sign + number_str + zeros_str);
                            CHECK( a.exponent() == 0 );
                            CHECK( a.positive() == positive );
                        }
                    }

                    SECTION("negative exponent") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            zeros_str += "0";
                            boost::real::real_explicit a(sign + zeros_str + number_str + zeros_str);
                            CHECK( a.exponent() == -i );
                            CHECK( a.positive() == positive );
                        }
                    }
                }

                SECTION("With zeros to take out from the left") {

                    SECTION("positive exponent") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            zeros_str += "0";
                            boost::real::real_explicit a(sign + zeros_str + number_str + number_str);
                            CHECK( a.exponent() == i );
                            CHECK( a.positive() == positive );
                        }
                    }

                    SECTION("exponent zero") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            zeros_str += "0";
                            boost::real::real_explicit a(sign + zeros_str + number_str);
                            CHECK( a.exponent() == 0 );
                            CHECK( a.positive() == positive );
                        }
                    }

                    SECTION("negative exponent") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            zeros_str += "0";
                            boost::real::real_explicit a(sign + zeros_str + zeros_str + number_str);
                            CHECK( a.exponent() == -i );
                            CHECK( a.positive() == positive );
                        }
                    }
                }

                SECTION("With zeros to take out from both sides") {

                    SECTION("positive exponent") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            zeros_str += "0";
                            boost::real::real_explicit a(sign + zeros_str + number_str + number_str + zeros_str);
                            CHECK( a.exponent() == i );
                            CHECK( a.positive() == positive );
                        }
                    }

                    SECTION("exponent zero") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            zeros_str += "0";
                            boost::real::real_explicit a(sign + zeros_str + number_str + zeros_str + zeros_str);
                            CHECK( a.exponent() == 0 );
                            CHECK( a.positive() == positive );
                        }
                    }

                    SECTION("negative exponent") {

                        for (int i = 1; i < 10; i++) {
                            number_str += "1";
                            zeros_str += "0";
                            boost::real::real_explicit a(sign + zeros_str + zeros_str + number_str + zeros_str);
                            CHECK( a.exponent() == -i );
                            CHECK( a.positive() == positive );
                        }
                    }
                }
            }
        }
    }
}
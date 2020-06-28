#include <catch2/catch.hpp>
#include <real/real.hpp>
#include <test_helpers.hpp>

TEMPLATE_TEST_CASE("Power", "[template]", int, long, long long) {

    using real=boost::real::real<TestType>;

    // std::map<std::string, boost::real::real<int>> algorithm_numbers;

    // algorithm_numbers.emplace("A(+100.00..)", boost::real::real(one, 3));
    // algorithm_numbers.emplace("A(+0.100..)", boost::real::real(one, 0));

    SECTION("real_explicit") {

        SECTION("Exponent = real_explicit") {

            SECTION("Integral exponents") {
                /* 20^10  */
                real a("20");
                real exp("10");
                real actual_result("10240000000000");
                real calculated_result = real::power(a, exp);

                CHECK(actual_result == calculated_result);
            }

            SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */
                /* 234^0.1  */
                real a("234");
                real exp("0.01e1");

                CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);
            }

        }

        SECTION("Exponent = real_operation") {

            SECTION("Integral exponents") {
                    
                SECTION("ADDITION") {
                    /* (5)^(8+12) */
                    real a("5");
                    real b("8");
                    real c("12");
                    real exp = b + c;
                    real actual_result("95367431640625");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);

                }

                SECTION("SUBTRACTION") {
                    /* (5)^(25-5) */
                    real a("5");
                    real b("25");
                    real c("5");
                    real exp = b - c;
                    real actual_result("95367431640625");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);

                }

                SECTION("MULTIPLICATION") {
                    /* (3*2)^20 */
                    real a("5");
                    real b("5");
                    real c("4");
                    real exp = b * c;
                    real actual_result("95367431640625");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);

                }

                SECTION("DIVISION") {
                    /* (5)^(40/2) */
                    real a("5");
                    real b("40");
                    real c("2");
                    real exp = b / c;
                    real actual_result("95367431640625");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);

                }

            }

            SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */

                SECTION("ADDITION") {
                    /* (5)^(8+1.2) */
                    real a("5");
                    real b("8");
                    real c("1.2");
                    real exp = b + c;

                    CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                }

                SECTION("SUBTRACTION") {
                    /* (5)^(25-0.5) */
                    real a("5");
                    real b("25");
                    real c("0.5");
                    real exp = b - c;

                    CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                }

                SECTION("MULTIPLICATION") {
                    /* (3*2)^20 */
                    real a("5");
                    real b("0.5");
                    real c("0.4");
                    real exp = b * c;

                    CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                }

                SECTION("DIVISION") {
                    /* (5)^(40/2) */
                    real a("5");
                    real b("0.4");
                    real c("2");
                    real exp = b / c;

                    CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                }

            }

        }

        // SECTION("Exponent = real_algorithm"){

        //     SECTION("Integral exponents") {
        //         /* 2^100  */
        //         real a("2");
        //         real exp = real(one<TestType>, 3);
        //         real actual_result("1267650600228229401496703205376");
        //         real calculated_result = real::power(a, exp);

        //         CHECK(actual_result == calculated_result);
        //     }

        //     SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */
        //         /* 234^0.1  */
        //         real a("234");
        //         real exp = real(one<TestType>, 0);

        //         CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);
        //     }

        // }

    }

    SECTION("real_operation") {

        SECTION("ADDITION") {

            SECTION("Exponent = real_explicit") {

                SECTION("Integral exponents") {
                    /* 20^10  */
                    real a = real("12") + real("8");
                    real exp("10");
                    real actual_result("10240000000000");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);
                }

                SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */
                    /* 234^0.1  */
                    real a = real("12") + real("8");
                    real exp("0.01e1");

                    CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);
                }

            }

            SECTION("Exponent = real_operation") {

                SECTION("Integral exponents") {
                        
                    SECTION("ADDITION") {
                        /* (5)^(8+12) */
                        real a = real("2") + real("3");
                        real b("8");
                        real c("12");
                        real exp = b + c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("SUBTRACTION") {
                        /* (5)^(25-5) */
                        real a = real("2") + real("3");
                        real b("25");
                        real c("5");
                        real exp = b - c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (3*2)^20 */
                        real a = real("2") + real("3");
                        real b("5");
                        real c("4");
                        real exp = b * c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("DIVISION") {
                        /* (5)^(40/2) */
                        real a = real("2") + real("3");
                        real b("40");
                        real c("2");
                        real exp = b / c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                }

                SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */

                    SECTION("ADDITION") {
                        /* (5)^(8+1.2) */
                        real a = real("2") + real("3");
                        real b("8");
                        real c("1.2");
                        real exp = b + c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("SUBTRACTION") {
                        /* (5)^(25-0.5) */
                        real a = real("2") + real("3");
                        real b("25");
                        real c("0.5");
                        real exp = b - c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (3*2)^20 */
                        real a = real("2") + real("3");
                        real b("0.5");
                        real c("0.4");
                        real exp = b * c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("DIVISION") {
                        /* (5)^(40/2) */
                        real a = real("2") + real("3");
                        real b("0.4");
                        real c("2");
                        real exp = b / c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                }

            }

            // SECTION("Exponent = real_algorithm"){

            //     SECTION("Integral exponents") {
            //         /* 2^100  */
            //         real a = real("1") + real("1");
            //         real exp = algorithm_numbers["A(+100.00..)"];
            //         real actual_result("1267650600228229401496703205376");
            //         real calculated_result = real::power(a, exp);

            //         CHECK(actual_result == calculated_result);
            //     }

            //     SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */
            //         /* 234^0.1  */
            //         real a = real("230") + real("4");
            //         real exp = algorithm_numbers["A(+0.100..)"];
            //         real actual_result("492219227058666339787776");  // 234^10
            //         real calculated_result = real::power(a, exp);

            //         CHECK_THROWS_AS(actual_result == calculated_result, boost::real::non_integral_exponent_exception);
            //     }

            // }

        }

        SECTION("SUBTRACTION") {

            SECTION("Exponent = real_explicit") {

                SECTION("Integral exponents") {
                    /* 20^10  */
                    real a = real("22") - real("2");
                    real exp("10");
                    real actual_result("10240000000000");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);
                }

                SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */
                    /* 234^0.1  */
                    real a = real("240") - real("6");
                    real exp("0.01e1");

                    CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);
                }

            }

            SECTION("Exponent = real_operation") {

                SECTION("Integral exponents") {
                        
                    SECTION("ADDITION") {
                        /* (5)^(8+12) */
                        real a = real("8") - real("3");
                        real b("8");
                        real c("12");
                        real exp = b + c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("SUBTRACTION") {
                        /* (5)^(25-5) */
                        real a = real("8") - real("3");
                        real b("25");
                        real c("5");
                        real exp = b - c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (3*2)^20 */
                        real a = real("8") - real("3");
                        real b("5");
                        real c("4");
                        real exp = b * c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("DIVISION") {
                        /* (5)^(40/2) */
                        real a = real("8") - real("3");
                        real b("40");
                        real c("2");
                        real exp = b / c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                }

                SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */

                    SECTION("ADDITION") {
                        /* (5)^(8+1.2) */
                        real a = real("8") - real("3");
                        real b("8");
                        real c("1.2");
                        real exp = b + c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("SUBTRACTION") {
                        /* (5)^(25-0.5) */
                        real a = real("8") - real("3");
                        real b("25");
                        real c("0.5");
                        real exp = b - c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (3*2)^20 */
                        real a = real("8") - real("3");
                        real b("0.5");
                        real c("0.4");
                        real exp = b * c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("DIVISION") {
                        /* (5)^(40/2) */
                        real a = real("8") - real("3");
                        real b("0.4");
                        real c("2");
                        real exp = b / c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                }

            }

            // SECTION("Exponent = real_algorithm"){

            //     SECTION("Integral exponents") {
            //         /* 2^100  */
            //         real a = real("4") - real("2");
            //         real exp = algorithm_numbers["A(+100.00..)"];
            //         real actual_result("1267650600228229401496703205376");
            //         real calculated_result = real::power(a, exp);

            //         CHECK(actual_result == calculated_result);
            //     }

            //     SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */
            //         /* 234^0.1  */
            //         real a = real("240") - real("6");
            //         real exp = algorithm_numbers["A(+0.100..)"];
            //         real actual_result("492219227058666339787776");  // 234^10
            //         real calculated_result = real::power(a, exp);

            //         CHECK_THROWS_AS(actual_result == calculated_result, boost::real::non_integral_exponent_exception);
            //     }

            // }

        }

        SECTION("MULTIPLICATION") {

            SECTION("Exponent = real_explicit") {

                SECTION("Integral exponents") {
                    /* 20^10  */
                    real a = real("5") * real("4");
                    real exp("10");
                    real actual_result("10240000000000");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);
                }

                SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */
                    /* 234^0.1  */
                    real a = real("2") * real("117");
                    real exp("0.01e1");

                    CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);
                }

            }

            SECTION("Exponent = real_operation") {

                SECTION("Integral exponents") {
                        
                    SECTION("ADDITION") {
                        /* (5)^(8+12) */
                        real a = real("5") * real("1");
                        real b("8");
                        real c("12");
                        real exp = b + c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("SUBTRACTION") {
                        /* (5)^(25-5) */
                        real a = real("5") * real("1");
                        real b("25");
                        real c("5");
                        real exp = b - c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (3*2)^20 */
                        real a = real("5") * real("1");
                        real b("5");
                        real c("4");
                        real exp = b * c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("DIVISION") {
                        /* (5)^(40/2) */
                        real a = real("5") * real("1");
                        real b("40");
                        real c("2");
                        real exp = b / c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                }

                SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */

                    SECTION("ADDITION") {
                        /* (5)^(8+1.2) */
                        real a = real("5") * real("1");
                        real b("8");
                        real c("1.2");
                        real exp = b + c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("SUBTRACTION") {
                        /* (5)^(25-0.5) */
                        real a = real("5") * real("1");
                        real b("25");
                        real c("0.5");
                        real exp = b - c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (3*2)^20 */
                        real a = real("5") * real("1");
                        real b("0.5");
                        real c("0.4");
                        real exp = b * c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("DIVISION") {
                        /* (5)^(40/2) */
                        real a = real("5") * real("1");
                        real b("0.4");
                        real c("2");
                        real exp = b / c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                }

            }

            // SECTION("Exponent = real_algorithm"){

            //     SECTION("Integral exponents") {
            //         /* 2^100  */
            //         real a = real("2") * real("1");
            //         real exp = algorithm_numbers["A(+100.00..)"];
            //         real actual_result("1267650600228229401496703205376");
            //         real calculated_result = real::power(a, exp);

            //         CHECK(actual_result == calculated_result);
            //     }

            //     SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */
            //         /* 234^0.1  */
            //         real a = real("2") * real("1");
            //         real exp = algorithm_numbers["A(+0.100..)"];
            //         real actual_result("492219227058666339787776");  // 234^10
            //         real calculated_result = real::power(a, exp);

            //         CHECK_THROWS_AS(actual_result == calculated_result, boost::real::non_integral_exponent_exception);
            //     }

            // }

        }

        SECTION("DIVISION") {

            SECTION("Exponent = real_explicit") {

                SECTION("Integral exponents") {
                    /* 20^10  */
                    real a = real("40") / real("2");
                    real exp("10");
                    real actual_result("10240000000000");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);
                }

                SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */
                    /* 234^0.1  */
                    real a = real("468") / real("2");
                    real exp("0.01e1");

                    CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);
                }

            }

            SECTION("Exponent = real_operation") {

                SECTION("Integral exponents") {
                        
                    SECTION("ADDITION") {
                        /* (5)^(8+12) */
                        real a = real("10") / real("2");
                        real b("8");
                        real c("12");
                        real exp = b + c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("SUBTRACTION") {
                        /* (5)^(25-5) */
                        real a = real("10") / real("2");
                        real b("25");
                        real c("5");
                        real exp = b - c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (3*2)^20 */
                        real a = real("10") / real("2");
                        real b("5");
                        real c("4");
                        real exp = b * c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("DIVISION") {
                        /* (5)^(40/2) */
                        real a = real("10") / real("2");
                        real b("40");
                        real c("2");
                        real exp = b / c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                }

                SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */

                    SECTION("ADDITION") {
                        /* (5)^(8+1.2) */
                        real a = real("10") / real("2");
                        real b("8");
                        real c("1.2");
                        real exp = b + c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("SUBTRACTION") {
                        /* (5)^(25-0.5) */
                        real a = real("10") / real("2");
                        real b("25");
                        real c("0.5");
                        real exp = b - c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (3*2)^20 */
                        real a = real("10") / real("2");
                        real b("0.5");
                        real c("0.4");
                        real exp = b * c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);

                    }

                    SECTION("DIVISION") {
                        /* (5)^(40/2) */
                        real a = real("10") / real("2");
                        real b("0.4");
                        real c("2");
                        real exp = b / c;

                        CHECK_THROWS_AS( real::power(a, exp), boost::real::non_integral_exponent_exception);
                    }

                }

            }

            // SECTION("Exponent = real_algorithm"){

            //     SECTION("Integral exponents") {
            //         /* 2^100  */
            //         real a = real("2") / real("1");
            //         real exp = algorithm_numbers["A(+100.00..)"];
            //         real actual_result("1267650600228229401496703205376");
            //         real calculated_result = real::power(a, exp);

            //         CHECK(actual_result == calculated_result);
            //     }

            //     SECTION("Non-Integral exponents") { /* throw non_integral_exponent_exception */
            //         /* 234^0.1  */
            //         real a = real("2") / real("1");
            //         real exp = algorithm_numbers["A(+0.100..)"];
            //         real actual_result("492219227058666339787776");  // 234^10
            //         real calculated_result = real::power(a, exp);

            //         CHECK_THROWS_AS(actual_result == calculated_result, boost::real::non_integral_exponent_exception);
            //     }

            // }

        }          

    }

}
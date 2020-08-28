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
                    /* (5)^(5*4) */
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


        }

        // SECTION("Exponent = real_algorithm"){

        //     SECTION("Integral exponents") {
        //         /* 2^5  */
        //         real a("2");
        //         real exp = real(five<TestType>, 1);
        //         real actual_result("32");
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
                    /* (12+8)^10  */
                    real a = real("12") + real("8");
                    real exp("10");
                    real actual_result("10240000000000");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);
                }

            }

            SECTION("Exponent = real_operation") {

                SECTION("Integral exponents") {
                        
                    SECTION("ADDITION") {
                        /* (2+3)^(8+12) */
                        real a = real("2") + real("3");
                        real b("8");
                        real c("12");
                        real exp = b + c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("SUBTRACTION") {
                        /* (2+3)^(25-5) */
                        real a = real("2") + real("3");
                        real b("25");
                        real c("5");
                        real exp = b - c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (2+3)^(5*4) */
                        real a = real("2") + real("3");
                        real b("5");
                        real c("4");
                        real exp = b * c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("DIVISION") {
                        /* (2+3)^(40/2) */
                        real a = real("2") + real("3");
                        real b("40");
                        real c("2");
                        real exp = b / c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

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
                    /* (22-2)^10  */
                    real a = real("22") - real("2");
                    real exp("10");
                    real actual_result("10240000000000");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);
                }

            }

            SECTION("Exponent = real_operation") {

                SECTION("Integral exponents") {
                        
                    SECTION("ADDITION") {
                        /* (8-3)^(8+12) */
                        real a = real("8") - real("3");
                        real b("8");
                        real c("12");
                        real exp = b + c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("SUBTRACTION") {
                        /* (8-3)^(25-5) */
                        real a = real("8") - real("3");
                        real b("25");
                        real c("5");
                        real exp = b - c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (8-3)^20 */
                        real a = real("8") - real("3");
                        real b("5");
                        real c("4");
                        real exp = b * c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("DIVISION") {
                        /* (8-3)^(40/2) */
                        real a = real("8") - real("3");
                        real b("40");
                        real c("2");
                        real exp = b / c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

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
                    /* (5*4)^10  */
                    real a = real("5") * real("4");
                    real exp("10");
                    real actual_result("10240000000000");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);
                }

            }

            SECTION("Exponent = real_operation") {

                SECTION("Integral exponents") {
                        
                    SECTION("ADDITION") {
                        /* (5*1)^(8+12) */
                        real a = real("5") * real("1");
                        real b("8");
                        real c("12");
                        real exp = b + c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("SUBTRACTION") {
                        /* ((5*1))^(25-5) */
                        real a = real("5") * real("1");
                        real b("25");
                        real c("5");
                        real exp = b - c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("MULTIPLICATION") {
                        /* ((5*1))^20 */
                        real a = real("5") * real("1");
                        real b("5");
                        real c("4");
                        real exp = b * c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("DIVISION") {
                        /* ((5*1))^(40/2) */
                        real a = real("5") * real("1");
                        real b("40");
                        real c("2");
                        real exp = b / c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

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
                    /* (40/2)^10  */
                    real a = real("40") / real("2");
                    real exp("10");
                    real actual_result("10240000000000");
                    real calculated_result = real::power(a, exp);

                    CHECK(actual_result == calculated_result);
                }

            }

            SECTION("Exponent = real_operation") {

                SECTION("Integral exponents") {
                        
                    SECTION("ADDITION") {
                        /* (10/2)^(8+12) */
                        real a = real("10") / real("2");
                        real b("8");
                        real c("12");
                        real exp = b + c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("SUBTRACTION") {
                        /* (10/2)^(25-5) */
                        real a = real("10") / real("2");
                        real b("25");
                        real c("5");
                        real exp = b - c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("MULTIPLICATION") {
                        /* (10/2)^20 */
                        real a = real("10") / real("2");
                        real b("5");
                        real c("4");
                        real exp = b * c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

                    }

                    SECTION("DIVISION") {
                        /* (10/2)^(40/2) */
                        real a = real("10") / real("2");
                        real b("40");
                        real c("2");
                        real exp = b / c;
                        real actual_result("95367431640625");
                        real calculated_result = real::power(a, exp);

                        CHECK(actual_result == calculated_result);

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

// Non-integral power test is not made template test case, it is taking too much time to test it on all template test cases
TEST_CASE("Non-Integral Power"){
    using real = boost::real::real<int>;
    SECTION("Positive Non-Integral Powers"){
        real a("20");
        real b("1.5");
        real c = real::power(a,b); // 20^1.5 = 89.4427191
        real lower_bound("89.4427190");
        real upper_bound("89.4427192");
        CHECK(c > lower_bound);
        CHECK(c < upper_bound);

        b = real("0.5");
        c = real::power(a,b); // 20^0.5 = 4.472135955
        lower_bound = real("4.472135954");
        upper_bound = real("4.472135956");
        CHECK(c > lower_bound);
        CHECK(c < upper_bound);
    }

    SECTION("Negative Non-Integral Powers"){
        real a("20");
        real b("-1.5");
        real c = real::power(a,b); // 20^(-1.5) = 0.0111803399
        real lower_bound = real("0.0111803398");
        real upper_bound = real("0.01118034");
        CHECK(c > lower_bound);
        CHECK(c < upper_bound);

        b = real("-0.5");
        c = real::power(a,b);  // 20^(-0.5) = 0.2236067977
        lower_bound = real("0.2236067976");
        upper_bound = real("0.2236067978");
        CHECK(c > lower_bound);
        CHECK(c < upper_bound);
    }

    SECTION("POWER IS AN OPERATION"){
        SECTION("POWER IS ADDITION OPERATION(A+B)"){
            real a("1.23");
            real b("3.58");
            real power = a + b; // 1.23 + 3.58 = 4.81
            real number("4.39");

            real result = real::power(number, power); // 4.39^4.81 = 1230.989482509448115
            real lower_bound("1230.989482509448114");
            real upper_bound("1230.989482509448116");
            CHECK(result > lower_bound);
            CHECK(result < upper_bound);
        }

        SECTION("POWER IS SUBTRACTION OPERATION(A-B)"){
            real a("1.23");
            real b("3.58");
            real power = b - a; // 3.58 - 1.23 = 2.35
            real number("4.39");

            real result = real::power(number, power); // 4.39^2.35 = 32.343843174550343
            real lower_bound("32.343843174550342");
            real upper_bound("32.343843174550344");
            CHECK(result > lower_bound);
            CHECK(result < upper_bound);
        }

        SECTION("POWER IS MULTIPLICATION OPERATION(A*B)"){
            real a("1.23");
            real b("3.58");
            real power = a * b; // 1.23 * 3.58 = 4.4034
            real number("4.39");

            real result = real::power(number, power); // 4.39^4.4034 = 674.571934476649233
            real lower_bound("674.571934476649232");
            real upper_bound("674.571934476649234");
            CHECK(result > lower_bound);
            CHECK(result < upper_bound);
        }

        SECTION("POWER IS DIVISION OPERATION(A/B)"){
            real a("1.23");
            real b("3.58");
            real power = a / b; // 1.23 / 3.58 = 0.343575418994413
            real number("4.39");

            real result = real::power(number, power); // 4.39^0.343575418994413 = 1.662398034486293
            real lower_bound("1.6623980344861");
            real upper_bound("1.6623980344863");
            CHECK(result > lower_bound);
            CHECK(result < upper_bound);
        }
    }


    SECTION("NUMBER IS AN OPERATION"){
        SECTION("NUMBER IS ADDITION OPERATION(A+B)"){
            real a("1.23");
            real b("3.58");
            real number = a + b; // 1.23 + 3.58 = 4.81
            real power("4.39");

            real result = real::power(number, power); // 4.81^4.39 = 987.681422883435912
            real lower_bound("987.681422883435911");
            real upper_bound("987.681422883435913");
            CHECK(result > lower_bound);
            CHECK(result < upper_bound);
        }

        SECTION("NUMBER IS SUBTRACTION OPERATION(A-B)"){
            real a("1.23");
            real b("3.58");
            real number = b - a; // 3.58 - 1.23 = 2.35
            real power("4.39");

            real result = real::power(number, power); // 2.35^4.39 = 42.558657064721475
            real lower_bound("42.558657064721474");
            real upper_bound("42.558657064721476");
            CHECK(result > lower_bound);
            CHECK(result < upper_bound);
        }

        SECTION("NUMBER IS MULTIPLICATION OPERATION(A*B)"){
            real a("1.23");
            real b("3.58");
            real number = a * b; // 1.23 * 3.58 = 4.4034
            real power("4.39");

            real result = real::power(number, power); // 4.4034^4.39 = 670.239356710538598
            real lower_bound("670.239356710538597");
            real upper_bound("670.239356710538599");
            CHECK(result > lower_bound);
            CHECK(result < upper_bound);
        }

        SECTION("NUMBER IS DIVISION OPERATION(A/B)"){
            real a("1.23");
            real b("3.58");
            real number = a / b; // 1.23 / 3.58 = 0.343575418994413
            real power("4.39");

            real result = real::power(number, power); // 0.343575418994413 ^ 4.39 = 0.009186222330203
            real lower_bound("0.0091862223301");
            real upper_bound("0.0091862223303");
            CHECK(result > lower_bound);
            CHECK(result < upper_bound);
        }


    }

    SECTION("BOTH NUMBER AND POWER ARE OPERATION"){
        real a("1.34");
        real b("3.26");
        real c("8.43");
        real d("0.38");
        real number = a + b; // 1.34 + 3.26 = 4.6
        real power = c * d;  // 8.43 * 0.38 = 3.2034

        real result = real::power(number, power); // 4.6 ^ 3.2034 = 132.763422034566691
        real lower_bound("132.763422034566690");
        real upper_bound("132.763422034566692");
        CHECK(result > lower_bound);
        CHECK(result < upper_bound);
    }
}
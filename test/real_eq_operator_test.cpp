#include <catch2/catch.hpp>
#include <real/real.hpp>
#include <test_helpers.hpp>

using real=boost::real::real<>;

TEST_CASE("Operator ==") {

    SECTION("a == b") {

        SECTION("without precision exception") {
            SECTION("Explicit == Explicit") {
                real a("1.5");
                real b("1.5");

                CHECK(a == b);
            }

            SECTION("Explicit == Addition") {
                real a("1");
                real b("0.5");
                real c("0.5");
                real d = b + c;

                CHECK(a == d); 
            }

            SECTION("Explicit == Subtraction") {
                real a("1");
                real b("1.5");
                real c("0.5");
                real d = b - c;

                CHECK(a == d);
            }

            SECTION("Explicit == multiplication") {
                real a("4");
                real b("2");
                real c("2");
                real d = b * c;

                CHECK(a == d);
            }

            SECTION("Addition == Explicit") {
                real a("1.5");
                real b("1.5");
                real c = a + b;
                real d("3");

                CHECK(c == d);
            }

            SECTION("Addition == Addition") {
                real a("1.5");
                real b("1.5");
                real c = a + b;
                real d = a + b;

                CHECK(c == d);
            }

            SECTION("Addition == Subtraction") {
                real a("1.5");
                real b("1.5");
                real c = a + b;
                real d("3.5");
                real e("0.5");
                real f = d - e;

                CHECK(c == f);
            }

            SECTION("Addition == multiplication") {
                real a("1.5");
                real b("1.5");
                real c = a + b;
                real d("1.5");
                real e("2");
                real f = d * e;

                CHECK(c == f);
            }

            SECTION("Subtraction == Explicit") {
                real a("1.5");
                real b("1.5");
                real c = a - b;
                real d("0");

                CHECK(c == d);
            }

            SECTION("Subtraction == Subtraction") {
                real a("1.5");
                real b("1.5");
                real c = a - b;
                real d = a - b;

                CHECK(c == d);
            }

            SECTION("Subtraction == multiplication") {
                real a("1.5");
                real b("1.5");
                real c = a - b;
                real d("0");
                real e = a * d;

                CHECK(c == e);
            }

            SECTION("multiplication == Explicit") {
                real a("1.5");
                real b("2");
                real c = a * b;
                real d("3");

                CHECK(c == d);
            }

            SECTION("multiplication == Addition") {
                real a("1.5");
                real b("2");
                real c = a * b;
                real d = a + a;

                CHECK(c == d);
            }

            SECTION("multiplication == Subtraction") {
                real a("1.5");
                real b("2");
                real c = a * b;
                real d("-1");
                real e = b - d;

                CHECK(c == e);
            }

            SECTION("multiplication == multiplication") {
                real a("1.5");
                real b("2");
                real c = a * b;
                real d = a * b;

                CHECK(c == d);
            }
        }




        SECTION("With precision exception") {
            SECTION("Explicit == Explicit") {
                real a("1.555555555555555555");
                real b("1.555555555555555555");

                CHECK_THROWS_AS(a == b, boost::real::precision_exception);
            }

            SECTION("Explicit == Addition") {
                real a("22222222222220000000000");
                real b("11111111111110000000000");
                real c("11111111111110000000000");
                real d = b + c;

                CHECK(a == d);
            }

            SECTION("Explicit == Subtraction") {
                real a("22222222222222222222");
                real b("22222222222222222223");
                real c("1");
                real d = b - c;

                CHECK(a == d);
            }

            SECTION("Explicit == multiplication") {
                real a("22222222222220000000000");
                real b("11111111111110000000000");
                real c("2");
                real d = b * c;

                CHECK(a == d);
            }

            SECTION("Addition == Explicit") {
                real a("1.1111111111111");
                real b("1.1111111111111");
                real c = a + b;
                real d("2.2222222222222");

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }

            SECTION("Addition == Addition") {
                real a("1.1111111111111");
                real b("1.1111111111111");
                real c = a + b;
                real d = a + b;

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }

            SECTION("Addition == Subtraction") {
                real a("1.1111111111111");
                real b("1.1111111111111");
                real c = a + b;
                real d("2.2222222222223");
                real e("0.0000000000001");
                real f = d - e;

                CHECK_THROWS_AS(c == f, boost::real::precision_exception);
            }

            SECTION("Addition == multiplication") {
                real a("1.1111111111111");
                real b("1.1111111111111");
                real c = a + b;
                real d("2");
                real e = a * d;

                CHECK_THROWS_AS(c == e, boost::real::precision_exception);
            }

            SECTION("Subtraction == Explicit") {
                real a("1.1111111111112");
                real b("0.0000000000001");
                real c = a - b;
                real d("1.1111111111111");

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }

            SECTION("Subtraction == Addition") {
                real a("1.1111111111112");
                real b("0.0000000000001");
                real c = a - b;
                real d("-0.0000000000001");
                real e = a + d;

                CHECK_THROWS_AS(c == e, boost::real::precision_exception);
            }

            SECTION("Subtraction == Subtraction") {
                real a("1.1111111111112");
                real b("0.0000000000001");
                real c = a - b;
                real d = a - b;

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }

            SECTION("Subtraction == multiplication") {
                real a("1.1111111111112");
                real b("0.0000000000001");
                real c = a - b;
                real d("1.1111111111111");
                real e("1");
                real f = d * e;

                CHECK_THROWS_AS(c == f, boost::real::precision_exception);
            }

            SECTION("multiplication == Explicit") {
                real a("1.1111111111111");
                real b("2");
                real c = a * b;
                real d("2.2222222222222");

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }

            SECTION("multiplication == Addition") {
                real a("1.1111111111111");
                real b("2");
                real c = a * b;
                real d = a + a;

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }

            SECTION("multiplication == Subtraction") {
                real a("1.1111111111111");
                real b("2");
                real c = a * b;
                real d("2.2222222222223");
                real e("0.0000000000002");
                real f = d - e;

                CHECK_FALSE(c == f);
            }

            SECTION("multiplication == multiplication") {
                real a("1.1111111111111");
                real b("2");
                real c = a * b;
                real d = a * b;

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }
        }
    }



    SECTION("a < b") {

        SECTION("without precision exception") {
            SECTION("Explicit == Explicit") {
                real a("1");
                real b("1.5");

                CHECK_FALSE(a == b);
            }

            SECTION("Explicit == Addition") {
                real a("1");
                real b("0.5");
                real c("1");
                real d = b + c;

                CHECK_FALSE(a == d);
            }

            SECTION("Explicit == Subtraction") {
                real a("1");
                real b("1.5");
                real c("0.2");
                real d = b - c;

                CHECK_FALSE(a == d);
            }

            SECTION("Explicit == multiplication") {
                real a("3");
                real b("2");
                real c("2");
                real d = b * c;

                CHECK_FALSE(a == d);
            }

            SECTION("Addition == Explicit") {
                real a("1.5");
                real b("1.5");
                real c = a + b;
                real d("4");

                CHECK_FALSE(c == d);
            }

            SECTION("Addition == Addition") {
                real a("1.5");
                real b("1");
                real c = a + b;
                real d = a + a;

                CHECK_FALSE(c == d);
            }

            SECTION("Addition == Subtraction") {
                real a("1.5");
                real b("1");
                real c = a + b;
                real d("3.5");
                real e("0.5");
                real f = d - e;

                CHECK_FALSE(c == f);
            }

            SECTION("Addition == multiplication") {
                real a("1.5");
                real b("1.5");
                real c = a + b;
                real d("2");
                real e("2");
                real f = d * e;

                CHECK_FALSE(c == f);
            }

            SECTION("Subtraction == Explicit") {
                real a("1.5");
                real b("1.5");
                real c = a - b;
                real d("1");

                CHECK_FALSE(c == d);
            }

            SECTION("Subtraction == Addition") {
                real a("1.5");
                real b("1.5");
                real c = a - b;
                real d("1.5");
                real e = a + d;

                CHECK_FALSE(c == e);
            }

            SECTION("Subtraction == Subtraction") {
                real a("1.5");
                real b("1");
                real c = a - a;
                real d = a - b;

                CHECK_FALSE(c == d);
            }

            SECTION("Subtraction == multiplication") {
                real a("1.5");
                real b("1.5");
                real c = a - b;
                real d = a * b;

                CHECK_FALSE(c == d);
            }

            SECTION("multiplication == Explicit") {
                real a("1.5");
                real b("2");
                real c = a * b;
                real d("4");

                CHECK_FALSE(c == d);
            }

            SECTION("multiplication == Addition") {
                real a("1.5");
                real b("2");
                real c = a * b;
                real d = a + b;

                CHECK_FALSE(c == d);
            }

            SECTION("multiplication == Subtraction") {
                real a("1.5");
                real b("2");
                real c = a * b;
                real d("5");
                real e = d - a;

                CHECK_FALSE(c == e);
            }

            SECTION("multiplication == multiplication") {
                real a("1.5");
                real b("2");
                real c = a * b;
                real d = b * b;

                CHECK_FALSE(c == d);
            }
        }



        SECTION("With precision exception") {

            SECTION("Explicit == Explicit") {
                real a("1.555555555555555550");
                real b("1.55555555555555555");

                CHECK_THROWS_AS(a == b, boost::real::precision_exception);
            }

            SECTION("Explicit == Addition") {
                real a("22222222222220000000000");
                real b("11111111111110000000000");
                real c("11111111111110000000000");
                real d = b + c;

                CHECK(a == d);
            }

            SECTION("Explicit == Subtraction") {
                real a("22222222222222222222");
                real b("22222222222222222224");
                real c("1");
                real d = b - c;

                CHECK_FALSE(a == d);
            }

            SECTION("Explicit == multiplication") {
                real a("22222222222210000000000");
                real b("11111111111110000000000");
                real c("2");
                real d = b * c;

                CHECK_FALSE(a == d);
            }

            SECTION("Addition == Explicit") {
                real a("1.1111111111110");
                real b("1.1111111111111");
                real c = a + b;
                real d("2.2222222222222");

                CHECK_FALSE(c == d);
            }

            SECTION("Addition == Addition") {
                real a("1.1111111111110");
                real b("1.1111111111111");
                real c = a + b;
                real d = a + b;

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }

            SECTION("Addition == Subtraction") {
                real a("1.1111111111110");
                real b("1.1111111111112");
                real c = a + b;
                real d("2.2222222222223");
                real e("0.0000000000001");
                real f = d - e;

                CHECK_THROWS_AS(c == f, boost::real::precision_exception);
            }

            SECTION("Addition == multiplication") {
                real a("1.1111111111111");
                real b("1.1111111111111");
                real c = a + b;
                real d("2");
                real e = a * d;

                CHECK_THROWS_AS(c == e, boost::real::precision_exception);
            }

            SECTION("Subtraction == Explicit") {
                real a("1.1111111111111");
                real b("0.0000000000001");
                real c = a - b;
                real d("1.1111111111111");

                CHECK_FALSE(c == d);
            }

            SECTION("Subtraction == Addition") {
                real a("1.1111111111111");
                real b("0.0000000000001");
                real c = a - b;
                real d("-0.0000000000001");
                real e = a + d;

                CHECK_THROWS_AS(c == e, boost::real::precision_exception);
            }

            SECTION("Subtraction == Subtraction") {
                real a("1.1111111111111");
                real b("0.0000000000001");
                real c = a - b;
                real d = a - b;

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }

            SECTION("Subtraction == multiplication") {
                real a("1.1111111111111");
                real b("0.0000000000001");
                real c = a + b;
                real d("1.1111111111111");
                real e("1");
                real f = d * e;

                CHECK_FALSE(c == f);
            }

            SECTION("multiplication == Explicit") {
                real a("1.111111111111");
                real b("2");
                real c = a * b;
                real d("2.2222222222222");

                CHECK_FALSE(c == d);
            }

            SECTION("multiplication == Addition") {
                real a("1.111111111111");
                real b("2");
                real c = a * b;
                real d = a + a;

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }

            SECTION("multiplication == Subtraction") {
                real a("1.111111111111");
                real b("2");
                real c = a * b;
                real d("2.2222222222223");
                real e("0.0000000000001");
                real f = d - e;

                CHECK_FALSE(c == f);
            }

            SECTION("multiplication == multiplication") {
                real a("1.111111111111");
                real b("2");
                real c = a * b;
                real d = a * b;

                CHECK_THROWS_AS(c == d, boost::real::precision_exception);
            }
        }

    }

    SECTION("a > b") {

        SECTION("without precision exception") {
            SECTION("Explicit == Explicit") {
                real a("2");
                real b("1.5");

                CHECK_FALSE(a == b);
            }

            SECTION("Explicit == Addition") {
                real a("1.5");
                real b("0.5");
                real c("0.5");
                real d = b + c;

                CHECK_FALSE(a == d);
            }

            SECTION("Explicit == Subtraction") {
                real a("1.5");
                real b("1.5");
                real c("0.5");
                real d = b - c;

                CHECK_FALSE(a == d);
            }

            SECTION("Explicit == multiplication") {
                real a("5");
                real b("2");
                real c("2");
                real d = b * c;

                CHECK_FALSE(a == d);
            }

            SECTION("Addition == Explicit") {
                real a("2");
                real b("1.5");
                real c = a + b;
                real d("3");

                CHECK_FALSE(c == d);
            }

            SECTION("Addition == Addition") {
                real a("1.5");
                real b("2");
                real c = a + b;
                real d = a + a;

                CHECK_FALSE(c == d);
            }

            SECTION("Addition == Subtraction") {
                real a("1.5");
                real b("1.5");
                real c = a + b;
                real d("3.5");
                real e("1");
                real f = d - e;

                CHECK_FALSE(c == f);
            }

            SECTION("Addition == multiplication") {
                real a("1.5");
                real b("2");
                real c = a + b;
                real d("1.5");
                real e("2");
                real f = d * e;

                CHECK_FALSE(c == f);
            }

            SECTION("Subtraction == Explicit") {
                real a("1.5");
                real b("1");
                real c = a - b;
                real d("0");

                CHECK_FALSE(c == d);
            }

            SECTION("Subtraction == Addition") {
                real a("1.5");
                real b("1");
                real c = a - b;
                real d("-1.5");
                real e = a + d;

                CHECK_FALSE(c == e);
            }

            SECTION("Subtraction == Subtraction") {
                real a("1.5");
                real b("1");
                real c = a - b;
                real d = a - a;

                CHECK_FALSE(c == d);
            }

            SECTION("Subtraction == multiplication") {
                real a("1.5");
                real b("1");
                real c = a - b;
                real d("0");
                real e = a * d;

                CHECK_FALSE(c == e);
            }

            SECTION("multiplication == Explicit") {
                real a("2");
                real b("2");
                real c = a * b;
                real d("3");

                CHECK_FALSE(c == d);
            }

            SECTION("multiplication == Addition") {
                real a("3");
                real b("2");
                real c = a * b;
                real d = a + b;

                CHECK_FALSE(c == d);
            }

            SECTION("multiplication == Subtraction") {
                real a("1.5");
                real b("2");
                real c = a * b;
                real d("0.5");
                real e = b - d;

                CHECK_FALSE(c == e);
            }

            SECTION("multiplication == multiplication") {
                real a("1.5");
                real b("2");
                real c = a * b;
                real d = a * a;

                CHECK_FALSE(c == d);
            }
        }



        SECTION("With precision exception") {
            SECTION("Explicit == Explicit") {
                real a("1.555555555555555555");
                real b("1.5555555555555555");

                CHECK_FALSE(a == b);
            }

            SECTION("Explicit == Addition") {
                real a("22222222222222220000000");
                real b("11111111111110000000000");
                real c("11111111111110000000000");
                real d = b + c;

                CHECK_FALSE(a == d);
            }

            SECTION("Explicit == Subtraction") {
                real a("22222222222222222222");
                real b("22222222222222222222");
                real c("1");
                real d = b - c;

                CHECK_FALSE(a == d);
            }

            SECTION("Explicit == multiplication") {
                real a("22222222222222220000000");
                real b("11111111111110000000000");
                real c("2");
                real d = b * c;

                CHECK_FALSE(a == d);
            }

            SECTION("Addition == Explicit") {
                real a("1.1111111111111222");
                real b("1.1111111111111222");
                real c = a + b;
                real d("2.2222222222222");

                CHECK_FALSE(c == d);
            }

            SECTION("Addition == Addition") {
                real a("1.1111111111111222");
                real b("1.1111111111111");
                real c = a + a;
                real d = b + b;

                CHECK_FALSE(c == d);
            }

            SECTION("Addition == Subtraction") {
                real a("1.1111111111111111");
                real b("1.1111111111111222");
                real c = a + b;
                real d("2.2222222222223");
                real e("0.0000000000001");
                real f = d - e;

                CHECK_FALSE(c == f);
            }

            SECTION("Addition == multiplication") {
                real a("1.1111111111111");
                real b("1.1111111111111222");
                real c = a + b;
                real d("2");
                real e = a * d;

                CHECK_FALSE(c == e);
            }

            SECTION("Subtraction == Explicit") {
                real a("1.111111111111222");
                real b("0.000000000000001");
                real c = a - b;
                real d("1.1111111111111");

                CHECK_FALSE(c == d);
            }

            SECTION("Subtraction == Addition") {
                real a("1.1111111111115");
                real b("0.0000000000001");
                real c = a - b;
                real d("-0.0000000000003");
                real e = a + d;

                CHECK_FALSE(c == e);
            }

            SECTION("Subtraction == Subtraction") {
                real a("1.1111111111114");
                real b("0.0000000000001");
                real c = a - b;
                real d("0.0000000000003");
                real e = a - d;

                CHECK_FALSE(c == e);
            }

            SECTION("Subtraction == multiplication") {
                real a("1.1111111111112222");
                real b("0.0000000000001");
                real c = a - b;
                real d("1.1111111111111");
                real e("1");
                real f = d * e;

                CHECK_FALSE(c == f);
            }

            SECTION("multiplication == Explicit") {
                real a("1.1111111111111222");
                real b("2");
                real c = a * b;
                real d("2.2222222222222");

                CHECK_FALSE(c == d);
            }

            SECTION("multiplication == Addition") {
                real a("1.1111111111111");
                real b("2");
                real c = a * b;
                real d("1.1111111111100");
                real e = a + d;

                CHECK_FALSE(c == e);
            }

            SECTION("multiplication == Subtraction") {
                real a("1.1111111111111");
                real b("2");
                real c = a * b;
                real d("2.2222222222221");
                real e("0.0000000000001");
                real f = d - e;

                CHECK_FALSE(c == f);
            }

            SECTION("multiplication == multiplication") {
                real a("1.11111111111112");
                real b("2");
                real c = a * b;
                real d("1.1111111111111");
                real e = d * b;
                CHECK_FALSE(c == e);
            }
        }
    }

    SECTION("Testing UDL") {
        SECTION("explicit == explicit") {
            SECTION("integer == integer") {
                auto a = 123_r;
                auto b = 123_r;

                CHECK(a == b);
            }

            SECTION("integer == double") {
                auto a = 123_r;
                auto b = 123.00_r;

                CHECK(a == b);
            }

            SECTION("double == double") {
                auto a = 1234.5_r;
                auto b = 1234.5_r;

                CHECK(a == b);
            }

            SECTION("string == integer") {
                auto a = "123"_r;
                auto b = 123_r;

                CHECK(a == b);
            }

            SECTION("string == string") {
                auto a = "123"_r;
                auto b = "123"_r;

                CHECK(a == b);
            }

            SECTION("string with exponent == double") {
                auto a = "12345e-1"_r;
                auto b = 1234.5_r;

                CHECK(a == b);
            }

            SECTION("trailing zeroes == without trailing zeroes") {

                SECTION("Without exponent") {
                    auto a = "12300.00"_r;
                    auto b = 12300_r;

                    CHECK(a == b);
                }
                SECTION("With exponent") {
                    auto a = "1230000.00e-2"_r;
                    auto b = 12300_r;

                    CHECK(a == b);
                }
            }
        }
    }
}
#include <catch2/catch.hpp>
#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("Operator <") {

    SECTION("a == b") {

        SECTION("without precision exception") {
            SECTION("Explicit < Explicit") {
                boost::real::real a("1.5");
                boost::real::real b("1.5");

                CHECK_FALSE(a < b);
            }

            SECTION("Explicit < Addition") {
                boost::real::real a("1");
                boost::real::real b("0.5");
                boost::real::real c("0.5");
                boost::real::real d = b + c;

                CHECK_FALSE(a < d);
            }

            SECTION("Explicit < Subtraction") {
                boost::real::real a("1");
                boost::real::real b("1.5");
                boost::real::real c("0.5");
                boost::real::real d = b - c;

                CHECK_FALSE(a < d);
            }

            SECTION("Explicit < multiplication") {
                boost::real::real a("4");
                boost::real::real b("2");
                boost::real::real c("2");
                boost::real::real d = b * c;

                CHECK_FALSE(a < d);
            }

            SECTION("Addition < Explicit") {
                boost::real::real a("1.5");
                boost::real::real b("1.5");
                boost::real::real c = a + b;
                boost::real::real d("3");

                CHECK_FALSE(c < d);
            }

            SECTION("Addition < Addition") {
                boost::real::real a("1.5");
                boost::real::real b("1.5");
                boost::real::real c = a + b;
                boost::real::real d = a + b;

                CHECK_FALSE(c < d);
            }

            SECTION("Addition < Subtraction") {
                boost::real::real a("1.5");
                boost::real::real b("1.5");
                boost::real::real c = a + b;
                boost::real::real d("3.5");
                boost::real::real e("0.5");
                boost::real::real f = d - e;

                CHECK_FALSE(c < f);
            }

            SECTION("Addition < multiplication") {
                boost::real::real a("1.5");
                boost::real::real b("1.5");
                boost::real::real c = a + b;
                boost::real::real d("1.5");
                boost::real::real e("2");
                boost::real::real f = d * e;

                CHECK_FALSE(c < f);
            }

            SECTION("Subtraction < Explicit") {
                boost::real::real a("1.5");
                boost::real::real b("1.5");
                boost::real::real c = a - b;
                boost::real::real d("0");

                CHECK_FALSE(c < d);
            }

            SECTION("Subtraction < Addition") {
                boost::real::real a("1.5");
                boost::real::real b("1.5");
                boost::real::real c = a - b;
                boost::real::real d("-1.5");
                boost::real::real e = a + d;

                CHECK_FALSE(c < e);
            }

            SECTION("Subtraction < Subtraction") {
                boost::real::real a("1.5");
                boost::real::real b("1.5");
                boost::real::real c = a - b;
                boost::real::real d = a - b;

                CHECK_FALSE(c < d);
            }

            SECTION("Subtraction < multiplication") {
                boost::real::real a("1.5");
                boost::real::real b("1.5");
                boost::real::real c = a + b;
                boost::real::real d("2");
                boost::real::real e = a * d;

                CHECK_FALSE(c < e);
            }

            SECTION("multiplication < Explicit") {
                boost::real::real a("1.5");
                boost::real::real b("2");
                boost::real::real c = a * b;
                boost::real::real d("3");

                CHECK_FALSE(c < d);
            }

            SECTION("multiplication < Addition") {
                boost::real::real a("1.5");
                boost::real::real b("2");
                boost::real::real c = a * b;
                boost::real::real d = a + a;

                CHECK_FALSE(c < d);
            }

            SECTION("multiplication < Subtraction") {
                boost::real::real a("1.5");
                boost::real::real b("2");
                boost::real::real c = a * b;
                boost::real::real d("0.5");
                boost::real::real e = b - d;

                CHECK_FALSE(c < e);
            }

            SECTION("multiplication < multiplication") {
                boost::real::real a("1.5");
                boost::real::real b("2");
                boost::real::real c = a * b;
                boost::real::real d = a * b;

                CHECK_FALSE(c < d);
            }
        }




        SECTION("With precision exception") {
            SECTION("Explicit < Algorithm") {
                boost::real::real a("1.11");
                boost::real::real b(one_one_one, 1);

                CHECK_THROWS_AS(a < b, boost::real::precision_exception);
            }

            SECTION("Explicit < Explicit") {
                boost::real::real a("1.555555555555555555");
                boost::real::real b("1.555555555555555555");

                CHECK_THROWS_AS(a < b, boost::real::precision_exception);
            }

            SECTION("Explicit < Addition") {
                boost::real::real a("22222222222220000000000");
                boost::real::real b("11111111111110000000000");
                boost::real::real c("11111111111110000000000");
                boost::real::real d = b + c;

                CHECK_THROWS_AS(a < d, boost::real::precision_exception);
            }

            SECTION("Explicit < Subtraction") {
                boost::real::real a("22222222222222222222");
                boost::real::real b("22222222222222222223");
                boost::real::real c("1");
                boost::real::real d = b - c;

                CHECK_THROWS_AS(a < d, boost::real::precision_exception);
            }

            SECTION("Explicit < multiplication") {
                boost::real::real a("22222222222220000000000");
                boost::real::real b("11111111111110000000000");
                boost::real::real c("2");
                boost::real::real d = b * c;

                CHECK_THROWS_AS(a < d, boost::real::precision_exception);
            }

            SECTION("Addition < Explicit") {
                boost::real::real a("1.1111111111111");
                boost::real::real b("1.1111111111111");
                boost::real::real c = a + b;
                boost::real::real d("2.2222222222222");

                CHECK_THROWS_AS(c < d, boost::real::precision_exception);
            }

            SECTION("Addition < Addition") {
                boost::real::real a("1.1111111111111");
                boost::real::real b("1.1111111111111");
                boost::real::real c = a + b;
                boost::real::real d = a + b;

                CHECK_THROWS_AS(c < d, boost::real::precision_exception);
            }

            SECTION("Addition < Subtraction") {
                boost::real::real a("1.1111111111111");
                boost::real::real b("1.1111111111111");
                boost::real::real c = a + b;
                boost::real::real d("2.2222222222223");
                boost::real::real e("0.0000000000001");
                boost::real::real f = d - e;

                CHECK_THROWS_AS(c < f, boost::real::precision_exception);
            }

            SECTION("Addition < multiplication") {
                boost::real::real a("1.1111111111111");
                boost::real::real b("1.1111111111111");
                boost::real::real c = a + b;
                boost::real::real d("2");
                boost::real::real e = a * d;

                CHECK_THROWS_AS(c < e, boost::real::precision_exception);
            }

            SECTION("Subtraction < Explicit") {
                boost::real::real a("1.1111111111112");
                boost::real::real b("0.0000000000001");
                boost::real::real c = a - b;
                boost::real::real d("1.1111111111111");

                CHECK_THROWS_AS(c < d, boost::real::precision_exception);
            }

            SECTION("Subtraction < Addition") {
                boost::real::real a("1.1111111111112");
                boost::real::real b("0.0000000000001");
                boost::real::real c = a - b;
                boost::real::real d("-0.0000000000001");
                boost::real::real e = a + d;

                CHECK_THROWS_AS(c < e, boost::real::precision_exception);
            }

            SECTION("Subtraction < Subtraction") {
                boost::real::real a("1.1111111111112");
                boost::real::real b("0.0000000000001");
                boost::real::real c = a - b;
                boost::real::real d = a - b;

                CHECK_THROWS_AS(c < d, boost::real::precision_exception);
            }

            SECTION("Subtraction < multiplication") {
                boost::real::real a("1.1111111111112");
                boost::real::real b("0.0000000000001");
                boost::real::real c = a + b;
                boost::real::real d("1.1111111111111");
                boost::real::real e("1");
                boost::real::real f = d * e;

                CHECK_THROWS_AS(c < f, boost::real::precision_exception);
            }

            SECTION("multiplication < Explicit") {
                boost::real::real a("1.1111111111111");
                boost::real::real b("2");
                boost::real::real c = a * b;
                boost::real::real d("2.2222222222222");

                CHECK_THROWS_AS(c < d, boost::real::precision_exception);
            }

            SECTION("multiplication < Addition") {
                boost::real::real a("1.1111111111111");
                boost::real::real b("2");
                boost::real::real c = a * b;
                boost::real::real d = a + a;

                CHECK_THROWS_AS(c < d, boost::real::precision_exception);
            }

            SECTION("multiplication < Subtraction") {
                boost::real::real a("1.1111111111111");
                boost::real::real b("2");
                boost::real::real c = a * b;
                boost::real::real d("2.2222222222223");
                boost::real::real e("0.0000000000001");
                boost::real::real f = d - e;

                CHECK_THROWS_AS(c < f, boost::real::precision_exception);
            }

            SECTION("multiplication < multiplication") {
                boost::real::real a("1.1111111111111");
                boost::real::real b("2");
                boost::real::real c = a * b;
                boost::real::real d = a * b;

                CHECK_THROWS_AS(c < d, boost::real::precision_exception);
            }
        }
    }

    SECTION("a < b") {}

    SECTION(" a > b") {}
}

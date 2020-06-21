#include <catch2/catch.hpp>

#include <real/rational_number.hpp>
#include <real/real_exception.hpp>
#include <real/real.hpp>
#include <test_helpers.hpp>

TEMPLATE_TEST_CASE("CONSTRUCTOR UNIT TEST","[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using rational = boost::real::rational_number<TestType>;
	using integer = boost::real::integer<TestType>;
	SECTION("USING INTEGERS"){
		integer a("10");
		integer b("20");
		rational c(a,b);
		CHECK(c.a==integer("1"));
		CHECK(c.b==integer("2"));
		CHECK(c.positive==true);

		c = rational(a);
		CHECK(c.a == integer("10"));
		CHECK(c.b == integer("1"));
		CHECK(c.positive == true);

		CHECK_THROWS_AS(c == rational(a, integer("0")), boost::real::divide_by_zero);

		c = rational("1/2");
		rational d = rational(integer("1"), integer("2"));
		CHECK(c==d);

		c = rational("-1/2");
		d = rational(integer("-1"), integer("2"));
		CHECK(c==d);

		d = rational(integer("1"), integer("-2"));
		CHECK(c==d);

		c = rational("5");
		d = rational(integer("5"), integer("1"));
		CHECK(c==d);

		d = rational(c);
		CHECK(c==d);
	}

	SECTION("USING STRING_VIEW"){
		rational a("10/20");
		rational b("3/9");
		CHECK(a.a == integer("1"));
		CHECK(a.b == integer("2"));
		CHECK(b.a == integer("1"));
		CHECK(b.b == integer("3"));

		a = rational("5/9");
		CHECK(a.a == integer("5"));
		CHECK(a.b == integer("9"));

		a = rational("6/28");
		CHECK(a.a == integer("3"));
		CHECK(a.b == integer("14"));
	}
}

TEMPLATE_TEST_CASE("INTEGRATION WITH REAL HPP", "[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using real = boost::real::real<TestType>;
	SECTION("CONSTRUCTOR TEST"){
		boost::real::real<int> a("10/11", "rational");
		boost::real::real<int> b = "10/11"_rational;
		CHECK(a==b);
	}

	SECTION("COMPARISON OPERATOR TESTS"){
		SECTION("RATIONAL - RATIONAL"){
			real a("10/11", "rational");
			real b("9/11", "rational");
			CHECK(a>b);
			CHECK_FALSE(a<b);
			CHECK_FALSE(a==b);

			b = real("10/11","rational");
			CHECK(a==b);
			CHECK_FALSE(a>b);
			CHECK_FALSE(a<b);
			b = real("20/22", "rational");
			CHECK(a==b);
		}

		SECTION("INTEGER - RATIONAL"){
			real a("10/11", "rational");
			real b("1", "integer");
			CHECK_FALSE(a==b);
			CHECK(a<b);
			CHECK_FALSE(a>b);
			CHECK(b>a);
			CHECK_FALSE(b<a);

			a = real("10", "rational");
			b = real("10", "integer");
			CHECK(a==b);
			CHECK_FALSE(a>b);
			CHECK_FALSE(a<b);
			CHECK_FALSE(b>a);
			CHECK_FALSE(b<a);
		}
	}

	SECTION("ADDITION - SUBTRACTION OPERATOR TEST"){
		SECTION("RATIONAL - INTEGER"){
			real a("7/9", "rational");
			real b("1", "integer");
			real c = a+b;
			real d("16/9", "rational");
			CHECK(c==d);
			c = b+a;
			CHECK(c==d);
			c = a-b;
			d = real("-2/9", "rational");
			CHECK(c==d);
			c = b-a;
			d = real("2/9", "rational");
			CHECK(c==d);
		}

		SECTION("RATIONAL - RATIONAL"){
			real a("1/4", "rational");
			real b("1/4", "rational");
			real c = a+b;
			real d("1/2", "rational");
			CHECK(c==d);
			c = a-b;
			d = real("0/10", "rational");
			CHECK(c==d);

		}
	}

	SECTION("MULTIPLICATION OPERATOR TEST"){
		SECTION("RATIONAL - RATIONAL"){
			real a("10/17","rational");
			real b("1/2","rational");
			real c = a*b;
			real d("5/17", "rational");
			CHECK(c==d);
			b = real("2", "rational");
			c = a*b;
			d = real("20/17", "rational");
			CHECK(c==d);
			a = real("1/2", "rational");
			c = a*b;
			d = real("1", "rational");
			CHECK(c==d);
		}

		SECTION("INTEGER - RATIONAL"){
			real a("10", "integer");
			real b("10/17", "rational");
			real c = a*b;
			real d("100/17", "rational");
			CHECK(c==d);
			c = b*a;
			CHECK(c==d);

			a = real("0", "integer");
			c = a*b;
			d = real("0", "rational");
			CHECK(c==d);

		}
	}

	SECTION("DIVISION OPERATION TEST"){
		SECTION("RATIONAL - RATIONAL"){
			real a("10/20", "rational");
			real b("1/3", "rational");
			real c = a/b;
			real d("3/2", "rational");
			CHECK(c==d);
		}

		SECTION("INTEGER - RATIONAL"){
			real a("1/3", "rational");
			real b("2", "integer");
			real c = a/b;
			real d("1/6", "rational");
			CHECK(c==d);
		}

		SECTION("INTEGER - INTEGER"){
			real a("1", "integer");
			real b("3", "integer");
			real c = a/b;
			real d("1/3", "rational");
			CHECK(c==d);
		}
	}
}


TEMPLATE_TEST_CASE("Addition Test","[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using rational = boost::real::rational_number<TestType>;
	using integer = boost::real::integer<TestType>;
	SECTION("BOTH NUMBERS ARE POSITIVE AND RATIONAL NUMBERS"){
		rational a,b,c,d;
		a = rational(integer("1"), integer("2"));
		b = rational(integer("1"), integer("2"));
		// just checking whether both are equal or not
		CHECK(a==b);
		c = a+b;
		d = rational(integer("1"), integer("1"));
		CHECK(c==d);
		c+=rational("1/2");
		d = rational("3/2");
		CHECK(c==d);
	}
	SECTION("NUMBERS HAVE DIFFERENT SIGN AND BOTH ARE RATIONAL NUMBERS"){
		rational a,b,c,d;
		a = rational(integer("-1"), integer("4"));
		b = rational(integer("1"), integer("2"));
		c = a+b;
		d = rational(integer("1"), integer("4"));
		CHECK(c==d);
		c = b+a;
		CHECK(c==d);
	}
	SECTION("BOTH NUMBERS ARE NEGATIVE AND RATIONAL NUMBERS"){
		rational a,b,c,d;
		a = rational("-1/4");
		b = rational("-1/4");
		c = a+b;
		d = rational("-1/2");
		CHECK(c==d);
	}

	SECTION("BOTH NUMBERS ARE POSITIVE AND ONE IS INTEGER"){
		rational a("1/2");
		integer b("1");
		rational c = a+b;
		rational d("3/2");
		CHECK(c==d);

		c = b+a;
		CHECK(c==d);
	}
}

TEMPLATE_TEST_CASE("Subtraction Test", "[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using rational = boost::real::rational_number<TestType>;
	using integer = boost::real::integer<TestType>;
	SECTION("BOTH NUMBERS ARE POSITIVE AND RATIONAL NUMBERS"){
		rational a,b,c,d;
		a = rational("1/2");
		b = rational("1/4");
		c = a-b;
		d = rational("1/4");
		CHECK(c==d);
		d = (-d);
		c = (-c);
		CHECK(c==d);
	}

	SECTION("BOTH NUMBERS HAVE DIFFERENT SIGN AND BOTH ARE RATIONAL NUMBERS"){
		rational a,b,c,d;
		a = rational("1/2");
		b = rational("-1/4");
		c = a-b;
		d = rational("3/4");
		CHECK(c==d);
		c = b-a;
		d = rational("-3/4");
		CHECK(c==d);
	}

	SECTION("BOTH NUMBERS ARE NEGATIVE AND RATIONAL NUMBERS"){

	}

	SECTION("BOTH NUMBERS ARE POSITIVE AND ONE IS INTEGER"){
		rational a,c,d;
		integer b;
		a = rational("5/4");
		b = integer("1");
		c = a-b;
		d = rational("1/4");
		CHECK(c==d);

		c = c-b;
		d = rational("-3/4");
		CHECK(c==d);

		c-=b;
		d = rational("-7/4");
		CHECK(c==d);

		c = b-a;
		d = rational("-1/4");
		CHECK(c==d);

		a = rational("2");
		b = integer("2");
		c = a-b;
		d = rational("0/5");
		CHECK(c==d);

		c = b-a;
		CHECK(c==d);

		a = rational("1/4");
		c = a - (rational("1/4"));
		d = rational("0/10000000000");
		CHECK(c==d);

		c = rational("1/4") - a;
		CHECK(c==d);
	}
}

TEMPLATE_TEST_CASE("MULTIPLICATION TEST", "[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using rational = boost::real::rational_number<TestType>;
	using integer = boost::real::integer<TestType>;
	SECTION("BOTH NUMBERS ARE POSITIVE AND RATIONAL NUMBERS"){
		rational a,b,c,d;
		a = rational("1/2");
		b = rational("1/2");
		c = a*b;
		d = rational("1/4");
		CHECK(c==d);

		b = rational("2");
		c = a*b;
		d = rational("1");
		CHECK(c==d);
	}

	SECTION("BOTH NUMBERS HAVE DIFFERENT SIGN AND RATIONAL NUMBERS"){
		rational a,b,c,d;
		a = rational("1/2");
		b = rational("-1/2");
		c = a*b;
		d = rational("-1/4");
		CHECK(c==d);

		b = rational("-2");
		c = a*b;
		d = rational("-1");
		CHECK(c==d);
	}

	SECTION("BOTH NUMBERS ARE NEGATIVE AND RATIONAL NUMBERS"){
		rational a,b,c,d;
		a = rational("-1/2");
		b = rational("-1/2");
		c = a*b;
		d = rational("1/4");
		CHECK(c==d);
	}

	SECTION("BOTH NUMBERS ARE POSITIVE AND ONE IS INTEGER"){
		integer a;
		rational b,c,d;
		a = integer("2");
		b = rational("1/4");
		c = b*a;
		d = rational("1/2");
		CHECK(c==d);
		c = a*b;
		CHECK(c==d);
		a = integer("0");
		c = a*b;
		d = rational("0");
		CHECK(c==d);
	}

	SECTION("BOTH NUMBERS HAVE DIFFERENT SIGNS AND ONE IS INTEGER"){

	}
	SECTION("BOTH NUMBERS HAVE NEGATIVE SIGN AND ONE IS INTEGER"){

	}
}

TEMPLATE_TEST_CASE("DIVISION TEST", "[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using rational = boost::real::rational_number<TestType>;
	using integer = boost::real::integer<TestType>;
	SECTION("BOTH NUMBERS ARE RATIONAL"){
		rational a,b,c,d;
		a = rational("1/2");
		b = rational("1/2");
		c = a/b;
		d = rational("1");
		CHECK(c==d);

		b = rational("3/2");
		c = a/b;
		d = rational("1/3");
		CHECK(c==d);

		b = rational("1/3");
		c = a/b;
		d = rational("3/2");
		CHECK(c==d);

		b = rational("-1/3");
		c = a/b;
		d = rational("-3/2");
		CHECK(c==d);
	}

	SECTION("ONE NUMBER IS RATIONAL AND OTHER IS INTEGER"){
		
	}
}

TEMPLATE_TEST_CASE("Operator tests", "[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using rational = boost::real::rational_number<TestType>;
	using integer = boost::real::integer<TestType>;
	SECTION("Equal Operator test"){
		SECTION("RATIONAL - RATIONAL"){
			rational a,b,c,d;
			a = rational(integer("1"), integer("2"));
			b = rational(integer("10"), integer("20"));
			CHECK(a==b);

			CHECK(a == rational(integer("40"), integer("80")));
			integer a1("2");
			CHECK_FALSE(a==a1);
			CHECK_FALSE(a1==a);
		}

		SECTION("INTEGER - RATIONAL"){
			rational a,b;
			integer c;
			a = rational("10/11");
			c = integer("1");
			CHECK(c>a);
		}

	}
	SECTION("Greater than Operator test"){
		rational a,b,c,d;
		a = rational(integer("1"), integer("2"));
		b = rational(integer("1"), integer("3"));
		CHECK(a>b);
		CHECK(a>=b);
		CHECK_FALSE(b>a);

		a = rational(integer("1"), integer("10000000000000000000"));
		b = rational(integer("2"), integer("10000000000000000000"));
		CHECK(b>a);

		integer _a("1");
		CHECK_FALSE(a>_a);

		a = rational(integer("-1"), integer("2"));
		b = rational(integer("1"), integer("3"));
		CHECK(b>a);
		CHECK_FALSE(a>b);

		b = rational(integer("-1"), integer("3"));
		CHECK(b>a);
	}

	SECTION("Less Than Operator test"){
		rational a,b,c,d;
		a = rational(integer("1"), integer("2"));
		b = rational(integer("1"), integer("3"));
		CHECK_FALSE(a<b);
		CHECK(b<a);
	}
}

TEMPLATE_TEST_CASE("HELPER FUNCTION TEST", "[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using integer = boost::real::integer<TestType>;
	using rational = boost::real::rational_number<TestType>;

	SECTION("Testing abs() Function"){
		rational a("-1/4");
		rational b = abs(a);
		rational c("1/4");
		CHECK(b==c);

		a = rational("-0/60");
		b = abs(a);
		c = rational("0");
		CHECK(b==c);

		a = rational("0/40");
		b = abs(a);
		CHECK(b==c);
	}

	SECTION("Testing floor() Function"){
		integer a,b;
		rational c;
		a = integer("0");
		c = rational("1/2");
		b = floor(c);
		CHECK(a==b);

		a = integer("1");
		c = rational("3/2");
		b = floor(c);
		CHECK(a==b);

		a = integer("-2");
		c = rational("-3/2");
		b = floor(c);
		CHECK(a==b);
	}

	SECTION("Testing ceil() function"){
		integer a,b;
		rational c,d;
		a = integer("1");
		c = rational("1/2");
		b = ceil(c);
		CHECK(a==b);

		a = integer("2");
		c = rational("3/2");
		b = ceil(c);
		CHECK(a==b);

		a = integer("-1");
		c = rational("-3/2");
		b = ceil(c);
		CHECK(a==b);

	}
}
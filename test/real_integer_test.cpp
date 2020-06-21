#include <catch2/catch.hpp>

#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE("CONSTRUCTOR UNIT TEST"){
	boost::real::integer a("1000000");
	boost::real::integer b("1e6");
	CHECK(a==b);

	a = boost::real::integer("1");
	b = boost::real::integer("-1");
	CHECK_FALSE(a==b);

}

TEMPLATE_TEST_CASE("INTEGRATION WITH REAL.HPP", "[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using real = boost::real::real<TestType>;
	SECTION("CONSTRUCTORS"){
		boost::real::real<int> a("10", "integer");
		auto b = 10_integer;
		auto c = "10"_integer;
		CHECK(a==b);
		CHECK(a==c);
	}

	SECTION("COMPARISION OPERATORS"){
		real a("10", "integer");
		real b("15", "integer");
		CHECK(a<b);
		CHECK_FALSE(a==b);
		CHECK_FALSE(a>b);

		b = real("10", "integer");
		CHECK(a==b);
		CHECK_FALSE(a>b);
		CHECK_FALSE(a<b);
	}

	SECTION("CALCULATION OPERATIONS"){
		SECTION("ADDITION"){
			real a("10", "integer");
			real b("20", "integer");
			real c = a+b;
			real d("30", "integer");
			CHECK(c==d);

			b = real("0", "integer");
			c = a+b;
			CHECK(a==c);

			b = real("-10", "integer");
			c = a+b;
			d = real("0", "integer");
			CHECK(c==d);

			b = real("-20", "integer");
			c = a+b;
			d = real("-10", "integer");
			CHECK(c==d);
		}

		SECTION("SUBTRACTION"){
			real a("30", "integer");
			real b("20", "integer");
			real c = a-b;
			real d("10", "integer");
			CHECK(c==d);

			b = real("-20", "integer");
			c = a-b;
			d = real("50", "integer");
			CHECK(c==d);

			c = b-a;
			d = real("-50", "integer");
			CHECK(c==d);
		}

		SECTION("MULTIPLICATION"){
			real a("20", "integer");
			real b("30", "integer");
			real c = a*b;
			real d("600", "integer");
			CHECK(c==d);

			a = real("0", "integer");
			c = a*b;
			CHECK(a==c);

			a = real("-2", "integer");
			c = a*b;
			d = real("-60", "integer");
			CHECK(c==d);

			b = real("-20", "integer");
			c = a*b;
			d = real("40", "integer");
			CHECK(c==d);
		}

		// Division is checked in rational number test.
	}
}

TEMPLATE_TEST_CASE("Addition Test", "[template]", int, unsigned int, long , unsigned long, long long, unsigned long long){
	using integer=boost::real::integer<TestType>;
	SECTION("BOTH NUMBERS ARE POSITIVE"){
		integer a("10");
		integer b("20");
		integer c("30");
		integer d = a+b;
		CHECK(c==d);

		a = integer("1000000000000000000000000000000000000");
		b = integer("1");
		c = integer("1000000000000000000000000000000000001");
		d = a+b;
		CHECK(c==d);

		a = integer("99");
		b = integer("1");
		c = integer("100");
		d = a+b;
		CHECK(c==d);

		a = integer("2779997979127668899356782655389825");
		b = integer("1");
		c = a+b;
		d = integer("2779997979127668899356782655389826");
		CHECK(c==d);
	}
	
	SECTION("ONE NUMBER IS NEGATIVE"){
		integer a("10");
		integer b("-10");
		integer c = a+b;
		integer d("0");
		CHECK(c==d);

		c = b + a;
		CHECK(c==d);

		a = integer("100");
		b = integer("-1");
		c = integer("99");
		d = a+b;
		CHECK(c==d);

		a = integer("-100");
		b = integer("1");
		c = integer("-99");
		d = a+b;
		CHECK(c==d);

		a = integer("1000000000000000000000000000000000000000000000");
		b = integer("-1");
		c = integer("999999999999999999999999999999999999999999999");
		d = a+b;
		CHECK(c==d);

		a = integer("-1000000000000000000000000000000000000000000000");
		b = integer("1");
		c = integer("-999999999999999999999999999999999999999999999");
		d = a+b;
		CHECK(c==d);

		a = integer("1000000000000000000000000008997");
		b = integer("-1000000000000000000000000000000");
		c = integer("8997");
		d = a+b;
		CHECK(c==d);	
		}
	
	
	SECTION("BOTH NUMBERS ARE NEGATIVE"){

		integer a = integer("-1");
		integer b = integer("-2");
		integer c = a+b;
		integer d = integer("-3");
		CHECK(c==d);

		a = integer("-1000");
		b = integer("-11");
		c = a+b;
		d = integer("-1011");
		CHECK(c==d);

		a = integer("-99999999999999999999999999");
		b = integer("-1");
		d = integer("-100000000000000000000000000");
		c = a+b;
		CHECK(c==d);

		c = b+a;
		CHECK(c==d);
	}
}
TEMPLATE_TEST_CASE("Subtraction Test ", "[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using integer = boost::real::integer<TestType>;
	SECTION("BOTH NUMBERS ARE POSITIVE"){
		integer a("1");
		integer b("2");
		integer c("-1");
		integer d = a-b;
		CHECK(c==d);
		d = b-a;
		CHECK(d==a);

		a = integer("10000000000000000008998");
		b = integer("10000000000000000000000");
		c = integer("8998");
		d = a-b;
		CHECK(c==d);
		c = integer("-8998");
		d = b-a;
		CHECK(c==d);
	}

	SECTION("ONE NUMBER IS NEGATIVE"){
		integer a,b,c,d;

		a = integer("1");
		b = integer("-1");
		c = integer("2");
		d = a-b;
		CHECK(c==d);
		//c = integer("-2");

		d = b-a;
		c = (-c);
		CHECK(c==d);

	}
}


TEMPLATE_TEST_CASE("COMPARISION OPERATOR TESTS", "[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using integer = boost::real::integer<TestType>;

	SECTION("ALL OPERATOR TESTS FOR NUMBERS"){
		integer a("1");
		integer b("2");
		CHECK(b>a);

		a = integer("1");
		b = integer("1");
		CHECK(a==b);
		CHECK(a>=b);
		CHECK(a<=b);
		CHECK_FALSE(a!=b);
		CHECK_FALSE(b>a);
		CHECK_FALSE(b<a);
		CHECK_FALSE(a>b);
		CHECK_FALSE(a<b);
		
		a = integer("1000000000000000000000000000009765399200001");
		b = integer("2779997979127668899356782655389825");
		CHECK(a>b);
		CHECK(a>=b);
		CHECK(a!=b);
		CHECK_FALSE(a==b);
		CHECK_FALSE(a<=b);
		CHECK_FALSE(a<b);

		a = integer("-1");
		b = integer("-2");
		CHECK_FALSE(b>a);
		CHECK(a>b);
		CHECK_FALSE(a==b);

		a = integer("1");
		b = integer("-1");
		CHECK_FALSE(a==b);
		CHECK(a>b);

		a = integer("0");
		b = integer("-1");
		CHECK(a>b);

	}
}

TEMPLATE_TEST_CASE("MULTIPLICATION TEST","[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using integer = boost::real::integer<TestType>;

	SECTION("BOTH NUMBERS ARE POSITIVE"){
		integer a,b,c,d;

		a = integer("1");
		b = integer("2");
		c = a*b;
		CHECK(c==b);
	}
}

TEMPLATE_TEST_CASE("REMAINDER OPERATOR TEST","[template]", int, unsigned int, long, unsigned long, long long, unsigned long long){
	using integer = boost::real::integer<TestType>;
	SECTION("BOTH NUMBERS ARE POSITIVE"){
		integer a,b,c,d;
		a = integer("10");
		b = integer("7");
		c = a%b;
		d = integer("3");
		CHECK(c==d);

		a = integer("1000000000000000000000000000000005");
		b = integer("1000000000000000000000000000000000");
		c = a%b;
		d = integer("5");
		CHECK(c==d);
	}

	SECTION("ONE NUMBER IS NEGATIVE AND OTHER IS POSITIVE"){
		integer a,b,c,d;
		a = integer("-7");
		b = integer("5");
		c = a%b;
		d = integer("3");
		CHECK(c==d);

		a = integer("7");
		b = integer("-5");
		c = a%b;
		d = integer("2");
		CHECK(c==d);		

	}
}
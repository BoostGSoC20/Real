#include <catch2/catch.hpp>
#include <test_helpers.hpp>

TEST_CASE("TRIGONOMETRIC FUNCTIONS"){
	using real = boost::real::real<int>;
	SECTION("BASIC TRIGONOMETRIC VALUES"){
		real a("0");
		real b = real::sin(a);
		CHECK(a==b);

		real c("1");
		real d = real::cos(a);
		CHECK(c==d);
	}

	// checking for property sin^2 + cos^2  = 1. Not using == operator, because it takes lot of time to test
	SECTION("BASIC TRIGONOMETRIC PROPERTIES"){
		real a("2"); // some random number
		real b = real::sin(a);
		real c = real::cos(a);
		b = b*b;
		c = c*c;
		real lower_limit("1");
		real upper_limit("1");
		real e = b+c;
		real one = boost::real::literals::one_real<int>;
		for(int i=1;i<4;++i){
			lower_limit = one - real({1}, -i);
			upper_limit = one + real({1}, -i);
			CHECK(e > lower_limit);
			CHECK(e < upper_limit);
		}
	}
}

TEST_CASE("LOGARITHM AND EXPONENT"){
	using real = boost::real::real<int>;
	SECTION("BASIC FUNCTIONS VALUES"){
		real a("0");
		real b = real::exp(a); // exp(0) = 1
		real c("1");
		CHECK(b==c);

		b = real::log(c); // log(1) = 0
		CHECK(a==b);

		a = real("2");
		b = real::log(a); // log 2 = 0.693147181
		real lower_limit("0.693147180");
		real upper_limit("0.693147182");
		CHECK(b > lower_limit);
		CHECK(b < upper_limit);

		b = real::exp(a); // exp 2 = 7.389056099;
		lower_limit = real("7.389056098");
		upper_limit = real("7.389056100");
		CHECK(b > lower_limit);
		CHECK(b < upper_limit);

		a  = real("-7.345");
		CHECK_THROWS_AS(b = real::log(a), boost::real::logarithm_not_defined_for_non_positive_number);
		b = real::exp(a); // exp (-4.345) = 0.000645813
		lower_limit = real("0.000645812");
		upper_limit = real("0.000645814");
		CHECK(b > lower_limit);
		CHECK(b < upper_limit);

		a = real("0.47783");
		b = real::log(a); // ln(0.0047783) = −0.738500258
		lower_limit = real("-0.738500259");
		upper_limit = real("-0.738500257");
		CHECK(b > lower_limit);
		CHECK(b < upper_limit);

		b = real::exp(a); // exp(0.47783) = 1.612571323
		lower_limit = real("1.612571322");
		upper_limit = real("1.612571324");
		CHECK(b > lower_limit);
		CHECK(b < upper_limit);
	}
}
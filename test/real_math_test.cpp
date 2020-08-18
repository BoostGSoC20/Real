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
	using TYPE = boost::real::TYPE;
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
		b = real::log(a); // ln(0.47783) = −0.738500258
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

	SECTION("ADDITION OPERATION (A+B)"){
		real a("0.5");
		real b("1.5");
		real c = a + b;
		real value = real::exp(c); // exp 2 = 7.389056099;
		real lower_limit = real("7.389056098");
		real upper_limit = real("7.389056100");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(c); // log 2 = 0.693147181
		lower_limit = real("0.693147180");
		upper_limit = real("0.693147182");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		a = real("0.46683");
		b = real("0.01100");
		c = a+b;
		value = real::exp(c); // exp(0.47783) = 1.612571323
		lower_limit = real("1.612571322");
		upper_limit = real("1.612571324");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(c);
		lower_limit = real("-0.738500259");
		upper_limit = real("-0.738500257");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("SUBTRACTION OPERATION (A-B)"){
		real a("3.5");
		real b("1.5");
		real c = a - b;
		real value = real::exp(c); // exp 2 = 7.389056099;
		real lower_limit = real("7.389056098");
		real upper_limit = real("7.389056100");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);


		value = real::log(c); // log 2 = 0.693147181
		lower_limit = real("0.693147180");
		upper_limit = real("0.693147182");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		a = real("0.48883");
		b = real("0.01100");
		c = a - b;
		value = real::exp(c); // exp(0.47783) = 1.612571323
		lower_limit = real("1.612571322");
		upper_limit = real("1.612571324");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(c);
		lower_limit = real("-0.738500259");
		upper_limit = real("-0.738500257");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("MULTIPLICATION (A*B)"){
		real a("1/2", TYPE::RATIONAL);
		real b("4", TYPE::INTEGER);
		real c = a * b;
		real value = real::exp(c);
		real lower_limit = real("7.389056098");
		real upper_limit = real("7.389056100");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);


		value = real::log(c); // log 2 = 0.693147181
		lower_limit = real("0.693147180");
		upper_limit = real("0.693147182");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		a = real("0.5");
		b = real("4");
		value = real::exp(c);
		lower_limit = real("7.389056098");
		upper_limit = real("7.389056100");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);


		value = real::log(c); // log 2 = 0.693147181
		lower_limit = real("0.693147180");
		upper_limit = real("0.693147182");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		a = real("4.7783");
		b = real("0.1");
		c = a * b;
		value = real::exp(c); // exp(0.47783) = 1.612571323
		lower_limit = real("1.612571322");
		upper_limit = real("1.612571324");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(c);
		lower_limit = real("-0.738500259");
		upper_limit = real("-0.738500257");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("DIVISION OPERATOR (A/B)"){
		real a("16", TYPE::INTEGER);
		real b("8", TYPE::INTEGER);
		real c = a/b;
		real value = real::exp(c);
		real lower_limit = real("7.389056098");
		real upper_limit = real("7.389056100");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(c); // log 2 = 0.693147181
		lower_limit = real("0.693147180");
		upper_limit = real("0.693147182");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		a = real("16");
		b = real("8");
		c = a/b;
		value = real::exp(c);
		lower_limit = real("7.389056098");
		upper_limit = real("7.389056100");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(c); // log 2 = 0.693147181
		lower_limit = real("0.693147180");
		upper_limit = real("0.693147182");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		a = real("1");
		b = real("0.5");
		c = a/b;
		value = real::exp(c);
		lower_limit = real("7.389056098");
		upper_limit = real("7.389056100");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(c); // log 2 = 0.693147181
		lower_limit = real("0.693147180");
		upper_limit = real("0.693147182");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		a = real("1");
		b = real("1/2", TYPE::RATIONAL);
		c = a/b;
		value = real::exp(c);
		lower_limit = real("7.389056098");
		upper_limit = real("7.389056100");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(c); // log 2 = 0.693147181
		lower_limit = real("0.693147180");
		upper_limit = real("0.693147182");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		a = real("4.7783");
		b = real("10");
		c = a / b;
		value = real::exp(c); // exp(0.47783) = 1.612571323
		lower_limit = real("1.612571322");
		upper_limit = real("1.612571324");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(c);
		lower_limit = real("-0.738500259");
		upper_limit = real("-0.738500257");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("A*(B+C)"){
		real a("2.4");
		real b("1.45");
		real c("6.87");
		real d = a * (b + c); // 2.4 * (1.45 + 6.87) = 19.968
		real value = real::exp(d); // exp(19.968) = 469885685.150121983
		real lower_limit("469885685.150121982");
		real upper_limit("469885685.150121984");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(d); // ln(19.968) = 2.9941309922
		lower_limit = real("2.9941309921");
		upper_limit = real("2.9941309923");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("A*(B-C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a * (b - c); // 2.4 * (6.87 - 1.45) = 13.008
		real value = real::exp(d); // exp(13.008) = 445966.8942017718
		real lower_limit("445966.8942017717");
		real upper_limit("445966.8942017719");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(d); // ln(13.008) = 2.5655645528
		lower_limit = real("2.5655645527");
		upper_limit = real("2.5655645529");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}
	SECTION("A*(B/C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a * (b / c); // 2.4 * (6.87 / 1.45) = 11.3710344828
		real value = real::exp(d); // exp(11.3710344828) = 86771.5847792432
		real lower_limit("86771.5847792431");
		real upper_limit("86771.5847792433");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(d); // ln(11.3710344828) = 2.4310692872
		lower_limit = real("2.4310692871");
		upper_limit = real("2.4310692873");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}
	SECTION("A/(B+C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a / (b + c); // 2.4 / (6.87 + 1.45) = 0.2884615385
		real value = real::exp(d); // exp(0.2884615385) = 1.3343730265
		real lower_limit("1.3343730264");
		real upper_limit("1.3343730266");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(d); // ln(0.2884615385) = −1.2431935173
		lower_limit = real("-1.243193518");
		upper_limit = real("-1.243193516");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}
	SECTION("A/(B-C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a / (b - c); // 2.4 / (6.87 - 1.45) = 0.442804428
		real value = real::exp(d); // exp(0.442804428) = 1.5570677858
		real lower_limit("1.5570677857");
		real upper_limit("1.5570677859");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(d); // ln(0.442804428) = −0.8146270782
		lower_limit = real("-0.814627079");
		upper_limit = real("-0.814627077");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}
	/*
	//Currently commented due to bug in division operator 
	SECTION("A/(B*C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a / (b * c); // 2.4 / (6.87 * 1.45) = 0.2409275711
		real value = real::exp(d); // exp(0.2409275711) = 1.2724288714
		real lower_limit("1.2724288713");
		real upper_limit("1.2724288715");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}
	*/
	SECTION("A+(B*C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a + (b * c); // 2.4 + (6.87 * 1.45) = 12.3615
		real value = real::exp(d); // exp(12.3615) = 233631.414318997
		real lower_limit("233631.414318996");
		real upper_limit("233631.414318998");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(d); // ln(12.3615) = 2.5145868039
		lower_limit = real("2.5145868038");
		upper_limit = real("2.514586804");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("A+(B/C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a + (b / c); // 2.4 + (6.87 / 1.45) = 7.1379310345
		real value = real::exp(d); // exp(7.1379310345) = 1258.8212352445
		real lower_limit("1258.8212352444");
		real upper_limit("1258.8212352446");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(d); // ln(7.1379310345) = 1.9654229633
		lower_limit = real("1.9654229632");
		upper_limit = real("1.9654229634");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("A+(B-C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a + (b - c); // 2.4 + (6.87 - 1.45) = 7.82
		real value = real::exp(d); // exp(7.82) = 2489.9054080445
		real lower_limit("2489.9054080444");
		real upper_limit("2489.9054080446");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(d); // ln(7.82) = 2.0566845546
		lower_limit = real("2.0566845545");
		upper_limit = real("2.0566845547");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("A+(B+C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a + (b + c); // 2.4 + (6.87 + 1.45) = 10.72
		real value = real::exp(d); // exp(10.72) = 45251.9028419625
		real lower_limit("45251.9028419624");
		real upper_limit("45251.9028419626");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(d); // ln(10.72) = 2.3721111556
		lower_limit = real("2.3721111555");
		upper_limit = real("2.3721111557");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("A-(B+C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a - (b + c); // 2.4 - (6.87 + 1.45) = −5.92
		real value = real::exp(d); // exp(−5.92) = 0.0026852002
		real lower_limit("0.0026852001");
		real upper_limit("0.0026852003");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("A-(B-C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a - (b - c); // 2.4 - (6.87 - 1.45) = −3.02
		real value = real::exp(d); // exp(−3.02) = 0.0488012184
		real lower_limit("0.0488012183");
		real upper_limit("0.0488012185");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("A-(B*C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a - (b * c); // 2.4 - (6.87 * 1.45) = −7.5615
		real value = real::exp(d); // exp(−7.5615) = 0.0005200945
		real lower_limit("0.0005200944");
		real upper_limit("0.0005200946");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("A-(B/C)"){
		real a("2.4");
		real b("6.87");
		real c("1.45");
		real d = a - (b / c); // 2.4 - (6.87 / 1.45) = −2.3379310345
		real value = real::exp(d); // exp(−2.3379310345) = 0.0965271431
		real lower_limit("0.0965271430");
		real upper_limit("0.0965271432");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("(A+B) + (C+D)"){
		real a("2.45");
		real b("3.73");
		real c("8.46");
		real d("9.35");
		real e = (a + b) + (c + d); // (2.45 + 3.73) + (8.46 + 9.35) = 23.99
		real value = real::exp(e); // exp(23.99) = 26225550960.8129381278
		real lower_limit("26225550960.8129381277");
		real upper_limit("26225550960.8129381279");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(e); // ln(23.99) = 3.1776370769
		lower_limit = real("3.1776370768");
		upper_limit = real("3.177637077");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("(A+B) * (C+D)"){
		real a("2.45");
		real b("3.73");
		real c("8.46");
		real d("9.35");
		real e = (a + b) * (c + d); // (2.45 + 3.73) * (8.46 + 9.35) = 110.0658
		real value = real::exp(e); // exp(110.0658) = 6.3236756499×10^47
		real lower_limit("6.3236756498e47");
		real upper_limit("6.32367565e47");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(e); // ln(110.0658) = 4.7010783688
		lower_limit = real("4.7010783687");
		upper_limit = real("4.7010783689");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("(A+B) / (C+D)"){
		real a("2.45");
		real b("3.73");
		real c("8.46");
		real d("9.35");
		real e = (a + b) / (c + d); // (2.45 + 3.73) / (8.46 + 9.35) = 0.3469960696
		real value = real::exp(e); // exp(0.3469960696) = 1.4148111646
		real lower_limit("1.4148111645");
		real upper_limit("1.4148111647");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);

		value = real::log(e); // ln(0.3469960696) = −1.0584418259
		lower_limit = real("-1.058441826");
		upper_limit = real("-1.0584418258");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}

	SECTION("(A+B) - (C+D)"){
		real a("2.45");
		real b("3.73");
		real c("8.46");
		real d("9.35");
		real e = (a + b) - (c + d); // (2.45 + 3.73) - (8.46 + 9.35) = −11.63
		real value = real::exp(e); // exp(−11.63) = 1.4148111646
		real lower_limit("0.00000889517");
		real upper_limit("0.00000889519");
		CHECK(value > lower_limit);
		CHECK(value < upper_limit);
	}



}
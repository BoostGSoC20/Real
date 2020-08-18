#include <catch2/catch.hpp>
#include <real/real.hpp>
#include <real/irrationals.hpp>
#include <test_helpers.hpp>

TEST_CASE("Pi") {

	using real = boost::real::real<int>;

	real pi = boost::real::irrational::PI<int>;
	boost::real::exact_number length;

	SECTION("TRIGONOMETRIC PROPERTIES") {

		SECTION("sin(pi) == 0") {

			real sin_pi = real::sin(pi);
			boost::real::exact_number zero("0");

			auto sin_pi_iterator = sin_pi.get_real_itr().cbegin();
			++sin_pi_iterator;

            CHECK(sin_pi_iterator.get_interval().lower_bound <= sin_pi_iterator.get_interval().upper_bound);
            CHECK(!sin_pi_iterator.get_interval().lower_bound.positive);
            CHECK(sin_pi_iterator.get_interval().upper_bound.positive);
            ++sin_pi_iterator;

            CHECK(sin_pi_iterator.get_interval().lower_bound <= sin_pi_iterator.get_interval().upper_bound);
            CHECK(!sin_pi_iterator.get_interval().lower_bound.positive);
            CHECK(sin_pi_iterator.get_interval().upper_bound.positive);
            ++sin_pi_iterator;

            CHECK(sin_pi_iterator.get_interval().lower_bound <= sin_pi_iterator.get_interval().upper_bound);
            CHECK(!sin_pi_iterator.get_interval().lower_bound.positive);
            CHECK(sin_pi_iterator.get_interval().upper_bound.positive);
            ++sin_pi_iterator;

            CHECK(sin_pi_iterator.get_interval().lower_bound <= sin_pi_iterator.get_interval().upper_bound);
            CHECK(!sin_pi_iterator.get_interval().lower_bound.positive);
            CHECK(sin_pi_iterator.get_interval().upper_bound.positive);
            ++sin_pi_iterator;
		}

		SECTION("cos(2 * pi) == 1") {

			real two("2");
			real cos_pi = real::cos(two * pi);
			boost::real::exact_number<int> one("1");

			auto cos_pi_iterator = cos_pi.get_real_itr().cbegin();
			++cos_pi_iterator;

            CHECK(cos_pi_iterator.get_interval().lower_bound <= cos_pi_iterator.get_interval().upper_bound);
            CHECK(cos_pi_iterator.get_interval().lower_bound <= one);
            CHECK(cos_pi_iterator.get_interval().upper_bound >= one);

            ++cos_pi_iterator;

            CHECK(cos_pi_iterator.get_interval().lower_bound <= cos_pi_iterator.get_interval().upper_bound);
            CHECK(cos_pi_iterator.get_interval().lower_bound <= one);
            CHECK(cos_pi_iterator.get_interval().upper_bound >= one);

            ++cos_pi_iterator;
            
            CHECK(cos_pi_iterator.get_interval().lower_bound <= cos_pi_iterator.get_interval().upper_bound);
            CHECK(cos_pi_iterator.get_interval().lower_bound <= one);
            CHECK(cos_pi_iterator.get_interval().upper_bound >= one);

            ++cos_pi_iterator;
            
            CHECK(cos_pi_iterator.get_interval().lower_bound <= cos_pi_iterator.get_interval().upper_bound);
            CHECK(cos_pi_iterator.get_interval().lower_bound <= one);
            CHECK(cos_pi_iterator.get_interval().upper_bound >= one);

            ++cos_pi_iterator;
            
            CHECK(cos_pi_iterator.get_interval().lower_bound <= cos_pi_iterator.get_interval().upper_bound);
            CHECK(cos_pi_iterator.get_interval().lower_bound <= one);
            CHECK(cos_pi_iterator.get_interval().upper_bound >= one);
		}

		SECTION("sin(2 * pi) == 0") {

			real two("2");
			real sin_2pi = real::sin(two * pi);
			
			auto sin_2pi_iterator = sin_2pi.get_real_itr().cbegin();
			++sin_2pi_iterator;

            CHECK(sin_2pi_iterator.get_interval().lower_bound <= sin_2pi_iterator.get_interval().upper_bound);
            CHECK(!sin_2pi_iterator.get_interval().lower_bound.positive);
            CHECK(sin_2pi_iterator.get_interval().upper_bound.positive);

            ++sin_2pi_iterator;

            CHECK(sin_2pi_iterator.get_interval().lower_bound <= sin_2pi_iterator.get_interval().upper_bound);
            CHECK(!sin_2pi_iterator.get_interval().lower_bound.positive);
            CHECK(sin_2pi_iterator.get_interval().upper_bound.positive);

            ++sin_2pi_iterator;

            CHECK(sin_2pi_iterator.get_interval().lower_bound <= sin_2pi_iterator.get_interval().upper_bound);
            CHECK(!sin_2pi_iterator.get_interval().lower_bound.positive);
            CHECK(sin_2pi_iterator.get_interval().upper_bound.positive);

            ++sin_2pi_iterator;

            CHECK(sin_2pi_iterator.get_interval().lower_bound <= sin_2pi_iterator.get_interval().upper_bound);
            CHECK(!sin_2pi_iterator.get_interval().lower_bound.positive);
            CHECK(sin_2pi_iterator.get_interval().upper_bound.positive);

            ++sin_2pi_iterator;

            CHECK(sin_2pi_iterator.get_interval().lower_bound <= sin_2pi_iterator.get_interval().upper_bound);
            CHECK(!sin_2pi_iterator.get_interval().lower_bound.positive);
            CHECK(sin_2pi_iterator.get_interval().upper_bound.positive);

            ++sin_2pi_iterator;

            CHECK(sin_2pi_iterator.get_interval().lower_bound <= sin_2pi_iterator.get_interval().upper_bound);
            CHECK(!sin_2pi_iterator.get_interval().lower_bound.positive);
            CHECK(sin_2pi_iterator.get_interval().upper_bound.positive);
		}


		SECTION("sin(pi / 2) == 1") {

			real two("2");
			real sin_pi_by_2 = real::sin(pi / two);
			boost::real::exact_number one("1");

			auto sin_pi_by_2_iterator = sin_pi_by_2.get_real_itr().cbegin();
			++sin_pi_by_2_iterator;

            CHECK(sin_pi_by_2_iterator.get_interval().lower_bound <= sin_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(sin_pi_by_2_iterator.get_interval().lower_bound <= one);
            CHECK(sin_pi_by_2_iterator.get_interval().upper_bound >= one);

            ++sin_pi_by_2_iterator;

            CHECK(sin_pi_by_2_iterator.get_interval().lower_bound <= sin_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(sin_pi_by_2_iterator.get_interval().lower_bound <= one);
            CHECK(sin_pi_by_2_iterator.get_interval().upper_bound >= one);

            ++sin_pi_by_2_iterator;

            CHECK(sin_pi_by_2_iterator.get_interval().lower_bound <= sin_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(sin_pi_by_2_iterator.get_interval().lower_bound <= one);
            CHECK(sin_pi_by_2_iterator.get_interval().upper_bound >= one);
            ++sin_pi_by_2_iterator;

            CHECK(sin_pi_by_2_iterator.get_interval().lower_bound <= sin_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(sin_pi_by_2_iterator.get_interval().lower_bound <= one);
            CHECK(sin_pi_by_2_iterator.get_interval().upper_bound >= one);

            ++sin_pi_by_2_iterator;

            CHECK(sin_pi_by_2_iterator.get_interval().lower_bound <= sin_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(sin_pi_by_2_iterator.get_interval().lower_bound <= one);
            CHECK(sin_pi_by_2_iterator.get_interval().upper_bound >= one);

		}

		SECTION("cos(pi / 2) == 0") {

			real two("2");
			real cos_pi_by_2 = real::cos(pi / two);
			boost::real::exact_number zero = boost::real::exact_number<int>();

			auto cos_pi_by_2_iterator = cos_pi_by_2.get_real_itr().cbegin();
			++cos_pi_by_2_iterator;


            CHECK(cos_pi_by_2_iterator.get_interval().lower_bound <= cos_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(!cos_pi_by_2_iterator.get_interval().lower_bound.positive);
            CHECK(cos_pi_by_2_iterator.get_interval().upper_bound.positive);

            ++cos_pi_by_2_iterator;

            CHECK(cos_pi_by_2_iterator.get_interval().lower_bound <= cos_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(!cos_pi_by_2_iterator.get_interval().lower_bound.positive);
            CHECK(cos_pi_by_2_iterator.get_interval().upper_bound.positive);

            ++cos_pi_by_2_iterator;

            CHECK(cos_pi_by_2_iterator.get_interval().lower_bound <= cos_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(!cos_pi_by_2_iterator.get_interval().lower_bound.positive);
            CHECK(cos_pi_by_2_iterator.get_interval().upper_bound.positive);

            ++cos_pi_by_2_iterator;

            CHECK(cos_pi_by_2_iterator.get_interval().lower_bound <= cos_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(!cos_pi_by_2_iterator.get_interval().lower_bound.positive);
            CHECK(cos_pi_by_2_iterator.get_interval().upper_bound.positive);

            ++cos_pi_by_2_iterator;

            CHECK(cos_pi_by_2_iterator.get_interval().lower_bound <= cos_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(!cos_pi_by_2_iterator.get_interval().lower_bound.positive);
            CHECK(cos_pi_by_2_iterator.get_interval().upper_bound.positive);

            ++cos_pi_by_2_iterator;

            CHECK(cos_pi_by_2_iterator.get_interval().lower_bound <= cos_pi_by_2_iterator.get_interval().upper_bound);
            CHECK(!cos_pi_by_2_iterator.get_interval().lower_bound.positive);
            CHECK(cos_pi_by_2_iterator.get_interval().upper_bound.positive);

		}

	} 

	SECTION("digit check") {
		// matching starting few digits with hardcoded values
		std::string hardcoded_Pi("3.14159265358979323846264338327950288419716939937510582097494459230781640628620899");
		pi.get_real_itr().set_maximum_precision(25);
		auto pi_itr = pi.get_real_itr().cend();
		std::string real_pi = pi_itr.get_interval().upper_bound.as_string();

		for (int i=0; i<(int)hardcoded_Pi.size(); ++i) {
			CHECK(real_pi[i] == hardcoded_Pi[i]);
		}
	}

	SECTION("e^pi > pi^e") {

		real one("1");
		real e("2.718281828459045235360287471352662497757");
		real e_raised_to_pi = real::power(e, pi);
		real pi_raised_to_e = real::power(pi, e);

		auto itr1 = e_raised_to_pi.get_real_itr().cbegin();
		auto itr2 = pi_raised_to_e.get_real_itr().cbegin();

		++itr1;
		++itr2;

		CHECK(itr1.get_interval().lower_bound >= itr2.get_interval().upper_bound);
		std::cout << itr1.get_interval().lower_bound.as_string() << "  >=   " << itr2.get_interval().upper_bound.as_string() << "\n"; 

		++itr1;
		++itr2;

		CHECK(itr1.get_interval().lower_bound >= itr2.get_interval().upper_bound);
		std::cout << itr1.get_interval().lower_bound.as_string() << "  >=   " << itr2.get_interval().upper_bound.as_string() << "\n";

		++itr1;
		++itr2;

		CHECK(itr1.get_interval().lower_bound >= itr2.get_interval().upper_bound);
		std::cout << itr1.get_interval().lower_bound.as_string() << "  >=   " << itr2.get_interval().upper_bound.as_string() << "\n";
		
	}

}
#include <catch2/catch.hpp>
#include <real/real_explicit.hpp>
#include <test_helpers.hpp>

TEST_CASE("Iterate boost::real_explicit::const_precision_iterator until full precision is reached") {

    SECTION("Positive numbers") {

        std::vector<std::string> numbers = {
                "394723467263482764823874.5",
        };

        for (auto number : numbers) {
            SECTION("Testing for number " + number) {

                boost::real::real a(number);
                boost::real::const_precision_iterator approximation_it = a.get_real_itr().cbegin();
                boost::real::exact_number length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;

                for (size_t i = 0; i < 3; i++) {
                    CHECK( approximation_it.get_interval().lower_bound <= approximation_it.get_interval().upper_bound );
                    CHECK( approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound <= length);
                    length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;
                    ++approximation_it;
                }
            }
        }
    }


    SECTION("Negative numbers") {

        std::vector<std::string> numbers = {
                "-394723467263482764823874.5",
        };

        for (auto number : numbers) {
            SECTION("Testing for number " + number) {

                boost::real::real a(number);
                boost::real::const_precision_iterator approximation_it = a.get_real_itr().cbegin();
                boost::real::exact_number length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;

                for (size_t i = 0; i < 3; i++) {
                    CHECK( approximation_it.get_interval().lower_bound <= approximation_it.get_interval().upper_bound );
                    CHECK( approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound <= length);
                    length = approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound;
                    ++approximation_it;
                }
            }
        }
    }
}

TEST_CASE("Iterator cend") {

    boost::real::real a("39472346726348276482342342442323");
    boost::real::real b("39472346726348276482342342442323");
    boost::real::const_precision_iterator approximation_it = a.get_real_itr().cbegin();
    boost::real::const_precision_iterator end_it = b.get_real_itr().cend();

    SECTION("Iterate until the full explicit number digit amount returns the end of the iterator") {

        for(int i = 0; i < 3; i++) {
            CHECK_FALSE( approximation_it == end_it );
            ++approximation_it;
        }

        CHECK( approximation_it.get_interval() == end_it.get_interval() );
    }

    SECTION("Iterate cend() returns an interval more precise than cbegin()") {

        CHECK( end_it.get_interval().lower_bound <= end_it.get_interval().upper_bound);
        approximation_it = a.get_real_itr().cbegin();
        CHECK (end_it.get_interval().upper_bound - end_it.get_interval().lower_bound <=
                        approximation_it.get_interval().upper_bound - approximation_it.get_interval().lower_bound);
        CHECK( end_it.get_interval().lower_bound.positive == 
                        std::get<boost::real::real_explicit<>>(a.get_real_number()).positive());
        CHECK( end_it.get_interval().lower_bound.exponent ==
                        std::get<boost::real::real_explicit<>>(a.get_real_number()).exponent());
    }
}
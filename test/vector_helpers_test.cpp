#include <catch2/catch.hpp>
#include <real/real.hpp>
#include <test_helpers.hpp>

TEST_CASE( "Addition between vectors", "[vector]" ) {

    std::vector<int> a = {1,1,1};
    std::vector<int> b = {1,1};
    std::vector<int> c;

    REQUIRE( a.size() == 3 );
    REQUIRE( b.size() >= 2 );

    for (auto digit : b) {
        REQUIRE( digit == 1 );
    }

    for (auto digit : a) {
        REQUIRE( digit == 1 );
    }

    SECTION("moving right side operand exponent") {
        std::vector< std::pair<int, std::vector<int> > > expected_results = {
                std::make_pair(5, std::vector<int>({1,1,1,0,0,1,1})),
                std::make_pair(4, std::vector<int>({1,1,1,0,1,1})),
                std::make_pair(3, std::vector<int>({1,1,1,1,1})),
                std::make_pair(2, std::vector<int>({1,1,2,1})),
                std::make_pair(1, std::vector<int>({1,2,2})),
                std::make_pair(0, std::vector<int>({2,2,1})),
                std::make_pair(0, std::vector<int>({1,2,1,1})),
                std::make_pair(0, std::vector<int>({1,1,1,1,1})),
                std::make_pair(0, std::vector<int>({1,1,0,1,1,1})),
                std::make_pair(0, std::vector<int>({1,1,0,0,1,1,1}))
        };

        for (int i = 0; i < (int)expected_results.size(); i++) {
            int exponent = 5 - i;
            SECTION( "Exponent: " + std::to_string(exponent)) {
                int exponent_c = boost::real::helper::add_vectors(a,exponent,b,0,c);
                CHECK( exponent_c == expected_results[i].first);
                CHECK( c == expected_results[i].second);
            }
        }
    }

    SECTION("moving left side operand exponent") {
        std::vector< std::pair<int, std::vector<int> > > expected_results = {
                std::make_pair(5, std::vector<int>({1,1,1,0,0,1,1})),
                std::make_pair(4, std::vector<int>({1,1,1,0,1,1})),
                std::make_pair(3, std::vector<int>({1,1,1,1,1})),
                std::make_pair(2, std::vector<int>({1,1,2,1})),
                std::make_pair(1, std::vector<int>({1,2,2})),
                std::make_pair(0, std::vector<int>({2,2,1})),
                std::make_pair(0, std::vector<int>({1,2,1,1})),
                std::make_pair(0, std::vector<int>({1,1,1,1,1})),
                std::make_pair(0, std::vector<int>({1,1,0,1,1,1})),
                std::make_pair(0, std::vector<int>({1,1,0,0,1,1,1}))
        };

        for (int i = 0; i < (int)expected_results.size(); i++) {
            int exponent = 5 - i;
            SECTION( "Exponent: " + std::to_string(exponent)) {
                int exponent_c = boost::real::helper::add_vectors(b,0,a,exponent,c);
                CHECK( exponent_c == expected_results[i].first);
                CHECK( c == expected_results[i].second);
            }
        }
    }
}
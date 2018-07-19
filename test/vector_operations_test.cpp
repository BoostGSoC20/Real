#include <iostream>
#include <real/real_helpers.hpp>

int main() {

    std::vector<int> a = {1,1,1};
    std::vector<int> b = {1,1};
    std::vector<int> c;
    int exponent_c = boost::real::helper::add_vectors(a,1,b,0,c);

    std::cout << "c: " << exponent_c << " - ";
    for (auto& digit: c) {
        std::cout << digit;
    }
    std::cout << std::endl;

    c.clear();
    std::cout << boost::real::helper::add_vectors(a,4,b,3,c) << " - ";
    for (auto& digit: c) {
        std::cout << digit;
    }
    std::cout << std::endl;

    return 0;
}
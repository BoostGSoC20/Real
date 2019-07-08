#include <real/real.hpp>
#include <iostream>
#include <optional>

std::optional<unsigned int> boost::real::const_precision_iterator::maximum_precision = 10;

int main() {
    boost::real::real a("144"); // [100, 200]
    boost::real::real b("12");  // [10 , 20]
    boost::real::real result = b/a; // [100, 200] / [10, 20] = [100/20, 200/10] = [5, 20]

    std::cout << result << '\n';
}
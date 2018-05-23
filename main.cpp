#include <iostream>
#include <real/real.hpp>
#include <real/third_part.hpp>

int main() {

    boost::real::real a(15);
    a.add_number<boost::real::third_part>();

    boost::real::real b(15, {1,2,3,4,5,6,7,8});

    a.print();
    b.print();

    boost::real::real c(15, {9,9,9,9,9,9});
    boost::real::real d(15, {9,9,9,9,9,9});

    boost::real::real e(c + d);
    e.print();

    boost::real::real::iterator it = e.begin();

    for(int i = 0; i < 10; ++i) {
        std::cout << "lower bound: 0.";
        for (auto& l : it.get_lower_bound()) {
            std::cout << l << "";
        }

        std::cout << std::endl;

        std::cout << "upper bound: 0.";
        for (auto& l : it.get_upper_bound()) {
            std::cout << l << "";
        }

        std::cout << std::endl;
        ++it;
    }
    return 0;
}
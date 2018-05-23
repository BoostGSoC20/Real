#include <iostream>
#include <real/real.hpp>
#include <real/third_part.hpp>

int main() {

    boost::real::real a(15);
    a.add_number<boost::real::third_part>();
    boost::real::real c(15, {9,9,9,9,9,9});
    boost::real::real d(15, {9,9,9,9,9,9});
    boost::real::real e(c + d);

    a.print();
    c.print();
    d.print();

    boost::real::real::iterator it = e.begin();
    for(int i = 0; i < 10; ++i) {
        it.print();
        std::cout << std::endl;
        ++it;
    }
    return 0;
}
#include <iostream>
#include <real/real.hpp>
#include <real/third_part.hpp>

int main() {

    boost::real::real a;
    a.add_number<boost::real::third_part>();
    boost::real::real c({9,9,9,9,9,9});
    boost::real::real d({9,9,9,9,9,9});
    boost::real::real e(c + d);

    a.print(3);
    c.print(3);
    d.print(3);

    boost::real::real::iterator it = e.begin();
    for(int i = 0; i < 10; ++i) {
        it.print();
        std::cout << std::endl;
        ++it;
    }
    return 0;
}
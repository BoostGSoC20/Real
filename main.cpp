#include <iostream>
#include <real/real.hpp>
#include <real/third_part.hpp>

int main() {

    boost::real::real a(15);
    a.add_number<boost::real::third_part>();

    boost::real::real b(15, {1,2,3,4,5,6,7,8});

    a.print();
    b.print();

    boost::real::real c(15, {4,4,4,4,4,5});
    boost::real::real d(15, {3,5,5,5,5,5});

    boost::real::real e(c + d);
    e.print();
    return 0;
}
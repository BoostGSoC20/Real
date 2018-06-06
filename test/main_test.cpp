#include <iostream>
#include <real/real.hpp>
#include <real/third_part.hpp>

int main() {
    int i;
    boost::real::real a,b,c,d,e,f,g,g2,h,j,k;

    a = boost::real::real(boost::real::third_part());
    c = boost::real::real({9,9,9,9,9,9});
    d = boost::real::real({9,9,9,9,9,9});
    e = c + d;

    std::cout << "a get_nth_digit: " << a.get_nth_digit(2) << std::endl;
    std::cout << "function: " << boost::real::third_part()(2) << std::endl;

    std::cout << "a: ";
    a.print(3);
    std::cout << std::endl;
    std::cout << "c: ";
    c.print(3);
    std::cout << std::endl;
    std::cout << "d: ";
    d.print(3);
    std::cout << std::endl;

    boost::real::real::const_precision_iterator it = e.cbegin();
    for(i = 0; i < 10; ++i) {
        it.print();
        std::cout << std::endl;
        ++it;
    }

    f = boost::real::real({9,9,9,9,9,9});
    g = boost::real::real({9,9,9,9,9,8});

    if (g < f) {
        std::cout << "g < f --> true" << std::endl;
    } else {
        std::cout << "g < f --> false" << std::endl;
    }

    h = f - g;

    std::cout << "h: ";
    h.print(15);
    std::cout << std::endl;
    std::cout << "f: ";
    f.print(15);
    std::cout << std::endl;
    std::cout << "g: ";
    g.print(15);
    std::cout << std::endl;

    j = boost::real::real({9,9,9,8,9,9,9});

    for (i = 0; i < 10; ++i) {
        std::cout << "j:";
        j.print(i);
        std::cout << std::endl;
    }

    k = boost::real::real({9,9,9,7,9,9,9});

    for (i = 0; i < 10; ++i) {
        std::cout << "k:";
        k.print(i);
        std::cout << std::endl;
    }

    g2 = g;

    try {
        if (g < g2) {
            std::cout << "Error, equal numbers should throw precision_exception" << std::endl;
        }
    } catch (boost::real::precision_exception& e) {
        std::cout << "g < g correctly throws: " << e.what() << std::endl;
    }

    return 0;
}
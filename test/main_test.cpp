#include <iostream>
#include <real/real.hpp>
#include <real/third_part.hpp>

int main() {
    int i;
    boost::real::real a,b,c,d,e,f,g,g2,h,j,k,l,m;
    boost::real::real::const_precision_iterator it;

    c = boost::real::real({9,9,9,9,9,9});
    d = boost::real::real({9,9,9,9,9,9});
    e = c + d;

    std::cout << "c: " << c << std::endl;

    it = d.cbegin();
    for(i = 0; i < 10; ++i) {
        std::cout << "d: " << it << std::endl;
        ++it;
    }

    it = e.cbegin();
    for(i = 0; i < 10; ++i) {
        std::cout << "e: " << it << std::endl;
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

    std::cout << "h: " << h << std::endl;
    std::cout << "f: " << f << std::endl;
    std::cout << "g: " << g << std::endl;

    j = boost::real::real({9,9,9,8,9,9,9});

    it = j.cbegin();
    for (i = 0; i < 10; ++i) {
        std::cout << "j: " << it << std::endl;
        ++it;
    }

    k = boost::real::real({9,9,9,7,9,9,9});

    it = k.cbegin();
    for (i = 0; i < 10; ++i) {
        std::cout << "j:" << it << std::endl;
        ++it;
    }

    g2 = g;

    /*
    try {
        if (g < g2) {
            std::cout << "Error, equal numbers should throw precision_exception" << std::endl;
        }
    } catch (boost::real::precision_exception& e) {
        std::cout << "g < g correctly throws: " << e.what() << std::endl;
    } */

    l = boost::real::real({1,1,1}, false);
    m = boost::real::real({1,2}, false);

    std::cout << "l: " << l << std::endl;
    std::cout << "l: " << (l + m) << std::endl;

    return 0;
}
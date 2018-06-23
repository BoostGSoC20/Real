#include <iostream>
#include <real/real.hpp>
#include <real/third_part.hpp>

int main() {
    int i;
    boost::real::real a,b,c,d,e,f,g,g2,h,j,k,l,m;
    boost::real::real::const_precision_iterator it;

    c = boost::real::real({0,9,9,9,9,9,9}, 1);
    d = boost::real::real({0,9,9,9,9,9,9}, 1);
    e = c + d;

    std::cout << "c: " << c << std::endl;

    it = d.cbegin();
    for(i = 0; i < 10; ++i) {
        std::cout << "d: " << it.range << std::endl;
        ++it;
    }

    it = e.cbegin();
    for(i = 0; i < 10; ++i) {
        std::cout << "e: " << it.range << std::endl;
        ++it;
    }

    f = boost::real::real({0,9,9,9,9,9,9}, 1);
    g = boost::real::real({0,9,9,9,9,9,8}, 1);

    if (g < f) {
        std::cout << "g < f --> true" << std::endl;
    } else {
        std::cout << "g < f --> false" << std::endl;
    }

    std::cout << "f: " << f << std::endl;
    std::cout << "g: " << g << std::endl;
    std::cout << "f - g: " << (f - g) << std::endl;
    std::cout << "g - f: " << (g - f) << std::endl;
    std::cout << "f + g: " << (f + g) << std::endl;
    std::cout << "g + f: " << (g + f) << std::endl;

    j = boost::real::real({0,9,9,9,8,9,9,9}, 1);

    it = j.cbegin();
    for (i = 0; i < 10; ++i) {
        std::cout << "j: " << it.range << std::endl;
        ++it;
    }

    k = boost::real::real({0,9,9,9,7,9,9,9}, 1);

    it = k.cbegin();
    for (i = 0; i < 10; ++i) {
        std::cout << "j:" << it.range << std::endl;
        ++it;
    }

    g2 = g;

    try {
        if (g < g2) {
            std::cout << "Error, equal numbers should throw precision_exception" << std::endl;
        }
    } catch (boost::real::precision_exception& e) {
        std::cout << "g < g correctly throws: " << e.what() << std::endl;
    }

    l = boost::real::real({0,1,1,1}, 1, false);
    m = boost::real::real({0,1,2}, 1, false);

    std::cout << "l: " << l << std::endl;
    std::cout << "l: " << (l + m) << std::endl;

    if (m < l) {
        std::cout << "m < l --> True" << std::endl;
    } else {
        std::cout << "m < l --> Falses" << std::endl;
    }

    return 0;
}
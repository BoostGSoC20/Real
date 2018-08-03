#include <iostream>
#include <real/real.hpp>

int main() {

    std::vector<int> aa = {3,2};
    std::vector<int> bb = {1,2};
    std::vector<int> cc;
    int exponent_cc = boost::real::helper::multiply_vectors(aa,2,bb,2,cc);


    std::cout << "cc: " << exponent_cc << " - ";
    for (auto& c: cc) {
        std::cout << c;
    }

    std::cout << std::endl;



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

    std::cout << "e: " << e << std::endl;

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
    std::cout << "g * f: " << (g * f) << std::endl;
    std::cout << "f * g: " << (f * g) << std::endl;

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
        std::cout << "m < l --> False" << std::endl;
    }

    boost::real::real t_a([](uint n) { if (n == 0) return 0; else return 3; }, 1);
    boost::real::real t_b([](uint n) { if (n == 0) return 0; else return 9; }, 1);

    std::cout << "t_a: " << t_a << std::endl;
    std::cout << "t_b: " << t_b << std::endl;
    std::cout << "t_b + t_a: " << (t_b + t_a) << std::endl;
    std::cout << "t_a + t_b: " << (t_a + t_b) << std::endl;
    std::cout << "t_b - t_a: " << (t_b - t_a) << std::endl;
    std::cout << "t_a - t_b: " << (t_a - t_b) << std::endl;

    // Some non trivial tree operation number

    boost::real::real c_a({2});
    boost::real::real c_b({1,5}, 1);
    boost::real::real c_c({0,5}, 1);
    boost::real::real c_d({3,5}, 1, false);
    boost::real::real c_e({2}, false);
    boost::real::real c_f({1}, false);

    std::cout << "0.5 + 2 * 1.5 --> " << (c_c + c_a * c_b) << std::endl;
    std::cout << "-1 * (0.5 + 2 * 1.5) --> " << (c_f * (c_c + c_a * c_b)) << std::endl;
    std::cout << "-3.5 + -2.0 --> " << (c_d + c_e) << std::endl;
    std::cout << "-3.5 * -2.0 --> " << (c_d * c_e) << std::endl;

    std::vector<int> d_a = {4,8,0};
    std::vector<int> d_b = {1,5};
    std::vector<int> result;

    boost::real::helper::divide_vectors(d_a, 3, d_b, 2, result);

    std::cout << "r: ";
    for(auto& r: result) {
        std::cout << r;
    }
    std::cout << std::endl;

    return 0;
}
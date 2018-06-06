#ifndef BOOST_REAL_THIRD_PART_H
#define BOOST_REAL_THIRD_PART_H

#include <real/number.hpp>

namespace boost {
    namespace real {
        struct third_part: public boost::real::number {
            third_part() = default;

            int get_nth_digit(int n) const override { return 3; }
            int operator()(int n) const { return 3; }
        };
    }
}

#endif //BOOST_REAL_THIRD_PART_H

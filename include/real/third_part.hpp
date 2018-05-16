#ifndef BOOST_REAL_THIRD_PART_H
#define BOOST_REAL_THIRD_PART_H

#include <real/number.hpp>

namespace boost {
    namespace real {
        class third_part: public boost::real::number {
        public:
            third_part() = default;

            int get_nth_digit(unsigned int n) const { return 3; }
        };
    }
}

#endif //BOOST_REAL_THIRD_PART_H

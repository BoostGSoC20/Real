#ifndef BOOST_REAL_NUMBER_H
#define BOOST_REAL_NUMBER_H

namespace boost {
    namespace real {
        class number {
        public:
            virtual ~number() {};
            virtual int get_nth_digit(int n) const = 0;
        };
    }
}

#endif //BOOST_REAL_NUMBER_H

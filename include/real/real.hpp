#ifndef BOOST_REAL_REAL_HPP
#define BOOST_REAL_REAL_HPP

namespace boost {
    namespace real {
        class real {
        public:
            real();
            real(const real&);

            real& operator+=(const real$ rhs);
            real& operator-=(const real$ rhs);
            real& operator*=(const real$ rhs);
            real& operator/=(const real$ rhs);

            int get_nth_digit();
        };
    }
}

#endif //BOOST_REAL_REAL_HPP

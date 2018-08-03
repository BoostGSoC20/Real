#ifndef BOOST_REAL_UTILS_HPP
#define BOOST_REAL_UTILS_HPP

#include <real/real.hpp>
#include <sstream>

namespace boost {
    namespace real {
        std::string to_string(const boost::real::real& r) {
            std::stringstream f;
            f << r;
            return f.str();
        }
    }
}

#endif //BOOST_REAL_UTILS_HPP

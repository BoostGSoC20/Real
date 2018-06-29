#ifndef BOOST_REAL_REAL_EXCEPTION_HPP
#define BOOST_REAL_REAL_EXCEPTION_HPP

#include <exception>

namespace boost {
    namespace real {
        struct precision_exception : public std::exception {

            const char * what () const throw () override {
                return "The boost::real number precision is to slow to compare both numbers";
            }
        };

        struct none_operation_exception : public std::exception {

            const char * what () const throw () override {
                return "The boost::real number operation cannot be NONE";
            }
        };
    }
}

#endif //BOOST_REAL_REAL_EXCEPTION_HPP

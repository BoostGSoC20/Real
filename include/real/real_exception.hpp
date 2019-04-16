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

        struct invalid_representation_exception : public std::exception {

            const char * what () const throw () override {
                return "The boost::real number method cannot be called for real number for the current representation";
            }
        };

        struct invalid_string_number_exception : public std::exception {

            const char * what () const throw () override {
                return "The string passed to construct the boost::real number is invalid";
            }
        };
    }
}

#endif //BOOST_REAL_REAL_EXCEPTION_HPP

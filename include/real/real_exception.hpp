#ifndef BOOST_REAL_REAL_EXCEPTION_HPP
#define BOOST_REAL_REAL_EXCEPTION_HPP

#include <exception>

namespace boost {
    namespace real {
        struct precision_exception : public std::exception {
            const char * what () const throw () override {
                return "The boost::real number precision is too slow to compare both numbers";
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

        struct bad_variant_access_exception: public std::exception {
            const char * what () const throw () override {
                return "Cannot perform this method on this real variant type";
            }
        };

        struct divide_by_zero : public std::exception {
            const char * what () const throw () override {
                return "Divison by zero is undefined";
            }
        };

        struct divergent_division_result_exception : public std::exception {
            const char * what () const throw () override {
                return "The divisor approximation interval contains 0, so the quotient is unbounded";
            }
        };

        struct pi_precision_exception : public std::exception {
            const char * what () const throw () override {
                return "pi is currently undefined for precision > 2000 digits";
            }
        };

        struct invalid_distribution_operation_exception : public std::exception {

            const char * what () const throw () override {
                return "Distribution does not work for this operation.";
            }
        };

        struct exponent_overflow_exception : public std::exception {

            const char * what () const throw () override {
                return "The current precision exceeds the bounds of the exponent type";
            }
        };

        struct octal_input_not_supported_exception : public std::exception {

            const char * what () const throw () override {
                return "The string input began with 0 - octal input is not supported at this time";
                        
            }
        };

        struct invalid_recursion_level_exception : public std::exception {

            const char * what () const throw () override {
                return "Distributing with this recursion level is undefined.";
                        
            }
        };

        struct integer_contructor_for_non_integer_type : public std::exception {
            const char * what () const throw () override {
                return "Constructor of Integer type number is called for a non Integer type number";
            }
        };

        struct expected_real_integer_type_number : public std::exception {
            const char * what() const throw () override {
                return "Expected a integer type number but got a non-integer type number";
            }
        };

        struct expected_real_rational_type_number : public std::exception {
            const char * what() const throw () override {
                return "Expected a rational type number but got a non-rational type number";
            }
        };

        struct constructin_real_algorithm_or_real_operation_using_string : public std::exception {
            const char * what() const throw () override {
                return "Can not construct a real_algorithm or real_operation type from a string";
            }
        };

    }
}

#endif //BOOST_REAL_REAL_EXCEPTION_HPP

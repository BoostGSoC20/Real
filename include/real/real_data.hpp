#ifndef BOOST_REAL_REAL_DATA_HPP
#define BOOST_REAL_REAL_DATA_HPP

#include <variant>
#include <assert.h>
#include <iostream>

#include <real/const_precision_iterator.hpp>
#include <real/interval.hpp>
#include <real/real_explicit.hpp>
#include <real/real_algorithm.hpp>
#include <real/real_operation.hpp>
#include <real/real_exception.hpp>

namespace boost { 
    namespace real{

        class real_data {
            real_number _real;
            const_precision_iterator _precision_itr;

            public:
            /// @TODO: use move constructors, if possible
            
            real_data() = default;
            
            /// copy ctor - constructs real_data from other real_data
            real_data(const real_data &other) : _real(other._real), _precision_itr(other._precision_itr) {};

            // construct from the three different reals 
            real_data(real_explicit x) :_real(x), _precision_itr(&_real) {};
            real_data(real_algorithm x) : _real(x), _precision_itr(&_real) {};
            real_data(real_operation x) : _real(x), _precision_itr(&_real) {};

            const real_number& get_real_number() const {
                return _real;
            }

            const_precision_iterator& get_precision_itr() {
                return _precision_itr;
            }
        };

        // Now that real_data and const_precision_iterator have been defined, we may now define the following.

        /* const_precision_iterator member functions */
        /// determines a real_operation's approximation interval from its operands'
        void const_precision_iterator::update_operation_boundaries(real_operation &ro) {
            switch (ro.get_operation()) {
                case OPERATION::ADDITION:
                        this->_approximation_interval.lower_bound = ro.get_lhs_itr().get_interval().lower_bound +
                                                                    ro.get_rhs_itr().get_interval().lower_bound;

                        this->_approximation_interval.upper_bound = ro.get_lhs_itr().get_interval().upper_bound +
                                                                    ro.get_rhs_itr().get_interval().upper_bound;
                    break;


                case OPERATION::SUBTRACTION:
                            this->_approximation_interval.lower_bound =
                                ro.get_lhs_itr().get_interval().lower_bound -
                                ro.get_rhs_itr().get_interval().upper_bound;

                            this->_approximation_interval.upper_bound =
                                ro.get_lhs_itr().get_interval().upper_bound -
                                ro.get_rhs_itr().get_interval().lower_bound;
                    break;


                case OPERATION::MULTIPLICATION: {
                    bool lhs_positive = ro.get_lhs_itr().get_interval().positive();
                    bool rhs_positive = ro.get_rhs_itr().get_interval().positive();
                    bool lhs_negative = ro.get_lhs_itr().get_interval().negative();
                    bool rhs_negative = ro.get_rhs_itr().get_interval().negative();

                    if (lhs_positive && rhs_positive) { // Positive - Positive
                                this->_approximation_interval.lower_bound = 
                                    ro.get_lhs_itr().get_interval().lower_bound *
                                    ro.get_rhs_itr().get_interval().lower_bound;

                                this->_approximation_interval.upper_bound =
                                    ro.get_lhs_itr().get_interval().upper_bound *
                                    ro.get_rhs_itr().get_interval().upper_bound;

                    } else if (lhs_negative && rhs_negative) { // Negative - Negative
                                this->_approximation_interval.lower_bound = 
                                    ro.get_lhs_itr().get_interval().upper_bound *
                                    ro.get_rhs_itr().get_interval().upper_bound;

                                this->_approximation_interval.upper_bound =
                                    ro.get_lhs_itr().get_interval().lower_bound *
                                    ro.get_rhs_itr().get_interval().lower_bound;
                    } else if (lhs_negative && rhs_positive) { // Negative - Positive
                                this->_approximation_interval.lower_bound =
                                    ro.get_lhs_itr().get_interval().lower_bound *
                                    ro.get_rhs_itr().get_interval().upper_bound;

                                this->_approximation_interval.upper_bound =
                                    ro.get_lhs_itr().get_interval().upper_bound *
                                    ro.get_rhs_itr().get_interval().lower_bound;

                    } else if (lhs_positive && rhs_negative) { // Positive - Negative
                                this->_approximation_interval.lower_bound =
                                    ro.get_lhs_itr().get_interval().upper_bound *
                                    ro.get_rhs_itr().get_interval().lower_bound;

                                this->_approximation_interval.upper_bound =
                                    ro.get_lhs_itr().get_interval().lower_bound *
                                    ro.get_rhs_itr().get_interval().upper_bound;

                    } else { // One is around zero all possible combinations are be tested

                        exact_number current_boundary;

                        // Lower * Lower
                                current_boundary = 
                                    ro.get_lhs_itr().get_interval().lower_bound *
                                    ro.get_rhs_itr().get_interval().lower_bound;

                        this->_approximation_interval.lower_bound = current_boundary;
                        this->_approximation_interval.upper_bound = current_boundary;

                        // Upper * upper
                                current_boundary = 
                                ro.get_lhs_itr().get_interval().upper_bound *
                                ro.get_rhs_itr().get_interval().upper_bound;

                        if (current_boundary < this->_approximation_interval.lower_bound) {
                            this->_approximation_interval.lower_bound = current_boundary;
                        }

                        if (this->_approximation_interval.upper_bound < current_boundary) {
                            this->_approximation_interval.upper_bound = current_boundary;
                        }

                        // Lower * upper
                                current_boundary =
                                ro.get_lhs_itr().get_interval().lower_bound *
                                ro.get_rhs_itr().get_interval().upper_bound;

                        if (current_boundary < this->_approximation_interval.lower_bound) {
                            this->_approximation_interval.lower_bound = current_boundary;
                        }

                        if (this->_approximation_interval.upper_bound < current_boundary) {
                            this->_approximation_interval.upper_bound = current_boundary;
                        }

                        // Upper * lower
                                current_boundary =
                                    ro.get_lhs_itr().get_interval().upper_bound *
                                    ro.get_rhs_itr().get_interval().lower_bound;

                        if (current_boundary < this->_approximation_interval.lower_bound) {
                            this->_approximation_interval.lower_bound = current_boundary;
                        }

                        if (this->_approximation_interval.upper_bound < current_boundary) {
                            this->_approximation_interval.upper_bound = current_boundary;
                        }
                    }
                    break;
                }

                default:
                    throw boost::real::none_operation_exception();
            }
        }

        // remember to update afterwards
        // inits the precision of the real_operation, depending on those of its operands, to either
        // cbegin or cend.
        void const_precision_iterator::init_operation_itr(real_operation &ro, bool cend){
            if (cend) {
                ro.get_lhs_itr() = const_precision_iterator(ro.get_lhs_itr().cend());
                ro.get_rhs_itr() = const_precision_iterator(ro.get_rhs_itr().cend());
            } else {
                ro.get_lhs_itr() = const_precision_iterator(ro.get_lhs_itr().cbegin());
                ro.get_rhs_itr() = const_precision_iterator(ro.get_rhs_itr().cbegin());
            }
        }

        void const_precision_iterator::operation_iterate_n_times(real_operation &ro, int n) {
            /// @warning there could be issues if operands have different precisions/max precisions

            if (ro.get_lhs_itr()._precision < this->_precision + n)
                ro.get_lhs_itr().iterate_n_times(n);
            
            if (ro.get_rhs_itr()._precision < this->_precision + n)
                ro.get_rhs_itr().iterate_n_times(n);

            this->_precision += n;

            update_operation_boundaries(ro);
        }

        void const_precision_iterator::operation_iterate(real_operation &ro) {
            // only iterate if we must. If operand precision < this precision, then it must have
            // hit its maximum_precision. If operand precision == this precision, we try iterating. Otherwise,
            // it is == this->_precision + 1 (from being iterated elsewhere in the operation tree) and
            // we do not iterate again.

            if (ro.get_lhs_itr()._precision == this->_precision)
                ++(ro.get_lhs_itr());
            
            if (ro.get_rhs_itr()._precision == this->_precision)
                ++(ro.get_rhs_itr());

            (this->_precision)++;

            update_operation_boundaries(ro);
        }

        /* real_operation member functions */

        // note that we return a reference. It is necessary, for now, since iterating operands 
        // (see operation_iterate, above) REQUIRES modifying the operands' precision iterators
        const_precision_iterator& real_operation::get_lhs_itr() {
            return _lhs->get_precision_itr();
        }
        
        const_precision_iterator& real_operation::get_rhs_itr() {
            return _rhs->get_precision_itr();
        }
    }
}

#endif // BOOST_REAL_REAL_DATA_HPP 

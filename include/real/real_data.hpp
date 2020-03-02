#ifndef BOOST_REAL_REAL_DATA_HPP
#define BOOST_REAL_REAL_DATA_HPP

#include <variant>
#include <assert.h>
#include <iostream>
#include <limits>

#include <real/const_precision_iterator.hpp>
#include <real/interval.hpp>
#include <real/real_explicit.hpp>
#include <real/real_algorithm.hpp>
#include <real/real_operation.hpp>
#include <real/real_exception.hpp>

namespace boost { 
    namespace real{

        template <typename T = int>
        class real_data {
            real_number<T> _real;
            const_precision_iterator<T> _precision_itr;

            public:
            /// @TODO: use move constructors, if possible
            
            real_data() = default;
            
            /// copy ctor - constructs real_data from other real_data
            real_data(const real_data<T> &other) : _real(other._real), _precision_itr(other._precision_itr) {};

            // construct from the three different reals 
            real_data(real_explicit<T> x) :_real(x), _precision_itr(&_real) {};
            real_data(real_algorithm<T> x) : _real(x), _precision_itr(&_real) {};
            real_data(real_operation<T> x) : _real(x), _precision_itr(&_real) {};

            const real_number<T>& get_real_number() const {
                return _real;
            }

            real_number<T> const * get_real_ptr() const {
                return &_real;
            }

            const_precision_iterator<T>& get_precision_itr() {
                return _precision_itr;
            }
        };

        // Now that real_data and const_precision_iterator have been defined, we may now define the following.
        // Note these are all inline to avoid linker issues.

        /* const_precision_iterator member functions */
        /// determines a real_operation's approximation interval from its operands'
        template <typename T>
        inline void const_precision_iterator<T>::update_operation_boundaries(real_operation<T> &ro) {
            switch (ro.get_operation()) {
                case OPERATION::ADDITION:
                    this->_approximation_interval.lower_bound =
                            ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false) +
                            ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);

                    this->_approximation_interval.upper_bound =
                            ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true) +
                            ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);
                    break;


                case OPERATION::SUBTRACTION:
                    this->_approximation_interval.lower_bound =
                            ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false) -
                            ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);

                    this->_approximation_interval.upper_bound =
                            ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true) -
                            ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);
                    break;

                case OPERATION::MULTIPLICATION: {
                    bool lhs_positive = ro.get_lhs_itr().get_interval().positive();
                    bool rhs_positive = ro.get_rhs_itr().get_interval().positive();
                    bool lhs_negative = ro.get_lhs_itr().get_interval().negative();
                    bool rhs_negative = ro.get_rhs_itr().get_interval().negative();

                    if (lhs_positive && rhs_positive) { // Positive - Positive
                        this->_approximation_interval.lower_bound =
                                ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false) *
                                ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);

                        this->_approximation_interval.upper_bound =
                                ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true) *
                                ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);

                    } else if (lhs_negative && rhs_negative) { // Negative - Negative
                        this->_approximation_interval.lower_bound =
                                ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true) *
                                ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);

                        this->_approximation_interval.upper_bound =
                                ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false) *
                                ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);
                    } else if (lhs_negative && rhs_positive) { // Negative - Positive
                        this->_approximation_interval.lower_bound =
                                ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false) *
                                ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);

                        this->_approximation_interval.upper_bound =
                                ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true) *
                                ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);

                    } else if (lhs_positive && rhs_negative) { // Positive - Negative
                        this->_approximation_interval.lower_bound =
                                ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true) *
                                ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);

                        this->_approximation_interval.upper_bound =
                                ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false) *
                                ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);

                    } else { // One is around zero all possible combinations are be tested

                        exact_number<T> current_boundary;

                        // Lower * Lower
                        current_boundary =
                                ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false) *
                                ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);

                        this->_approximation_interval.lower_bound = current_boundary;
                        this->_approximation_interval.upper_bound = current_boundary;

                        // Upper * upper
                        current_boundary =
                                ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true) *
                                ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);

                        if (current_boundary < this->_approximation_interval.lower_bound) {
                            this->_approximation_interval.lower_bound.up_to(_precision, false) = current_boundary;
                        }

                        if (this->_approximation_interval.upper_bound < current_boundary) {
                            this->_approximation_interval.upper_bound = current_boundary;
                        }

                        // Lower * upper
                        current_boundary =
                                ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false) *
                                ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);

                        if (current_boundary < this->_approximation_interval.lower_bound.up_to(_precision, false)) {
                            this->_approximation_interval.lower_bound = current_boundary;
                        }

                        if (this->_approximation_interval.upper_bound < current_boundary) {
                            this->_approximation_interval.upper_bound = current_boundary;
                        }

                        // Upper * lower
                        current_boundary =
                                ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true) *
                                ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);

                        if (current_boundary < this->_approximation_interval.lower_bound.up_to(_precision, false)) {
                            this->_approximation_interval.lower_bound = current_boundary;
                        }

                        if (this->_approximation_interval.upper_bound < current_boundary) {
                            this->_approximation_interval.upper_bound = current_boundary;
                        }
                    }
                    break;
                }
                case OPERATION::DIVISION: {
                    T base = (std::numeric_limits<T>::max() / 4) * 2 - 1;
                    exact_number<T> zero = exact_number<T>();
                    exact_number<T> residual;
                    exact_number<T> quotient;
                    exact_number<T> numerator;
                    exact_number<T> denominator;

                    // if the interval contains zero, iterate until it doesn't, or until maximum_precision.
                    while (!ro.get_rhs_itr().get_interval().positive() &&
                           !ro.get_rhs_itr().get_interval().negative() &&
                           _precision <= this->maximum_precision())
                        ++(*this);

                    // if the interval contains zero after iterating until max precision, throw,
                    // because this causes one side of the result interval to tend towards +/-infinity
                    if (!ro.get_rhs_itr().get_interval().positive() &&
                        !ro.get_rhs_itr().get_interval().negative())
                        throw boost::real::divergent_division_result_exception();

                    // Q = N/D
                    // first, the upper boundary
                    if (ro.get_lhs_itr().get_interval().positive()) {
                        if (ro.get_rhs_itr().get_interval().positive()) {
                            numerator = ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true);
                            denominator = ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);
                        } else {
                            numerator = ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false);
                            denominator = ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);
                        }
                    } else if (ro.get_lhs_itr().get_interval().negative()) {
                        if (ro.get_rhs_itr().get_interval().positive()) {
                            numerator = ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true);
                            denominator = ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);
                        } else if (ro.get_rhs_itr().get_interval().negative()) {
                            numerator = ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false);
                            denominator = ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);
                        }
                    } else {
                        if (ro.get_rhs_itr().get_interval().positive()) {
                            numerator = ro.get_lhs_itr().get_interval().upper_bound.up_to(_precision, true);
                            denominator = ro.get_rhs_itr().get_interval().upper_bound.up_to(_precision, true);
                        } else if (ro.get_rhs_itr().get_interval().negative()) {
                            numerator = ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false);
                            denominator = ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);
                        }
                    }

                    // calculate the upper bound
                    quotient = numerator;
                    quotient.divide_vector(denominator, this->maximum_precision());

                    residual = quotient * denominator - numerator;
                    residual.normalize();
                    quotient.normalize();

                    this->_approximation_interval.upper_bound = quotient;

                    if (residual.abs() > zero) {
                        this->_approximation_interval.upper_bound.round_up(base);
                    }
                    // if both operands are numbers (not intervals), then we can skip doing the lower bound separately
                    if (ro.get_rhs_itr().get_interval().is_a_number() &&
                        ro.get_lhs_itr().get_interval().is_a_number()) {
                        _approximation_interval.lower_bound = quotient;
                        if (residual == zero) {
                            _approximation_interval.upper_bound = _approximation_interval.lower_bound;
                        } else {
                            _approximation_interval.lower_bound.round_down(base);
                        }
                        return;
                    }

                    // lower boundary
                    if (ro.get_lhs_itr().get_interval().positive()) {
                        if (ro.get_rhs_itr().get_interval().positive()) {
                            numerator = ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false);
                            denominator = ro.get_rhs_itr().get_interval().upper_bound;
                        } else {
                            numerator = ro.get_lhs_itr().get_interval().upper_bound;
                            denominator = ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);
                        }
                    } else if (ro.get_lhs_itr().get_interval().negative()) {
                        if (ro.get_rhs_itr().get_interval().positive()) {
                            numerator = ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false);
                            denominator = ro.get_rhs_itr().get_interval().upper_bound;
                        } else if (ro.get_rhs_itr().get_interval().negative()) {
                            numerator = ro.get_lhs_itr().get_interval().upper_bound;
                            denominator = ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);
                        }
                    } else {
                        if (ro.get_rhs_itr().get_interval().positive()) {
                            numerator = ro.get_lhs_itr().get_interval().lower_bound.up_to(_precision, false);
                            denominator = ro.get_rhs_itr().get_interval().lower_bound.up_to(_precision, false);
                        } else if (ro.get_rhs_itr().get_interval().negative()) {
                            numerator = ro.get_lhs_itr().get_interval().upper_bound;
                            denominator = ro.get_rhs_itr().get_interval().upper_bound;
                        }
                    }

                    quotient = numerator;
                    quotient.divide_vector(denominator, this->maximum_precision());

                    residual = quotient * denominator - numerator;
                    residual.normalize();
                    quotient.normalize();

                    this->_approximation_interval.lower_bound = quotient;

                    if (residual.abs() > zero) {
                        this->_approximation_interval.lower_bound.round_down(base);
                    }

                    if (this->_approximation_interval.lower_bound > this->_approximation_interval.upper_bound)
                        this->_approximation_interval.swap_bounds();

                    break;
                }

                default:
                    throw boost::real::none_operation_exception();
            }
        }

        template <typename T>
        inline void const_precision_iterator<T>::operation_iterate_n_times(real_operation<T> &ro, int n) {
            /// @warning there could be issues if operands have different precisions/max precisions

            if (ro.get_lhs_itr()._precision < this->_precision + n) {
                ro.get_lhs_itr().iterate_n_times(n);
            }
            
            if (ro.get_rhs_itr()._precision < this->_precision + n) {
                ro.get_rhs_itr().iterate_n_times(n);
            }

            this->_precision += n;

            update_operation_boundaries(ro);
        }

        template <typename T>
        inline void const_precision_iterator<T>::operation_iterate(real_operation<T> &ro) {
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
        template <typename T>
        inline const_precision_iterator<T>& real_operation<T>::get_lhs_itr() {
            return _lhs->get_precision_itr();
        }

        template <typename T>
        inline const_precision_iterator<T>& real_operation<T>::get_rhs_itr() {
            return _rhs->get_precision_itr();
        }
    }
}

#endif // BOOST_REAL_REAL_DATA_HPP 

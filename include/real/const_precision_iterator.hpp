#ifndef BOOST_CONST_PRECISION_ITERATOR_HPP
#define BOOST_CONST_PRECISION_ITERATOR_HPP

#include <real/interval.hpp>
#include <real/real_explicit.hpp>
#include <real/real_algorithm.hpp>
#include <real/real_operation.hpp>
#include <real/exact_number.hpp>
#include <real/real_exception.hpp>
#include<real/integer_number.hpp>
#include<real/rational_number.hpp>
#include <limits>
#include <memory>
#include <variant>
#include <assert.h>
#include <iterator>
#include <optional>

namespace boost {
    namespace real{
    /**
     * @file The const_precision_iterator provides the functionality to iterate through precision intervals
     * of all three kinds of reals
     * 
     * @note variant and visit/visitors are used extensively in this implementation
     * @TODO: consider doing traversals to lower the demands of recursion
     * @sa documention on std::variant, std::visit
     */
        template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
        template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
        // fwd decl
        template <typename T>
        class real;

        template <typename T>
        using real_number = std::variant<std::monostate, real_explicit<T>, real_algorithm<T>, real_operation<T>, integer<T>, rational_number<T>>;
        using precision_t = size_t;

        /// the default max precision to use if the user hasn't provided one.
        const precision_t DEFAULT_MAXIMUM_PRECISION = 10;

        template <typename T>
        class const_precision_iterator {
            public:
            /**
             * @brief Optional user-provided maximum precision for all const_precision_iterators. 
             */

            inline static std::optional<precision_t> global_maximum_precision;
            /// @TODO look into STL-style iterators
            // typedef std::forward_iterator_tag iterator_category;
            // typedef void difference_type (?);
            // typedef ??? value_type
            // typedef const value_type& reference (?) not necessary because const
            // typedef const value_type* pointer

            private:
                /**
                 * @brief this holds a ptr to explicit number, algorithmic number, or real_operation
                 */ 
                // raw pointer here is ok, precision iterator is always attached to the variant it points to
                // (refer to real_data.hpp). Any time the variant is destroyed, so is this pointer.
                real_number<T> * _real_ptr;

                /// current iterator precision
                precision_t _precision;

                /// local max precision, is used if set to > 0 by user
                precision_t _maximum_precision = 0;

                interval<T> _approximation_interval;

                void check_and_swap_boundaries() {
                    std::visit( overloaded { // perform operation on whatever is held in variant
                        [this] (real_explicit<T>& real) { 
                            if (!real.positive()) {
                            this->_approximation_interval.swap_bounds();
                            }
                        },
                        [this] (real_algorithm<T>& real) {
                            if (!real.positive()) {
                            this->_approximation_interval.swap_bounds();
                            }
                        },
                        [] (real_operation<T>& real) {
                            throw boost::real::bad_variant_access_exception();
                        },
                        [] (auto& real) {
                            throw boost::real::bad_variant_access_exception();
                        }
                    }, *_real_ptr);
                }

            public:
                /**
                 * @brief Returns the maximum allowed precision, if that precision is reached and an
                 * operator needs more precision, a precision_exception should be thrown.
                 *
                 * @return an unsigned integer with the maximum allowed precision, which was either
                 * given by the user, or some default value.
                 *
                 * @details The user may set the maximum precision for any specific precision iterator.
                 * They may also set a general maximum precision (the static optional value).
                 * Preference is given: _maximum_precision > maximum_precision > DEFAULT_MAXIMUM_PRECISION
                 */
                precision_t maximum_precision() const {
                    if((_maximum_precision == 0) && !(global_maximum_precision))
                        return DEFAULT_MAXIMUM_PRECISION;
                    else if (_maximum_precision == 0)
                        return global_maximum_precision.value();
                    else
                        return _maximum_precision;
                }

                void set_maximum_precision(precision_t maximum_precision) {
                    this->_maximum_precision = maximum_precision;
                }

                /**
                 * @brief *Default constructor:*
                 * Constructs an empty real::const_precision_iterator that points to nullptr.
                 */
                const_precision_iterator() = default;

                /**
                 * @brief *Copy constructor:* Construct a new real::const_precision_iterator
                 * which is a copy of the other iterator.
                 *
                 * @param other - the real::const_precision_iterator to copy.
                 */
                const_precision_iterator(const const_precision_iterator& other) = default;


                // fwd decl'd. Definition found in real_data.hpp
                void update_operation_boundaries(real_operation<T> &ro);

                /**
                 * @brief Constructor for the least precise precision iterator
                 */ 
                explicit const_precision_iterator(real_number<T> * a) : _real_ptr(a), _precision(1) {
                    std::visit( overloaded { // perform operation on whatever is held in variant
                        [this] (real_explicit<T>& real) {
                            T base = (std::numeric_limits<T>::max() /4)*2 - 1;
                            this->_approximation_interval.lower_bound.exponent = real.exponent();
                            this->_approximation_interval.upper_bound.exponent = real.exponent();
                            this->_approximation_interval.lower_bound.positive = real.positive();
                            this->_approximation_interval.upper_bound.positive = real.positive();

                            T first_digit = real.digits()[0];
                            this->_approximation_interval.lower_bound.digits.push_back(first_digit);

                            if (first_digit == base) {
                                this->_approximation_interval.upper_bound.digits.push_back(1);
                                this->_approximation_interval.upper_bound.exponent++;
                            } else if (this->_precision < real.digits().size()) {
                                this->_approximation_interval.upper_bound.digits.push_back(first_digit + 1);
                            } else {
                                this->_approximation_interval.upper_bound.digits.push_back(first_digit);
                            }
                            this->check_and_swap_boundaries();
                        },

                        [this] (real_algorithm<T>& real) {
                            T base = (std::numeric_limits<T>::max() /4)*2 - 1;
                            this->_approximation_interval.lower_bound.exponent = real.exponent();
                            this->_approximation_interval.upper_bound.exponent = real.exponent();
                            this->_approximation_interval.lower_bound.positive = real.positive();
                            this->_approximation_interval.upper_bound.positive = real.positive();

                            T first_digit = real[0];
                            this->_approximation_interval.lower_bound.digits.push_back(first_digit);

                            if (first_digit == base) {
                                this->_approximation_interval.upper_bound.digits.push_back(1);
                                this->_approximation_interval.upper_bound.exponent++;
                            } else {
                                this->_approximation_interval.upper_bound.digits.push_back(first_digit + 1);
                            }
                            this->check_and_swap_boundaries();
                        },

                        [this] (real_operation<T>& real) {
                            // we don't need to init operands here - they *SHOULD* already be at cbegin or >
                            update_operation_boundaries(real);
                            // _maximum_precision = std::max(real.get_lhs_itr().maximum_precision(), real.get_rhs_itr().maximum_precision());
                            },
                        [] (auto& real) {
                            throw boost::real::bad_variant_access_exception();
                            }
                    }, *_real_ptr);
                }

                // fwd decl, defined in real_data.hpp
                void init_operation_itr(real_operation<T> &ro, bool cend);

                /**
                 * @brief Constructor for maximum_precision precision iterator, from real_number
                 */
                explicit const_precision_iterator(real_number<T> * a, bool cend) : _real_ptr(a) {
                    if (cend) {
                        std::visit( overloaded { // perform operation on whatever is held in variant
                            [this, &a] (real_explicit<T>& real) {
                                *this = const_precision_iterator(a);
                                this->iterate_n_times((int)real.digits().size() + 1);
                            },
                            [this, &a] (real_algorithm<T>& real) {
                                *this = const_precision_iterator(a);
                                this->iterate_n_times(this->maximum_precision() - 1);
                            },
                            [this] (real_operation<T>& real) {
                                init_operation_itr(real, true);
                                update_operation_boundaries(real);
                            },
                            [] (auto & real) {
                                throw boost::real::bad_variant_access_exception();
                            }
                        }, *_real_ptr);
                    } else {
                        *this = const_precision_iterator(a);
                    }
                }

                const_precision_iterator cbegin() const {
                    return const_precision_iterator(_real_ptr);
                }

                /**
                 * @brief Construct a new boost::real::const_precision_iterator that iterates the number
                 * approximation intervals in increasing order according to the approximation precision.
                 *
                 * The iterator starts pointing the interval with the maximum allowed precision.
                 *
                 * @return a boost::real::const_precision_iterator of the number.
                 */
                const_precision_iterator cend() {
                    this->iterate_n_times(this->maximum_precision() - _precision);
                    return *this;
                }

                interval<T> get_interval() const {
                    return _approximation_interval;
                }

                // fwd decl, defined in real_data.hpp
                void operation_iterate(real_operation<T> &ro);
                void operation_iterate_n_times(real_operation<T> &ro, int n);

                /**
                 * @brief It recalculates the approximation interval boundaries increasing the used
                 * precision, the new approximation interval is smaller than the current one.
                 */
                void operator++() {
                    std::visit( overloaded { // perform operation on whatever is held in variant
                        [this] (real_explicit<T>& real) { 
                            this->iterate_n_times(1);
                        },
                        [this] (real_algorithm<T>& real) {
                            this->iterate_n_times(1);
                        },
                        [this] (real_operation<T>& real) {
                            operation_iterate_n_times(real, 1);
                        },
                        [] (auto& real) {
                            throw boost::real::bad_variant_access_exception();
                        }
                    }, *_real_ptr);
                }

                void iterate_n_times(int n) {
                    std::visit( overloaded { // perform operation on whatever is held in variant
                        [this, &n] (real_explicit<T>& real) { 
                            if (this->_precision >= real.digits().size()) {
                                return;
                            }
                            T base = (std::numeric_limits<T>::max() /4)*2 - 1;
                           // If the number is negative, boundaries are interpreted as mirrored:
                           // First, the operation is made as positive, and after boundary calculation
                           // boundaries are swapped to come back to the negative representation.
                           this->check_and_swap_boundaries();

                           // If the explicit number just reaches the full precision (the end)
                           // then set both boundaries are equals.
                           if (this->_precision + n >= real.digits().size()) {
                               for(int i = this->_precision; i < (int)real.digits().size(); i++) {
                                   this->_approximation_interval.lower_bound.push_back(real.digits()[i]);
                               }
                               this->_approximation_interval.upper_bound = this->_approximation_interval.lower_bound;

                           } else {

                               // If the explicit number didn't reaches the full precision (the end)
                               // then the number interval is defined by truncation.

                               for(precision_t i = _precision; i < _precision + n; i++) {
                                   this->_approximation_interval.lower_bound.push_back(real.digits()[i]);
                               }

                               this->_approximation_interval.upper_bound.clear();
                               this->_approximation_interval.upper_bound.digits.resize(this->_approximation_interval.lower_bound.size());

                               int carry = 1;
                               for (int i = (int)this->_approximation_interval.lower_bound.size() - 1; i >= 0; --i) {
                                   if (this->_approximation_interval.lower_bound[i] + carry == base + 1) {
                                       this->_approximation_interval.upper_bound[i] = 0;
                                   } else {
                                       this->_approximation_interval.upper_bound[i] = this->_approximation_interval.lower_bound[i] + carry;
                                       carry = 0;
                                   }
                               }

                               if (carry > 0) {
                                   this->_approximation_interval.upper_bound.push_front(carry);
                                   this->_approximation_interval.upper_bound.exponent = this->_approximation_interval.lower_bound.exponent + 1;
                               } else {
                                   this->_approximation_interval.upper_bound.exponent = this->_approximation_interval.lower_bound.exponent;
                               }
                           }

                           // Left normalization of boundaries representation
                           this->_approximation_interval.lower_bound.normalize_left();
                           this->_approximation_interval.upper_bound.normalize_left();

                           this->check_and_swap_boundaries();
                           this->_precision = std::min(this->_precision + n, real.digits().size());
                        },
                        [this, &n] (real_algorithm<T>& real) {
                           // If the number is negative, bounds are interpreted as mirrored:
                           // First, the operation is made as positive, and after bound calculation
                           // bounds are swapped to come back to the negative representation.
                           T base = (std::numeric_limits<T>::max() /4)*2 - 1;
                           this->check_and_swap_boundaries();

                           for (int i = 0; i < n; i++) {
                               this->_approximation_interval.lower_bound.push_back((real)[this->_precision + i]);
                           }

                           this->_approximation_interval.upper_bound.clear();
                           this->_approximation_interval.upper_bound.digits.resize(this->_approximation_interval.lower_bound.size());
                           int carry = 1;
                           for (int i = (int)this->_approximation_interval.lower_bound.size() - 1; i >= 0; --i) {
                               if (this->_approximation_interval.lower_bound[i] + carry == base + 1) {
                                   this->_approximation_interval.upper_bound[i] = 0;
                               } else {
                                   this->_approximation_interval.upper_bound[i] = this->_approximation_interval.lower_bound[i] + carry;
                                   carry = 0;
                               }
                           }

                           if (carry > 0) {
                               this->_approximation_interval.upper_bound.push_front(carry);
                               this->_approximation_interval.upper_bound.exponent = this->_approximation_interval.lower_bound.exponent + 1;
                           } else {
                               this->_approximation_interval.upper_bound.exponent = this->_approximation_interval.lower_bound.exponent;
                           }

                           // Left normalization of boundaries representation
                           this->_approximation_interval.lower_bound.normalize_left();
                           this->_approximation_interval.upper_bound.normalize_left();

                           this->check_and_swap_boundaries();
                           this->_precision += n;
                        },
                        [this, &n] (real_operation<T>& real) {
                            operation_iterate_n_times(real, n);
                        },
                        [] (auto & real) {
                            throw boost::real::bad_variant_access_exception();
                        }
                    }, *_real_ptr);
                }

                /**
                 * @brief It compares by value equality; two real::const_precision_iterators
                 * are equals if they are pointing to the same real number and are in the same precision iteration.
                 *
                 * @param other - A real::const_precision_iterator that is the right side operand
                 * @return a bool that is true if and only if both iterators are equals.
                 */
                bool operator==(const const_precision_iterator& other) const{
                    // uninitialized iterators are never equals
                    if (this->_real_ptr == nullptr || other._real_ptr == nullptr) {
                        return false;
                    }

                    return (other._real_ptr == this->_real_ptr) && (other._approximation_interval == this->_approximation_interval);
                }

                /**
                 * @brief It compares by value not equal; two real::const_precision_iterators.
                 *
                 * @param other - A real::const_precision_iterator that is the right side operand
                 * @return a bool that is true if and only if both iterators are not equals.
                 */
                bool operator!=(const const_precision_iterator& other) const {
                    return !(*this == other);
                }
        };
    }
} 

#endif // BOOST_CONST_PRECISION_ITERATOR_HPP

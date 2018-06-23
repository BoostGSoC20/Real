#ifndef BOOST_REAL_REAL_HPP
#define BOOST_REAL_REAL_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <utility>

#include <real/real_exception.hpp>
#include <real/real_helpers.hpp>
#include <real/real_explicit.hpp>
#include <real/real_algorithm.hpp>


namespace boost {
    namespace real {

        class real {

            // Available operations
            enum class OPERATION {ADDITION, SUBTRACT, NONE};
            enum class KIND {EXPLICIT, OPERATION, ALGORITHM};

            KIND _kind = KIND::EXPLICIT;

            // Explicit number
            real_explicit _explicit_number;

            // Algorithmic number
            real_algorithm _algorithmic_number;

            // Composed number
            OPERATION _operation = OPERATION::NONE;
            real* _lhs_ptr = nullptr;
            real* _rhs_ptr = nullptr;

            void copy_operands(const real& other) {
                if (other._lhs_ptr != nullptr) {
                    this->_lhs_ptr = new real(*other._lhs_ptr);
                }

                if (other._rhs_ptr != nullptr) {
                    this->_rhs_ptr = new real(*other._rhs_ptr);
                }
            }

        public:

            class const_precision_iterator {
            private:

                // Internal number to iterate
                real const* _real_ptr = nullptr;

                // Explicit number iterator
                boost::real::real_explicit::const_precision_iterator _explicit_it;

                // Algorithmic number iterator
                boost::real::real_algorithm::const_precision_iterator _algorithmic_it;

                // If the number is a composition, the const_precision_iterator uses the operand iterators
                const_precision_iterator* _lhs_it_ptr = nullptr;
                const_precision_iterator* _rhs_it_ptr = nullptr;

                void calculate_operation_bounds() {

                    if (this->_real_ptr->_operation == OPERATION::ADDITION) {

                        boost::real::helper::add_boundaries(
                                this->_lhs_it_ptr->range.lower_bound,
                                this->_rhs_it_ptr->range.lower_bound,
                                this->range.lower_bound
                        );

                        boost::real::helper::add_boundaries(
                                this->_lhs_it_ptr->range.upper_bound,
                                this->_rhs_it_ptr->range.upper_bound,
                                this->range.upper_bound
                        );
                    } else if (this->_real_ptr->_operation == OPERATION::SUBTRACT) {
                        boost::real::helper::subtract_boundaries(
                                this->_lhs_it_ptr->range.lower_bound,
                                this->_rhs_it_ptr->range.upper_bound,
                                this->range.lower_bound
                        );

                        boost::real::helper::subtract_boundaries(
                                this->_lhs_it_ptr->range.upper_bound,
                                this->_rhs_it_ptr->range.lower_bound,
                                this->range.upper_bound
                        );
                    }
                }

            public:

                // Number range boundaries
                boost::real::Range range;

                const_precision_iterator() = default;

                const_precision_iterator(const const_precision_iterator& other) = default;

                explicit const_precision_iterator(real const* ptr) : _real_ptr(ptr) {

                    switch (this->_real_ptr->_kind) {

                        case KIND::EXPLICIT:
                            this->_explicit_it = this->_real_ptr->_explicit_number.cbegin();
                            this->range = this->_explicit_it.range;
                            break;

                        case KIND::ALGORITHM:
                            this->_algorithmic_it = this->_real_ptr->_algorithmic_number.cbegin();
                            this->range = this->_explicit_it.range;
                            break;

                        case KIND::OPERATION:
                            this->_lhs_it_ptr = new const_precision_iterator(this->_real_ptr->_lhs_ptr->cbegin());
                            this->_rhs_it_ptr = new const_precision_iterator(this->_real_ptr->_rhs_ptr->cbegin());
                            this->calculate_operation_bounds();
                            break;
                    }
                }

                void operator++() {

                    switch (this->_real_ptr->_kind) {

                        case KIND::EXPLICIT:
                            ++this->_explicit_it;
                            this->range = this->_explicit_it.range;
                            break;

                        case KIND::ALGORITHM:
                            ++this->_algorithmic_it;
                            this->range = this->_algorithmic_it.range;
                            break;

                        case KIND::OPERATION:
                            // Composed number iteration
                            this->range.lower_bound.clear();
                            this->range.upper_bound.clear();

                            // Recursive iteration of the operands
                            ++(*this->_lhs_it_ptr);
                            ++(*this->_rhs_it_ptr);

                            // Final bound calculation
                            this->calculate_operation_bounds();
                            break;
                    }
                };
            };

            real() = default;

            real(const real& other)  :
                    _explicit_number(other._explicit_number),
                    _operation(other._operation) { this->copy_operands(other); };

            real(std::initializer_list<int> digits, int integer_part)
                    : _explicit_number(digits, integer_part) {};

            real(std::initializer_list<int> digits, int integer_part, bool positive)
                    : _explicit_number(digits, integer_part, positive) {};

            real(int (*get_nth_digit)(unsigned int), int integer_part)
                    : _kind(KIND::ALGORITHM), _algorithmic_number(get_nth_digit, integer_part) {}

            real(int (*get_nth_digit)(unsigned int),
                 int integer_part,
                 bool positive)
                    : _kind(KIND::ALGORITHM),
                      _algorithmic_number(get_nth_digit, integer_part, positive) {}

            real(int (*get_nth_digit)(unsigned int),
                 int integer_part,
                 bool positive,
                 int max_precision)
                    : _kind(KIND::ALGORITHM),
                      _algorithmic_number(get_nth_digit, integer_part, positive, max_precision) {}

            ~real() {
                delete this->_lhs_ptr;
                this->_lhs_ptr = nullptr;

                delete this->_rhs_ptr;
                this->_rhs_ptr = nullptr;
            }

            int max_precision() const {

                int precision;
                switch (this->_kind) {

                    case KIND::EXPLICIT:
                        precision = this->_explicit_number.max_precision();
                        break;

                    case KIND::ALGORITHM:
                        precision = this->_algorithmic_number.max_precision();
                        break;

                    case KIND::OPERATION:
                        precision = std::max(this->_lhs_ptr->max_precision(), this->_rhs_ptr->max_precision());
                        break;
                }

                return precision;
            }

            const_precision_iterator cbegin() const {
                return const_precision_iterator(this);
            }

            /************** Operators ******************/

            int operator[](unsigned int n) const {
                int result;

                switch (this->_kind) {

                    case KIND::EXPLICIT:
                        result = this->_explicit_number[n];
                        break;

                    case KIND::ALGORITHM:
                        result = this->_algorithmic_number[n];
                        break;

                    case KIND::OPERATION:
                        //TODO: implement
                        result = 0;
                        break;
                }

                return result;
            };

            real& operator+=(const real& other) {
                this->_kind = KIND::OPERATION;
                this->_lhs_ptr = new real(*this);
                this->_rhs_ptr = new real(other);
                this->_operation = OPERATION::ADDITION;
                return *this;
            }

            real operator+(const real& other) const {
                real result = *this;
                result += other;
                return result;
            }

            real& operator-=(const real& other) {
                this->_kind = KIND::OPERATION;
                this->_lhs_ptr = new real(*this);
                this->_rhs_ptr = new real(other);
                this->_operation = OPERATION::SUBTRACT;
                return *this;
            }

            real operator-(const real& other) const {
                real result = *this;
                result -= other;
                return result;
            }

            real& operator=(const real& other) {
                this->_kind = other._kind;
                this->_explicit_number = other._explicit_number;
                this->_operation = other._operation;
                this->copy_operands(other);
                return *this;
            }

            bool operator<(const real& other) const {
                auto this_it = this->cbegin();
                auto other_it = other.cbegin();

                int current_precision = std::max(this->max_precision(), other.max_precision());
                for (int p = 0; p < current_precision; ++p) {
                    // Get more precision
                    ++this_it;
                    ++other_it;

                    if (this_it.range < other_it.range) {
                        return true;
                    }

                    if (other_it.range < this_it.range) {
                        return false;
                    }
                }

                // If the precision is reached and the number ranges still overlap, then we cannot
                // know if they are equals or other es less than this and we throw an error.
                throw boost::real::precision_exception();
            }
        };
    }
}

std::ostream& operator<<(std::ostream& os, const boost::real::real& r) {
    auto it = r.cbegin();
    for (int i = 0; i <= r.max_precision(); i++) {
        ++it;
    }
    os << it.range;
    return os;
}

#endif //BOOST_REAL_REAL_HPP

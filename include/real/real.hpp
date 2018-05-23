#ifndef BOOST_REAL_REAL_HPP
#define BOOST_REAL_REAL_HPP

#include <iostream>
#include <list>
#include <algorithm>
#include <initializer_list>
#include <utility>

#include <real/number.hpp>

namespace boost {
    namespace real {
        class real {

            enum OP {ADD, SUB, MUL, DIV, NONE};

            std::list<short> _digits;
            number* _number = NULL;
            real* _lhs = NULL;
            real* _rhs = NULL;
            OP _operation = OP::NONE;
            int _add_operands = 1;

            real(OP operation, const real& lhs, const real& rhs) {
                this->_lhs = new real(lhs);
                this->_rhs = new real(rhs);
                this->_precision = std::max(lhs._precision, rhs._precision);
                this->_operation = operation;

                if (operation == OP::ADD) {
                    this->_add_operands = this->_lhs->_add_operands + this->_rhs->_add_operands;
                }
            };

        public:

            class iterator {
            private:
                std::list<short> lower_bound = {};
                std::list<short> upper_bound = {};
                unsigned int n = 0;

                real* ptr = NULL;
                iterator* lhs_iterator = NULL;
                iterator* rhs_iterator = NULL;

                void add_bounds(const std::list<short>& lhs, const std::list<short>& rhs, std::list<short>& result) const {
                    short carry = 0;
                    short digit;

                    auto lhs_it = lhs.crbegin();
                    auto rhs_it = rhs.crbegin();

                    while(lhs_it != lhs.crend() and rhs_it != rhs.crend()) {

                        digit = carry + *lhs_it + *rhs_it;

                        if (digit > 9) {
                            carry = 1;
                            digit -= 10;
                        } else {
                            carry = 0;
                        }

                        result.push_front(digit);
                        ++lhs_it;
                        ++rhs_it;
                    }

                    if (carry == 1) {
                        result.push_front(1);
                    }
                };

            public:
                iterator() = default;

                iterator(const iterator& other)
                        : lower_bound(other.lower_bound),
                          upper_bound(other.upper_bound),
                          n(other.n),
                          ptr(other.ptr),
                          lhs_iterator(other.lhs_iterator),
                          rhs_iterator(other.rhs_iterator) {}

                iterator(real* ptr) : ptr(ptr) {
                    if (this->ptr->_operation != OP::NONE) {
                        this->lhs_iterator = new iterator(this->ptr->_lhs->begin());
                        this->rhs_iterator = new iterator(this->ptr->_rhs->begin());
                    }
                }

                std::list<short>& get_lower_bound() { return this->lower_bound; }
                std::list<short>& get_upper_bound() { return this->upper_bound; }

                void operator++() {
                    short new_digit, carry;

                    if (this->ptr->_operation == OP::NONE) {
                        if (!this->upper_bound.empty()) {
                            this->upper_bound.pop_back();
                            this->upper_bound.push_back(this->lower_bound.back());
                        }

                        this->n++;
                        new_digit = this->ptr->get_nth_digit(this->n);
                        this->lower_bound.push_back(new_digit);

                        carry = 1;
                        this->upper_bound.clear();
                        for (auto it = this->lower_bound.rbegin(); it != lower_bound.rend(); ++it) {
                            if (*it + carry == 10) {
                                this->upper_bound.push_front(0);
                            } else {
                                this->upper_bound.push_front(*it + carry);
                                carry = 0;
                            }
                        }

                        if (carry > 0) {
                            this->upper_bound.push_front(carry);
                        }

                        return;
                    }

                    this->lower_bound.clear();
                    this->upper_bound.clear();

                    if (this->ptr->_operation == OP::ADD) {
                        ++(*this->lhs_iterator);
                        ++(*this->rhs_iterator);
                        this->add_bounds((*this->lhs_iterator).get_lower_bound(), (*this->rhs_iterator).get_lower_bound(), this->lower_bound);
                        this->add_bounds((*this->lhs_iterator).get_upper_bound(), (*this->rhs_iterator).get_upper_bound(), this->upper_bound);
                    }
                }
            };

            unsigned int _precision;

            real(const real& other) {
                this->_digits = other._digits;
                this->_precision = other._precision;
                this->_number = other._number;
                this->_lhs = other._lhs;
                this->_rhs = other._rhs;
                this->_operation = other._operation;
            };

            real(unsigned int precision) {
                this->_precision = precision;
            };

            real(unsigned int precision, std::initializer_list<short> l) {
                this->_precision = precision;
                this->_digits = l;
            };

            ~real() {
                delete this->_number;
                this->_number = NULL;

                delete this->_lhs;
                this->_lhs = NULL;

                delete this->_rhs;
                this->_rhs = NULL;
            }

            /*
             * Returns the nth digit of a base case number (i.e. a number that is not a composition of
             * multiple numbers operations)
             *
             * Requires: this->_operation == OP::NONE
             */
            int get_nth_digit(unsigned int n) const {

                if (this->_number != NULL) {
                    return this->_number->get_nth_digit(n);
                }

                if (n > this->_digits.size()) {
                    return 0;
                }

                std::list<short>::const_iterator it = this->_digits.cbegin();
                for (unsigned int i = 1; i < n; i++) { it++; }

                return *it;
            };

            template <typename NUMBER, typename... Args>
            void add_number(Args&&... args) {
                this->_number = new NUMBER(std::forward<Args>(args)...);
            }

            // TODO: modify to use the iterator and print the number as the range [lower, upper] bounds
            void print() const {
                std::cout << "0.";
                for (unsigned int i = 1; i <= this->_precision; i++) {
                    std::cout << this->get_nth_digit(i);
                }
                std::cout << std::endl;
            }

            iterator begin() { return iterator(this); }

            // friend operators are needed to access the private enum OP
            friend real operator+(const real& lhs, const real& rhs);
        };

        inline real operator+(const real& lhs, const real& rhs){
            return real(real::OP::ADD, lhs, rhs);
        }
    }
}

#endif //BOOST_REAL_REAL_HPP

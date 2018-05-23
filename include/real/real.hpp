#ifndef BOOST_REAL_REAL_HPP
#define BOOST_REAL_REAL_HPP

#include <iostream>
#include <list>
#include <algorithm>
#include <initializer_list>

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

            // It assumes n < this->_precision
            int add_get_nth_digit(unsigned int n) const {
                short carry = 0;
                int digit;
                for(int i = this->_precision; i > 0; i--) {
                    digit = carry + this->_lhs->get_nth_digit(i) + this->_rhs->get_nth_digit(i);
                    if (digit > 9) {
                        carry = 1;
                        digit -= 10;
                    } else {
                        carry = 0;
                    }
                    if (i == n) {
                        return digit;
                    }
                }
            };

        public:

            class iterator {
            private:
                std::list<short> lower_bound = { 0 };
                std::list<short> upper_bound = { 0 };
                int n = 1;

                real* ptr;
                iterator* lhs_iterator;
                iterator* rhs_iterator;

            public:
                iterator() = default;

                iterator(const iterator& other)
                        : lower_bound(other.lower_bound),
                          upper_bound(other.upper_bound),
                          ptr(other.ptr),
                          n(other.n),
                          lhs_iterator(other.lhs_iterator),
                          rhs_iterator(other.rhs_iterator) {}

                // TODO: add the lhs and rhs iterators
                iterator(real* ptr)
                        : ptr(ptr) {;
                }

                iterator operator++() {

                    //TODO: fix this intializator, does not work because the *this does not return an iterator
                    iterator i(*this);

                    if (this->ptr->_operation == OP::NONE) {
                        this->lower_bound.push_back(this->ptr->get_nth_digit(this->n));
                        this->upper_bound.push_back(this->ptr->get_nth_digit(this->n));
                        this->n++;
                        return i;
                    }

                    // TODO: Make the algorthm margin both iterators.

                    return i;
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

            real& operator+=(const real& rhs) {};
            real& operator-=(const real& rhs) {};
            real& operator*=(const real& rhs) {};
            real& operator/=(const real& rhs) {};

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
                for (int i = 1; i < n; i++) { it++; }

                return *it;
            };

            template <typename NUMBER, typename... Args>
            void add_number(Args&&... args) {
                this->_number = new NUMBER(std::forward<Args>(args)...);
            };

            // TODO: modify to use the iterator and print the number as the range [lower, upper] bounds
            void print() const {
                std::cout << "0.";
                for (int i = 1; i <= this->_precision; i++) {
                    std::cout << this->get_nth_digit(i);
                }
                std::cout << std::endl;
            };

            iterator begin() { return iterator(*this); }

            // friend operators are needed to access the private enum OP
            friend real operator+(const real& lhs, const real& rhs);
        };

        inline real operator+(const real& lhs, const real& rhs){
            return real(real::OP::ADD, lhs, rhs);
        }
    }
}

#endif //BOOST_REAL_REAL_HPP

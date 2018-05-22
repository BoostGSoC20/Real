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
                std::list<short> m;
                real* ptr;

            public:
                iterator() = default;
                iterator(const iterator& other) : m(other.m) {}
                iterator(real* ptr) : ptr(ptr) {}
                std::list<short>& operator*() { return this->m; }
                iterator operator++() {
                    int n = this->m.size() + 1;
                    this->ptr->_digits.size();
                    this->m.push_back(this->ptr->get_nth_digit(n));


                    return *this; // WARNING: This is returning the updated iterator;
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

            int get_nth_digit(unsigned int n) const {

                if (n > this->_precision) {
                    return 0;
                }

                if (this->_number != NULL) {
                    return this->_number->get_nth_digit(n);
                }

                switch (this->_operation) {
                    case OP::ADD:
                        // check that this->_lhs != NULL and this->_rhs != NULL
                        return this->add_get_nth_digit(n);
                }

                if (n > this->_digits.size()) {
                    return 0;
                }

                std::list<short>::const_iterator it = this->_digits.cbegin();
                for (int i = 1; i < n; i++) {
                    it++;
                }

                return *it;
            };

            template <typename NUMBER, typename... Args>
            void add_number(Args&&... args) {
                this->_number = new NUMBER(std::forward<Args>(args)...);
            };

            void print() const {
                std::cout << "0.";
                for (int i = 1; i <= this->_precision; i++) {
                    std::cout << this->get_nth_digit(i);
                }
                std::cout << std::endl;
            };

            // friend operators are needed to access the private enum OP
            friend real operator+(const real& lhs, const real& rhs);
        };

        inline real operator+(const real& lhs, const real& rhs){
            return real(real::OP::ADD, lhs, rhs);
        }
    }
}

#endif //BOOST_REAL_REAL_HPP

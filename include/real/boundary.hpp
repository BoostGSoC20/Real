#ifndef BOOST_REAL_BOUNDARY_HPP
#define BOOST_REAL_BOUNDARY_HPP

#include <vector>
#include <real/boundary_helper.hpp>

namespace boost {
    namespace real {

        /**
         * @author Laouen Mayal Louan Belloli
         *
         * @brief Explicitly represents a number as a vector of digits with a sign and an exponent
         */
        struct boundary {
            std::vector<int> digits = {};
            int exponent = 0;
            bool positive = true;

            /**
             * @brief *default constructor*: It construct a representation of the number zero.
             */
            boundary() = default;

            /**
             * @brief *Copy constructor:* It construct a new boost::real::boundary that is a copy of the
             * other boost::real::boundary.
             *
             * @param other - The boost::real::boundary to copy.
             */
            boundary(const boundary &other) = default;

            /**
             * @brief Default asignment operator.
             *
             * @param other - The boost::real::boundary to copy.
             */
            boundary &operator=(const boundary& other) = default;

            /**
             * @brief *Lower comparator operator:* It compares the *this boost::real::boundary with the other
             * boost::real::boundary to determine if *this is lower than other.
             *
             * @param other - The right side operand boost::real::boundary to compare with *this.
             * @return a bool that is true if and only if *this is lower than other.
             */
            bool operator<(const boundary& other) const {

                if (this->positive != other.positive) {
                    return !this->positive;
                }

                if (this->positive) {
                    if (this->exponent == other.exponent) {
                        return boost::real::helper::aligned_vectors_is_lower(this->digits,
                                                                             other.digits);
                    }

                    return this->exponent < other.exponent;
                }

                if (this->exponent == other.exponent) {
                    return boost::real::helper::aligned_vectors_is_lower(other.digits,
                                                                         this->digits);
                }

                return other.exponent < this->exponent;
            }

            /**
             * @brief *Greater comparator operator:* It compares the *this boost::real::boundary with the other
             * boost::real::boundary to determine if *this is greater than other.
             *
             * @param other - The right side operand boost::real::boundary to compare with *this.
             * @return a bool that is true if and only if *this is greater than other.
             */
            bool operator>(const boundary& other) const {

                if (this->positive != other.positive) {
                    return this->positive;
                }

                if (this->positive) {
                    if (this->exponent == other.exponent) {
                        return boost::real::helper::aligned_vectors_is_lower(other.digits, this->digits);
                    }

                    return this->exponent > other.exponent;
                }

                if (this->exponent == other.exponent) {
                    return boost::real::helper::aligned_vectors_is_lower(this->digits, other.digits);
                }

                return other.exponent > this->exponent;
            }

            /**
             * @brief *Equality comparator operator:* It compares the *this boost::real::boundary with the other
             * boost::real::boundary to determine if *this and other are equals or not.
             *
             * @param other - The right side operand boost::real::boundary to compare with *this.
             * @return a bool that is true if and only if *this is equal to other.
             */
            bool operator==(const boundary& other) const {
                return !(*this < other || other < *this);
            }

            /**
             * @brief Generates a string representation of the boost::real::boundary.
             *
             * @return a string that represent the state of the boost::real::boundary
             */
            std::basic_string<char> as_string() const {
                std::basic_string<char> result = "";

                if (!this->positive) {
                    result = "-";
                }

                // If the number is to large, scientific notation is used to print it.
                if ((this->exponent < -10) || (this->exponent > (int)this->digits.size() + 10)) {
                    result += "0.";

                    for (const auto& d: this->digits) {
                        result += std::to_string(d);
                    }

                    result += "e" + std::to_string(this->exponent);
                    return result;
                }

                if (this->exponent <= 0) {
                    result += "0.";

                    for (int i = this->exponent; i < (int) this->digits.size(); ++i) {
                        if (i < 0) {
                            result += "0";
                        } else {
                            result += std::to_string(this->digits[i]);
                        }
                    }
                } else {

                    int digit_amount = std::max(this->exponent, (int) this->digits.size());
                    for (int i = 0; i < digit_amount; ++i) {

                        if (i == this->exponent) {
                            result += ".";
                        }

                        if (i < (int) this->digits.size()) {
                            result += std::to_string(this->digits[i]);
                        } else {
                            result += "0";
                        }
                    }

                    if (result.back() == '.') {
                        result.pop_back();
                    }
                }


                return result;
            }

            /**
             * @brief Swaps the boost::real::boundary value with the value of the other boost::real::boundary.
             * This operation is a more preformant form of swapping to boost::real::boundaries.
             *
             * @param other - The boost::real::boundary to swap with *this.
             */
            void swap(boundary &other) {
                this->digits.swap(other.digits);
                std::swap(this->exponent, other.exponent);
                std::swap(this->positive, other.positive);
            }

            /**
             * @brief add the digit parameter as a new digit of the boost::real::boundary. The digit
             * is added in the right side of the number.
             *
             * @param digit - The new digit to add.
             */
            void push_back(int digit) {
                this->digits.push_back(digit);
            }

            /**
             * @brief add the digit parameter as a new digit of the boost::real::boundary. The digit
             * is added in the left side of the number.
             *
             * @param digit - The new digit to add.
             */
            void push_front(int digit) {
                this->digits.insert(this->digits.begin(), digit);
            }

            /**
             * @brief Removes extra zeros at the sides to convert the number representation into a
             * normalized representation.
             */
            void normalize() {
                while (this->digits.size() > 1 && this->digits.front() == 0) {
                    this->digits.erase(this->digits.begin());
                    this->exponent--;
                }

                while (this->digits.size() > 1 && this->digits.back() == 0) {
                    this->digits.pop_back();
                }

                // Zero could have many representation, and the normalized is the next one.
                if (this->digits.size() == 1 && this->digits.front() == 0) {
                    this->exponent = 0;
                    this->positive = true;
                }
            }

            /**
             * @brief Removes extra zeros at the left side to convert the number representation
             * into a semi normalized representation.
             */
            void normalize_left() {
                while (this->digits.size() > 1 && this->digits.front() == 0) {
                    this->digits.erase(this->digits.begin());
                    this->exponent--;
                }
            }

            /**
             * @brief ir clears the number digits.
             */
            void clear() {
                this->digits.clear();
            }

            /**
             * @brief Returns the n-th digit of the boost::real::boundary.
             *
             * @param n - an int number indicating the index of the requested digit.
             * @return an integer with the value of the number n-th digit.
             */
            int &operator[](int n) {
                return this->digits[n];
            }

            /**
             * @brief It return the amount of digit of the boost::real::boundary
             *
             * @return an unsigne long representing the number of digits of the boost::real::boundary
             */
            unsigned long size() {
                return this->digits.size();
            }
        };
    }
}

#endif //BOOST_REAL_BOUNDARY_HPP

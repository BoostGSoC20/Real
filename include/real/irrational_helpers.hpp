#ifndef BOOST_REAL_IRRATIONAL_HELPERS_HPP
#define BOOST_REAL_IRRATIONAL_HELPERS_HPP

#include <vector>
#include <real/real.hpp>
#include <math.h>
#include <limits>

namespace boost {
    namespace real {
        namespace irrational {
            // used for extra precision. should be replaced with something more definitive in the future.
            inline const int PLACEHOLDER = 10; 

            /**
             * @brief The function returns the n-th digit of the champernowne number in the
             * binary integer version.
             *
             * @param n - The number digit index.
             * @return The value of the champernowne number n-th digit (either 0 or 1)
             */
            int champernowne_binary_get_nth_digit(unsigned int n) {
                std::vector<int> binary = {1};
                unsigned int index = 0;

                while (index < n) {

                    if (std::all_of(binary.begin(), binary.end(), [](int d) -> bool { return d == 1; })) {

                        for (int i = (int)binary.size() - 1; i >= 0; i--) {
                            binary[i] = 0;
                        }
                        binary.insert(binary.begin(), 1);

                    } else {

                        for (int i = (int)binary.size() - 1; i >= 0; i--) {
                            if (binary[i] == 0) {
                                for (int j = (int)binary.size() - 1; j > i; j--) {
                                    binary[j] = 0;
                                }
                                binary[i] = 1;
                                break;
                            }
                        }
                    }

                    index += binary.size();
                }

                return binary[binary.size() - 1 - (index - n)];
            }


            /// @TODO: figure out how to avoid unnecessary recalculation by saving
            // some information from the previous iteration.


            template <typename T = int>
            T pi_nth_digit(unsigned int n) {
                // Chudnovsky Algorithm
                // pi = C * ( sum_from_k=0_to_k=x (Mk * Lk / Xk) )^(-1) 
                // increasing x you get more precise pi

                static const boost::real::real_explicit<T> real_k("6");
                static const boost::real::real_explicit<T> real_m("1");
                static const boost::real::real_explicit<T> real_l("13591409");
                static const boost::real::real_explicit<T> real_l0("545140134");
                static const boost::real::real_explicit<T> real_x("1");
                static const boost::real::real_explicit<T> real_x0("-262537412640768000");
                static const boost::real::real_explicit<T> real_s("13591409");

                // real_c is constant C in the above formula
                // its actual value is C = 426880 * sqrt(10005)
                // following approximation for C can be removed 
                // once the square root function is implemented
                static const boost::real::real<T> real_c("42698670.6663333958177128891606596082733208840025090828008380071788526051574575942163017999114556686013457371674940804113922927361812667281931368821705825634600667987664834607957359835523339854848545832762473774912507545850325782197456759912124003920153233212768354462964858373556973060121234587580491432166");

                exact_number<T> K = real_k.get_exact_number();
                exact_number<T> L = real_l.get_exact_number();
                exact_number<T> M = real_m.get_exact_number();
                exact_number<T> X = real_x.get_exact_number();
                exact_number<T> S = real_s.get_exact_number();

                static exact_number<T> L0 = real_l0.get_exact_number();
                static exact_number<T> X0 = real_x0.get_exact_number();
                static exact_number<T> _16(std::vector<T> {16}, 1, true);
                static exact_number<T> _12(std::vector<T> {12}, 1, true);
                static exact_number<T> one("1");

                static boost::real::const_precision_iterator<T> real_c_itr = real_c.get_real_itr();
                real_c_itr.set_maximum_precision(n + 1);
                const exact_number<T> C = real_c_itr.cend().get_interval().lower_bound;


                bool nth_digit_found = false;
                bool first_iteration_over = false;

                exact_number<T> iteration_number = one;
                exact_number<T> prev_pi;
                exact_number<T> pi;
                exact_number<T> error;
                const exact_number<T> max_error(std::vector<T> {1}, -(n + 1), true);

                do {  
                    exact_number<T> temp = K * K * K - _16 * K;
                    temp.divide_vector(iteration_number * iteration_number * iteration_number, n + 1, true);
                    M *= temp;
                    X *= X0;
                    L += L0;
                    K += _12;

                    temp = M * L;
                    temp.divide_vector(X, n + 1, false);
                    S += temp;

                    temp = C;
                    temp.divide_vector(S, n + 1, false);

                    pi = temp;
                    if (!first_iteration_over) {
                        prev_pi = pi;
                        first_iteration_over = true;
                        iteration_number += one;
                    } else {
                        error = pi - prev_pi;
                        error.positive = true;

                        if (error < max_error) {
                            nth_digit_found = true;
                        }
                        iteration_number += one;
                        prev_pi = pi;
                    }

                } while (!nth_digit_found);

                return pi[n];
            }
        }
    }
}

#endif //BOOST_REAL_IRRATIONAL_HELPERS_HPP
#ifndef BOOST_REAL_IRRATIONAL_HELPERS_HPP
#define BOOST_REAL_IRRATIONAL_HELPERS_HPP

#include <vector>
#include <algorithm>
#include <real/real.hpp>
#include <math.h>

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
            // some information in real_algorithm

            // e^x = sum_{k=0}^\infty x^k / k! = 1 + x + x^2/2! + x^3/3! + x^4/4!
            // calculates e^x, where x = m/l
            template<int m, int l = 1>
            int exponential_get_nth_digit(unsigned int n) {
                std::vector<int> const one {1};
                std::vector<int> const zero {0};

                exact_number one_n {one, 1};
                exact_number last_term {one, 1}; // x^k_n / k_n!
                exact_number current_value; // summation up to k_n

                exact_number k;
                exact_number k_fac;
                exact_number const mn (m);
                exact_number const ln (l);
                std::cout << mn.as_string() << ", " << ln.as_string() << '\n';
                exact_number x = mn;

                /// @TODO look into possible precision problems
                x.divide_vector(ln, n+PLACEHOLDER, DIVISION_RESULT::EXACT);

                // prepare to calculate k=2 term
                k = one_n + one_n;
                last_term = x;
                current_value = one_n + x;

                // keep getting terms from the taylor series until the terms go below our precision bound
                /// @TODO: ensure cast doesn't overflow
                while(last_term.exponent >= 1-(int)(n+PLACEHOLDER)) {
                    last_term *= x;
                    last_term.divide_vector(k, n+PLACEHOLDER, DIVISION_RESULT::EXACT);
                    current_value += last_term;

                    k = k + one_n;
                }

                return current_value.digits[n];
            }

            int pi_get_nth_digit(unsigned int n) {
                if (n > 2000)
                    throw(pi_precision_exception());
                // 2000 digits of pi
                exact_number pi("3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700660631558817488152092096282925409171536436789259036001133053054882046652138414695194151160943305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194912983367336244065664308602139494639522473719070217986094370277053921717629317675238467481846766940513200056812714526356082778577134275778960917363717872146844090122495343014654958537105079227968925892354201995611212902196086403441815981362977477130996051870721134999999837297804995105973173281609631859502445945534690830264252230825334468503526193118817101000313783875288658753320838142061717766914730359825349042875546873115956286388235378759375195778185778053217122680661300192787661119590921642019893809525720106548586327886593615338182796823030195203530185296899577362259941389124972177528347913151557485724245415069595082953311686172785588907509838175463746493931925506040092770167113900984882401285836160356370766010471018194295559619894676783744944825537977472684710404753464620804668425906949129331367702898915210475216205696602405803815019351125338243003558764024749647326391419927260426992279678235478163600934172164121992458631503028618297455570674983850549458858692699569092721079750930295532116534498720275596023648066549911988183479775356636980742654252786255181841757467289097777279380008164706001614524919217321721477235014144197356854816136115735255213347574184946843852332390739414333454776241686251898356948556209921922218427255025425688767179049460165346680498862723279178608578438382796797668145410095388378636095068006422512520511739298489608412848862694560424196528502221066118630674427862203919494504712371378696095636437191728746776465757396241389086583264599581339047802759009");
                return pi[n];
            }

            // e^x = sum_{k=0}^\inf = x^0/0! + x^1/1! + x^2/2! + x^3/3! + x^3/6! + ...

            class exponential {
                private:
                // would be nice to interoperate between long, int, and boost::real::real,
                // and have ctors from the integral types
                boost::real::real k_prev = boost::real::real_explicit("0");
                boost::real::real const * const x_ptr;
                boost::real::real last_term; // x^kn / kn!
                boost::real::real current_value; // summation from k0 to k_n, with precision digits

                public:
                exponential(boost::real::real &x) : x_ptr(&x) {
                    last_term = boost::real::real ("1");
                    current_value = boost::real::real ("1");
                };

                int get_nth_digit(unsigned int n) {
                    boost::real::real one = boost::real::real_explicit("1");
                    // if n < k_prev, reset

                    boost::real::real min_bound;
                    std::get<boost::real::real_explicit>(min_bound.get_real_number()).digits = {1};
                    std::get<boost::real::real_explicit>(min_bound.get_real_number()).exponent = 1-n;

                    // keep getting terms from the taylor series until the terms go below our precision bound
                    while((last_term > min_bound) || (last_term == min_bound)) {
                        last_term = last_term * (*x_ptr) / (k_prev + one);
                        current_value = current_value + last_term;
                    }

                    return 0;
                }

            };
        }
    }
}

#endif //BOOST_REAL_IRRATIONAL_HELPERS_HPP

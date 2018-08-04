#ifndef BOOST_REAL_IRRATIONALS_HPP
#define BOOST_REAL_IRRATIONALS_HPP

#include <vector>
#include <algorithm>

namespace boost {
    namespace real {
        namespace irrational {

            /**
             * @brief The Champernowne is a transcendental real constant whose digits are formed by
             * consecutively concatenate representations of sucessive integets in a determined base.
             * In this function, a binary base is used.
             *
             * @param n - The number digit index.
             * @return The value if the champernowne number n-th digit
             */
            int champernowne_binary(unsigned int n) {
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
        }
    }
}

#endif //BOOST_REAL_IRRATIONALS_HPP

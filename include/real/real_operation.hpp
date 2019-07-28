#ifndef BOOST_REAL_REAL_OPERATION
#define BOOST_REAL_REAL_OPERATION

#include <memory> // shared_ptr

#include <real/real_algorithm.hpp>
#include <real/real_explicit.hpp>

namespace boost{
    namespace real{

        // fwd decl needed
        template <typename T>
        class real_data;
        template <typename T>
        class const_precision_iterator;

        /*
        * @brief real_operation is a (very unbalanced) binary tree representation of operations, where
        * the leaves are the operands and the nodes store the type of operation
        * 
        * @warning due to the recursive nature of real_operation, destruction may cause stack overflow
        */
        enum class OPERATION{ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION}; 

        template <typename T = int>
        class real_operation{
        private:
            std::shared_ptr<real_data<T>> _lhs;
            std::shared_ptr<real_data<T>> _rhs;
            OPERATION _operation;

        public:

            /*
             * @brief Constructor from two operands and an operation
             * @param lhs - left operand
             * @param rhs - right operand
             * @param op  - operation between the operands
             */
            real_operation(std::shared_ptr<real_data<T>> &lhs, std::shared_ptr<real_data<T>> &rhs, OPERATION op) : _lhs(lhs), _rhs(rhs), _operation(op) {};

            OPERATION get_operation() const {
                return _operation;
            }

            /// fwd decl'd, defined in real_data
            const_precision_iterator<T>& get_lhs_itr();
            
            /// fwd decl'd, defined in real_data
            const_precision_iterator<T>& get_rhs_itr();

            std::shared_ptr<real_data<T>> rhs() const {
                return _rhs;
            }

            std::shared_ptr<real_data<T>> lhs() const {
                return _lhs;
            }
        };
    }
}

#endif // BOOST_REAL_REAL_OPERATION

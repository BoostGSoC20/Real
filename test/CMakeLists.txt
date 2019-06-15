# FILE(GLOB TestSources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *_test.cpp)
set(TestSources
    real_algorithm_iterator_unit_test.cpp 
    real_eq_operator_test.cpp 
    real_greater_than_operator_test.cpp
    real_lower_than_operator_test.cpp
    real_explicit_constructors_unit_test.cpp 
    real_explicit_iterator_unit_test.cpp 
    real_iterator_addition_addition_test.cpp 
    real_iterator_addition_multiplication_test.cpp 
    real_iterator_addition_subtraction_test.cpp 
    real_iterator_addition_test.cpp
    real_iterator_multiplication_addition_test.cpp
    real_iterator_multiplication_multiplication_test.cpp
    real_iterator_multiplication_subtraction_test.cpp
    real_iterator_multiplication_test.cpp
    real_iterator_subtraction_addition_test.cpp
    real_iterator_subtraction_multiplication_test.cpp
    real_iterator_subtraction_subtraction_test.cpp
    real_iterator_subtraction_test.cpp
    vector_helpers_test.cpp
    )

foreach(testSrc ${TestSources})
    get_filename_component(testName ${testSrc} NAME_WE)
    add_executable(${testName} main-test.cpp ${testSrc})
    add_test(${testName} ${testName})
    target_include_directories(${testName}
        PRIVATE ./include
        PUBLIC ${CMAKE_SOURCE_DIR}/external/include/catch2
        # add other dependencies here, when needed for testing
        )
     target_link_libraries(${testName}
         PUBLIC Boost.Real
         )
endforeach(testSrc)

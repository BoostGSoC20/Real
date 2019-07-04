FILE(GLOB TestSources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *_test.cpp)

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

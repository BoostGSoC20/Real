cmake_minimum_required(VERSION 3.8)
project(Boost.Real)
set (Boost.Real 1)
set (Boost.Real 0)

add_library(Boost.Real INTERFACE)

# Check for standard to use
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
if(HAVE_FLAG_STD_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic --std=c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic --std=c++1z")
endif()

#Detect Boost.Test framework
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(include ${Boost_INCLUDE_DIRS})

# Unit tests
enable_testing()
FILE(GLOB TestSources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*_test.cpp)
foreach(testSrc ${TestSources})
    get_filename_component(testName ${testSrc} NAME_WE)
    add_executable(${testName} ${testSrc})
    add_test(${testName} ${testName})
endforeach(testSrc)

#Library Headers
add_executable(Boost.Real_headers include)
set_target_properties(Boost.Real_headers PROPERTIES
                                                 EXCLUDE_FROM_ALL TRUE
                                                 EXCLUDE_FROM_DEFAULT_BUILD TRUE
                                                 LINKER_LANGUAGE CXX)

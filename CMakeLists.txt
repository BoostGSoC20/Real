cmake_minimum_required(VERSION 3.8)
project(Boost.Real)
set (Boost.Real_VERSION_MAJOR 1)
set (Boost.Real_VERSION_MINOR 0)

#Add coverage support to CMAKE in debug mode
IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message("debug mode adding coverage report tools and flags")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")
    include(CodeCoverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -O0 -fsanitize=address -fno-omit-frame-pointer -fprofile-arcs -ftest-coverage")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

# Check for standard to use
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
if(HAVE_FLAG_STD_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic --std=c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic --std=c++1z")
endif()

include_directories(include external/include ${Boost_INCLUDE_DIRS})

# add Boost.Real as a 'linkable' target
add_library(Boost.Real INTERFACE)

#Library Headers
add_executable(Boost.Real_headers include)
set_target_properties(Boost.Real_headers PROPERTIES
                                                 EXCLUDE_FROM_ALL TRUE
                                                 EXCLUDE_FROM_DEFAULT_BUILD TRUE
                                                 LINKER_LANGUAGE CXX 
                                                 )
# Unit tests
option(REAL_TEST "Build tests" ON)
if(REAL_TEST)
    enable_testing()
    #Detect Boost.Test framework
    set(Boost_USE_MULTITHREADED OFF)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_subdirectory(test)
endif()

#Google Benchmark, turn on/off with -DREAL_BENCH=ON or OFF
option(REAL_BENCH "Build benchmarks" OFF)
if(REAL_BENCH)
    add_subdirectory(bench)
endif()

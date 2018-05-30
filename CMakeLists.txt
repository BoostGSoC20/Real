cmake_minimum_required(VERSION 3.8)
project(Boost.Real)
set (Boost.Real 1)
set (Boost.Real 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")

include_directories(include)

# Unit tests
enable_testing()
FILE(GLOB TestSources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*_test.cpp)
foreach(testSrc ${TestSources})
    get_filename_component(testName ${testSrc} NAME_WE)
    add_executable(${testName} ${testSrc})
    add_test(${testName} ${testName})
endforeach(testSrc)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)

add_subdirectory(benchmark)

# remember to add src's here
set(benchSrcs
    operation_tree_bench.cpp
    main_bench.cpp
    )
# to run a subset of benchmarks, use:
# ./main_bench --benchmark_filter=<regex>  
add_executable(main_bench ${benchSrcs})
target_include_directories(main_bench 
    PRIVATE ./include
    )
target_link_libraries(main_bench 
    PUBLIC Boost.Real
    PUBLIC benchmark
    )

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)

add_subdirectory(benchmark)

FILE(GLOB BenchSources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *_bench.cpp)

# NOTE: main-bench (to run all benchmarks) 
# to run a subset of benchmarks, use:
# ./main_bench --benchmark_filter=<regex>

foreach(benchSrc ${BenchSources})
    get_filename_component(benchName ${benchSrc} NAME_WE)
    add_executable(${benchName} main-bench.cpp ${benchSrc})
    target_include_directories(${benchName}
        PRIVATE ./include
        PUBLIC ./benchmark/include
        )
    target_link_libraries(${benchName}
        PUBLIC Boost.Real
        PUBLIC benchmark
        )
endforeach(benchSrc)

add_executable(main-bench main-bench.cpp ${BenchSources})
target_include_directories(main-bench
    PRIVATE ./include
    PUBLIC ./benchmark/include
    )
target_link_libraries(main-bench
    PUBLIC Boost.Real
    PUBLIC benchmark
    )

# TODO: add a target to run all benches and create reports

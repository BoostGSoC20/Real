set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)

add_subdirectory(benchmark)
include_directories(benchmark/include
    include)

set(bench_list
    addition_bench.cpp
    )

add_executable(main_bench ${bench_list})


target_link_libraries(main_bench
    benchmark
    Boost.Real
    ${CMAKE_THREAD_LIBS_INIT}
    )

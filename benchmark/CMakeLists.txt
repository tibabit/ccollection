
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/google-benchmark/include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/google-benchmark/lib")

macro(compile_benchmark_test name)
    add_executable(${name}_benchmark "${name}.cpp")
    target_link_libraries(${name}_benchmark ccollection benchmark pthread)
    add_test(${name}_benchmark ${name}_benchmark --benchmark_min_time=0.01)
endmacro(compile_benchmark_test)

compile_benchmark_test(vector)

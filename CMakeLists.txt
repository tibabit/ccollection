cmake_minimum_required(VERSION 2.6)
project(ccollection)

# build benchmarks
option(CCOLLECTION_ENABLE_BENCHMARK "Enable benchmarking" OFF)
#build unit test
option(CCOLLECTION_ENABLE_UNIT_TESTS "Enable unit tests" ON)
# enable ctest
set(BUILD_TESTING ON)

# needed at all places
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(src)

if (BUILD_TESTING)
    enable_testing()
endif()

if (CCOLLECTION_ENABLE_BENCHMARK)
    add_subdirectory(benchmark)
endif()

if (CCOLLECTION_ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()

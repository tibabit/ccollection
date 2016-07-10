cmake_minimum_required(VERSION 2.6)
project(ccollection)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/test/gtest/include")

link_directories("${PROJECT_SOURCE_DIR}/test/gtest/lib")

add_library(ccollection src/vector.c)

add_executable(ccollection_test test/test_main.cpp
    test/test_vector.cpp
    )

target_link_libraries(ccollection_test ccollection gtest pthread)

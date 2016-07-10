
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/gtest/include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/gtest/lib")

add_executable(ccollection_test test_main.cpp
    test_ccollection.cpp
    test_vector.cpp
)
target_link_libraries(ccollection_test ccollection gtest pthread)
add_test(ccollection_test ccollection_test)


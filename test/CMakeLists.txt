
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/gtest/include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/gtest/lib")

macro(compile_test name)
    add_executable(${name} test_main.cpp
        ${name}.cpp
        )
    target_link_libraries(${name} ccollection gtest pthread)
    add_test(${name} ${name})
endmacro()

compile_test(test_ccollection)
compile_test(test_vector)


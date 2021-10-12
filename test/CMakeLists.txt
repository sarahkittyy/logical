cmake_minimum_required(VERSION 3.18)
project(logical)

find_package(Catch2 REQUIRED)

file(GLOB sources "*.cpp")
add_executable(logical-test ${sources})
add_dependencies(logical-test logical)
target_link_libraries(logical-test logical Catch2::Catch2)
target_include_directories(logical-test PUBLIC "${CMAKE_SOURCE_DIR}/test")

include(CTest)
include(Catch)
catch_discover_tests(logical-test)

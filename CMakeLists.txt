cmake_minimum_required(VERSION 3.18)
project(logical)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTS "Build the tests." ON)

file(GLOB_RECURSE sources "src/*.cpp")

add_library(logical ${sources})

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(test/)
endif()

if(BUILD_SANDBOX)
	add_subdirectory(sandbox/)
endif()

target_compile_options(logical PUBLIC -Wall)
target_include_directories(logical PUBLIC
	"include/"
	PRIVATE
	"src/"
)
target_link_libraries(logical
	
)

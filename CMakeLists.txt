cmake_minimum_required(VERSION 2.8)

PROJECT(mobilehealthcare)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
file(
	GLOB_RECURSE
	source_files
	src/*
)
set(CMAKE_CXX_FLAGS -DDEBUG)
set(CMAKE_CXX_FLAGS "-g -Wall -pedantic")
add_definitions(-DDEBUG=1)
add_executable(
	mobilehealthcare
	${source_files}
)

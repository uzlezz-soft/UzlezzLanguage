cmake_minimum_required(VERSION 3.10)

project(UzlezzLanguage VERSION 0.1)
add_subdirectory(code)

option(BUILD_TESTS "Build tests for UzlezzLanguage" ON)
if (BUILD_TESTS)
	message(STATUS "Building with Tests")
	set(BUILD_SHARED_LIBS ON)
	enable_testing()
	add_subdirectory(test)
endif(BUILD_TESTS)
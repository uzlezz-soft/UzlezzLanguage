
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(UzlezzLanguage STATIC "clang-format.txt" "source/lexer.cpp" "source/token.cpp" "include/uzl/lexer.h" "include/uzl/common.h" "include/uzl/token.h" "source/log.h" "source/log.cpp")

target_include_directories(UzlezzLanguage PUBLIC include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../third-party/fmt ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/fmt/out)
message(STATUS "Using fmtlib via add_subdirectory")

target_link_libraries(UzlezzLanguage PRIVATE fmt::fmt)

install(TARGETS UzlezzLanguage
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
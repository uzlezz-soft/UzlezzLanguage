
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(UzlezzLanguage STATIC "Source/Lexer.cpp" "Include/UzL/Lexer.h")

target_include_directories(UzlezzLanguage PUBLIC Include)

install(TARGETS UzlezzLanguage
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
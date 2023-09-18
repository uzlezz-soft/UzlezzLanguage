
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Tests "source/entry_point.cpp")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../third-party/gtest ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/gtest/out)
message(STATUS "Using GoogleTest with add_subdirectory")

target_include_directories(Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../code/include)
target_include_directories(Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/gtest/googletest/include)
target_include_directories(Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/gtest/googlemock/include)

target_link_libraries(Tests PRIVATE UzlezzLanguage)
target_link_libraries(Tests PRIVATE gtest)
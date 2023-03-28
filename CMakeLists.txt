cmake_minimum_required(VERSION 3.22)
project(cpp_driver)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall --pedantic -g")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-packages" ${CMAKE_MODULE_PATH})

find_package(FUSE REQUIRED)
include_directories(${FUSE_INCLUDE_DIR})

include_directories("src")
add_library(cpp_driver_lib  src/model/Unit.cpp src/model/Unit.h src/model/MyCPU.cpp src/model/MyCPU.h src/model/ram/Ram.cpp src/model/ram/Ram.h src/model/ram/LRam.cpp src/model/ram/LRam.h src/model/ram/PRam.cpp src/model/ram/PRam.h)

add_executable(cpp_driver src/main.cpp)
target_link_libraries(cpp_driver cpp_driver_lib ${FUSE_LIBRARIES})

# Tests
project(cmake_tests)

file(GLOB_RECURSE test_SOURCES "test/*.cpp")

find_package(Catch2 REQUIRED)

add_executable(cmake_tests test/catch_amalgamated.cpp test/catch_amalgamated.hpp ${test_SOURCES})
target_link_libraries(cmake_tests cpp_driver_lib Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(cmake_tests)

cmake_minimum_required(VERSION 3.22)
project(cpp_driver)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall --pedantic -g")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-packages" ${CMAKE_MODULE_PATH})

find_package(FUSE REQUIRED)
include_directories(${FUSE_INCLUDE_DIR})

add_executable(cpp_driver src/helloFS.cpp src/helloFS.h src/hello.cpp)
target_link_libraries(cpp_driver ${FUSE_LIBRARIES})

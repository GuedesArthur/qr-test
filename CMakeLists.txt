cmake_minimum_required(VERSION 3.12)

project(qr-test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
string(TIMESTAMP BUILDDATE "%Y-%m-%d %H:%M")
set(BUILD_DATE ${BUILDDATE})
configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/version.h @ONLY) 

file(GLOB CPP_SOURCES "./src/*")

include_directories(include)
add_executable(qr-test ${CPP_SOURCES})

target_link_libraries(qr-test PRIVATE raylib)
target_include_directories(qr-test PUBLIC "${PROJECT_BINARY_DIR}/include")
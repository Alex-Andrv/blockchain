cmake_minimum_required(VERSION 3.23)
project(lab_7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "-lc++abi")
set(CMAKE_CXX_COMPILER "clang++")

#add_executable(lab_7 test/test_aes128.cpp)

add_executable(lab_7 src/main.cpp src/Random.h src/AES128.h)


cmake_minimum_required(VERSION 3.10)
project(SharedMemoryExample)

set(CMAKE_CXX_STANDARD 17)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/shm_key "")

add_executable(program_1 src/program_1.cpp)
add_executable(program_2 src/program_2.cpp)
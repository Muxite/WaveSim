cmake_minimum_required(VERSION 3.10)
project(WaveSim LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_ARCHITECTURES 89)

add_subdirectory("src/wave")

add_executable(WaveSim src/main.cpp)
target_link_libraries(WaveSim PRIVATE wave)
cmake_minimum_required(VERSION 3.10)
project(Lib-LoRa)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ECL)
add_subdirectory(src)
add_subdirectory(test)



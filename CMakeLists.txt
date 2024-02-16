cmake_minimum_required(VERSION 3.10)
project(Lib-LoRa)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(LoRaLibrary INTERFACE)
target_include_directories(LoRaLibrary INTERFACE .)
target_include_directories(LoRaLibrary INTERFACE src)
target_include_directories(LoRaLibrary INTERFACE include)

add_subdirectory(ECL)


target_link_libraries(LoRaLibrary INTERFACE EmbeddedCoreLibrary)

add_executable(
    TestExecutable
    test/test_main.cpp
)

target_link_libraries(
  TestExecutable 
  LoRaLibrary
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(TestExecutable)
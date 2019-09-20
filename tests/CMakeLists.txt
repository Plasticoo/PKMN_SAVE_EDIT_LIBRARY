cmake_minimum_required(VERSION 3.13)

project(PKMN_SAVE_EDIT_TESTS_LIBRARY)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)

include_directories(../include)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  set(CMAKE_CXX_FLAGS "-ggdb3 -O0 -std=c++17 -pedantic -m64 -march=native -mmacosx-version-min=10.15 -L/usr/local/Cellar/llvm/8.0.1/lib -lc++fs")
else()
  set(CMAKE_CXX_FLAGS "-ggdb3 -O0 -std=c++17 -pedantic -m64 -march=native")
endif()

include_directories(../include ../include/Gen ../include/Rom ../lib)

file(GLOB sources "../src/*.cpp")
file(GLOB gen1_sources "../src/Gen/Gen1/*.cpp")
file(GLOB rom_sources "../src/Rom/*.cpp")
file(GLOB test_sources "src/*.cpp")

add_executable(pkmnsav_tests ${gen1_sources} ${rom_sources} ${sources} ${test_sources})

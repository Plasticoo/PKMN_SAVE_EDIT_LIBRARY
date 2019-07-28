cmake_minimum_required(VERSION 3.13)

project(PKMN_SAVE_EDIT_LIBRARY)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)

include_directories(include)

set(CMAKE_CXX_FLAGS "-ggdb3 -O0 -std=c++17 -pedantic -m64 -pipe -fPIC -march=native")

file(GLOB sources "lib/*.cpp")

include_directories(include include/gen1 include/Rom)
file(GLOB gen1_sources "lib/gen1/*.cpp")
file(GLOB rom_sources "lib/Rom/*.cpp")

add_library(pkmnsav SHARED ${gen1_sources} ${rom_sources} ${sources})

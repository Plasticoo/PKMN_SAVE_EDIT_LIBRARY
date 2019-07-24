cmake_minimum_required(VERSION 3.13)

project(PKMN_SAVE_EDIT_LIBRARY)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -std=c99 -pedantic -m64 -pipe -fPIC -march=native -O0 -ggdb3 -Iinclude")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -std=c++17 -pedantic -m64 -pipe -fPIC -march=native -O2 -Iinclude")

file(GLOB sources "lib/*.cpp")

include_directories(include include/gen1)
file(GLOB gen1_sources "lib/gen1/*.cpp")

add_library(pkmnsav SHARED ${gen1_sources} ${sources})

cmake_minimum_required(VERSION 3.13)

project(PKMN_SAVE_EDIT_LIBRARY)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)

include_directories(include)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  set(CMAKE_CXX_FLAGS "-ggdb3 -O0 -std=c++17 -pedantic -m64 -pipe -fPIC -march=native -mmacosx-version-min=10.15")
else()
  set(CMAKE_CXX_FLAGS "-ggdb3 -O0 -std=c++17 -pedantic -m64 -pipe -fPIC -march=native")
endif()

file(GLOB sources "src/*.cpp")

include_directories(include include/gen1 include/Rom lib)
file(GLOB gen1_sources "src/gen1/*.cpp")
file(GLOB rom_sources "src/Rom/*.cpp")

add_library(pkmnsav SHARED ${gen1_sources} ${rom_sources} ${sources})

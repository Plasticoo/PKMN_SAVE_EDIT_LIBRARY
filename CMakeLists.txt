cmake_minimum_required(VERSION 3.13)

project(PKMN_SAVE_EDIT_LIBRARY)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=modernize-*")

include_directories(include)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  set(CMAKE_CXX_FLAGS "-ggdb3 -O0 -std=c++17 -pedantic -m64 -pipe -fPIC -march=native -mmacosx-version-min=10.15")
else()
  set(CMAKE_CXX_FLAGS "-ggdb3 -O0 -std=c++17 -pedantic -m64 -pipe -fPIC -march=native")
endif()

file(GLOB sources "src/*.cpp")

include_directories(include include/Gen/Gen1 include/Rom lib)
file(GLOB gen1_sources "src/Gen/Gen1/*.cpp")
file(GLOB rom_sources "src/Rom/*.cpp")


add_library(pkmnsav SHARED ${gen1_sources} ${rom_sources} ${sources})
target_link_libraries(pkmnsav /usr/local/Cellar/llvm/8.0.1/lib/libc++.dylib)

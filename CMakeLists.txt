cmake_minimum_required(VERSION 2.8.9)

project(PKMN_SAVE_EDIT_LIBRARY)

set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -Wall")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -march=native -O2")

include_directories(include/gen1)

file(GLOB gen1_sources "lib/gen1/*.c")

add_library(pkmn_save_edit_lib SHARED ${gen1_sources})

install(TARGETS pkmn_save_edit_lib DESTINATION /usr/lib)

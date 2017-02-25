cmake_minimum_required(VERSION 2.8.9)

project(PKMN_SAVE_EDIT_LIBRARY)

include_directories(include/gen1)

file(GLOB gen1_sources "lib/gen1/*.c")

add_library(pkmn_save_edit_lib SHARED ${gen1_sources})

install(TARGETS pkmn_save_edit_lib DESTINATION /usr/lib)

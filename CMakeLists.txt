
cmake_minimum_required(VERSION 2.8.9)
project(PKMN_SAVE_EDIT_LIBRARY)
set(CMAKE_BUILD_TYPE Release)

#Bring the headers, such as Student.h into the project
include_directories(include/gen1)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB gen1_sources "lib/gen1/*.c")

#Generate the shared library from the sources
add_library(testStudent SHARED ${gen1_sources})

install(TARGETS testStudent DESTINATION /usr/lib)

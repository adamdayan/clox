cmake_minimum_required(VERSION 3.15...4.0)

project(
  clox
  VERSION 1.0
  LANGUAGES C)
# TODO: change this later!
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(clox_lib)

add_executable(clox main.c)
target_link_libraries(clox PRIVATE clox_lib)


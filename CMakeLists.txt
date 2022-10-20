cmake_minimum_required(VERSION 3.16)

project(
  SmallVector
  VERSION 1.0
  LANGUAGES CXX
)

enable_testing()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_program( CLANG_TIDY_EXE NAMES "clang-tidy-10") 

if(NOT CLANG_TIDY_EXE) 
    message(STATUS "clang-tidy not found.") 
endif()

add_subdirectory(external)
add_subdirectory(tests)
add_subdirectory(src)

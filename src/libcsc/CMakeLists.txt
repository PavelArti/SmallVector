set(target_rgr library_vector)

add_library(${target_rgr} INTERFACE)

target_sources(
  ${target_rgr}
  INTERFACE
  libcsc/smallvector/SmallVector.hpp
)

include(CompileOptions)

target_include_directories(
  ${target_rgr}
  INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}
)
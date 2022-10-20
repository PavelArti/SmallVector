set(target_test vector_test)

add_executable(${target_test} libcsc/SmallVectorTest.cpp)

include(CompileOptions)
set_compile_options(${target_test})

target_link_libraries(
  ${target_test}
	PRIVATE
    library_vector
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${target_test})
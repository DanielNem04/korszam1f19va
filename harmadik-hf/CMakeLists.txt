cmake_minimum_required(VERSION 3.10)
project(TestMatrix)

add_executable(TestMatrix test_matrix.cpp)

set_target_properties(TestMatrix PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

target_compile_options(TestMatrix PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -pedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
)

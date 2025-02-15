add_executable(tests
  test-context.cpp
)
target_link_libraries(tests xlamb gtest gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
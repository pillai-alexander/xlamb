add_executable(tests
  test-context_entity_handling.cpp
  test-context_views.cpp
  test-context_rng.cpp
  test-context_any_map.cpp
)
target_link_libraries(tests xlamb gtest gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
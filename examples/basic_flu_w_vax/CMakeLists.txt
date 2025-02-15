cmake_minimum_required(VERSION 3.21)

add_executable(basic_flu_vax_model main.cpp)

target_link_libraries(basic_flu_vax_model PRIVATE xlamb)

set_target_properties(basic_flu_vax_model
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
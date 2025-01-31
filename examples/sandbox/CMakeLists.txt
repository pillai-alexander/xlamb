cmake_minimum_required(VERSION 3.21)

add_executable(sandbox main.cpp)

target_link_libraries(sandbox PRIVATE xlamb EnTT)

set_target_properties(sandbox
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
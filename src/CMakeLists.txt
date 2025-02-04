cmake_minimum_required(VERSION 3.21)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${xlamb_SOURCE_DIR}/include/xlamb/*.hpp")

add_library(
  xlamb
  logger.cpp
  entity.cpp
  context.cpp
  architect.cpp
  ${HEADER_LIST}
)

target_include_directories(xlamb PUBLIC ${xlamb_SOURCE_DIR}/include)

target_link_libraries(xlamb PUBLIC spdlog EnTT)

# IDEs should put the headers in a nice place
source_group(
  TREE "${xlamb_SOURCE_DIR}/include/xlamb"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
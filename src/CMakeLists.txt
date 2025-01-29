cmake_minimum_required(VERSION 3.21)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${xlamb_SOURCE_DIR}/include/xlamb/*.hpp")

add_library(
  xlamb
  log.cpp
  ${HEADER_LIST}
)

target_include_directories(xlamb PUBLIC ${xlamb_SOURCE_DIR}/include)

# IDEs should put the headers in a nice place
source_group(
  TREE "${xlamb_SOURCE_DIR}/include/xlamb"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
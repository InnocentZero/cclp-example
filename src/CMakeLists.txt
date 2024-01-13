set(TARGET ${PROJECT_NAME})
file(GLOB SRC_LIST CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.c")
add_executable(${TARGET} ${SRC_LIST})
target_link_libraries(${TARGET}
  PRIVATE cclp
)

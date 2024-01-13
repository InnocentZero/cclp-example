cmake_minimum_required(VERSION 3.27)

project(CCLP_EXAMPLE
    VERSION 1.0
    DESCRIPTION "An example config for using the library with CMake"
    LANGUAGES C
)
# CMAKE Standard
set(CMAKE_C_STANDARD 11)
# Adding global flags for debug
set(CMAKE_C_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -fsanitize=address -g")
# Adding global flags for release
set(CMAKE_C_FLAGS_RELEASE_INIT "${CMAKE_C_FLAGS} -O3 -g0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# including project headers
include_directories(include)

#including library headers
include_directories(lib/inc)

# Adding the library to be compiled as a target
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/lib/src/*.c)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/lib/inc/*.h)
add_library(cclp OBJECT ${SOURCES} ${HEADERS})

# including the project source files
add_subdirectory(src)

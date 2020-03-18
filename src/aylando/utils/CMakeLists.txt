project(aylando-utils)

set(UTILS_PATH "${CMAKE_SOURCE_DIR}/include/aylando/utils")

add_library(aylando-utils STATIC
    Array2d.cpp "${UTILS_PATH}/Array2d.h"
)
target_include_directories(aylando-utils PRIVATE "${UTILS_PATH}")

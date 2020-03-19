cmake_minimum_required(VERSION 3.16.0)
project(base VERSION 0.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY, "${CMAKE_BINARY_DIR}/bin")

find_package(Git QUIET)
set(CAN_GIT ${GIT_FOUND} AND EXISTS "${PROJECT_SOURCE_DIR}/.git" CACHE STRING "Does git exist and are we in a git repo?")

# sfml
set(BUILD_SHARED_LIBS OFF) # use static linking
add_subdirectory("submodules/sfml")

# FastNoise
add_subdirectory("submodules/fastnoise")

# # imgui-sfml
set(IMGUI_DIR "${PROJECT_SOURCE_DIR}/submodules/imgui")
set(SFML_DIR "${SFML_BINARY_DIR}")
add_subdirectory("submodules/imgui-sfml-sacxy")

# source libraries
add_subdirectory("src")

# testing
include(CTest)
if(BUILD_TESTING)
    # doctest
    add_subdirectory("submodules/doctest")
    add_subdirectory("tests")
endif()

# main executable
add_subdirectory("app")

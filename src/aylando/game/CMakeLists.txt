project(aylando-game)

set(GAME_PATH "${CMAKE_SOURCE_DIR}/include/aylando/game")

add_library(aylando-game STATIC
    World.cpp "${GAME_PATH}/World.h"
)
target_include_directories(aylando-game PRIVATE "${GAME_PATH}")
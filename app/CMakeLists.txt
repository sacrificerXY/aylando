project(app)

add_executable(app main.cpp)
target_link_libraries(app aylando-game ImGui-SFML-SacXY)
target_include_directories(app PUBLIC "${CMAKE_SOURCE_DIR}/include")

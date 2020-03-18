project(sample-test)

add_executable(sample-test test-main.cpp)
target_link_libraries(sample-test aylando-utils doctest)
target_include_directories(sample-test PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_test(SampleTest sample-test)

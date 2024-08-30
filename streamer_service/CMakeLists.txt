cmake_minimum_required(VERSION 3.10)

project(StreamerService)

find_package(OpenCV REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(StreamerService src/main.cpp)

target_link_libraries(StreamerService ${OpenCV_LIBS} ${SDL2_LIBRARIES})

install(TARGETS StreamerService DESTINATION bin)

cmake_minimum_required(VERSION 3.10)

project(TrackerService)

find_package(OpenCV REQUIRED)

add_executable(TrackerService src/main.cpp)

target_link_libraries(TrackerService ${OpenCV_LIBS})

install(TARGETS TrackerService DESTINATION bin)

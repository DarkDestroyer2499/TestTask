cmake_minimum_required(VERSION 3.10)

project(CameraService)

find_package(OpenCV REQUIRED)

add_executable(CameraService src/main.cpp)

target_link_libraries(CameraService ${OpenCV_LIBS})

install(TARGETS CameraService DESTINATION bin)

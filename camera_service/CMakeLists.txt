cmake_minimum_required(VERSION 3.10)

project(CameraService)

find_package(OpenCV REQUIRED)

# Add spdlog library
find_package(spdlog REQUIRED)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(CameraService src/main.cpp src/CameraService.cpp)

target_link_libraries(CameraService ${OpenCV_LIBS} spdlog::spdlog)

install(TARGETS CameraService DESTINATION bin)

cmake_minimum_required(VERSION 3.10)

project(KeyboardInputService)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find ZeroMQ using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZeroMQ REQUIRED libzmq)
include_directories(${ZeroMQ_INCLUDE_DIRS})

# Add spdlog library
find_package(spdlog REQUIRED)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Gather all .cpp files in the src directory
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/keyboard_input_service/src/*.cpp)

# Add executable
add_executable(KeyboardInputService ${SOURCES})

# Link SDL2, ZeroMQ, and spdlog libraries
target_link_libraries(KeyboardInputService ${SDL2_LIBRARIES} ${ZeroMQ_LIBRARIES} spdlog::spdlog)

# Install target
install(TARGETS KeyboardInputService DESTINATION bin)

cmake_minimum_required(VERSION 3.10)

project(StreamerService)

# Find required packages
find_package(OpenCV REQUIRED)
find_package(SDL2 REQUIRED)
find_package(spdlog REQUIRED)

# Include directories for header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Gather all .cpp files in the src directory
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/streamer_service/src/*.cpp)

# Add executable
add_executable(StreamerService ${SOURCES})

# Link libraries
target_link_libraries(StreamerService ${OpenCV_LIBS} ${SDL2_LIBRARIES} spdlog::spdlog rt)

# Install target
install(TARGETS StreamerService DESTINATION bin)

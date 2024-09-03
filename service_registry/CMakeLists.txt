cmake_minimum_required(VERSION 3.10)

project(ServiceRegistry)

# Find SDL2, OpenCV, and spdlog
find_package(OpenCV REQUIRED)
find_package(SDL2 REQUIRED)
find_package(spdlog REQUIRED)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Gather all .cpp files in the src directory
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/service_registry/src/*.cpp)
# Add executable
add_executable(ServiceRegistry ${SOURCES})

# Link libraries
target_link_libraries(ServiceRegistry ${OpenCV_LIBS} ${SDL2_LIBRARIES} spdlog::spdlog rt)

# Install target
install(TARGETS ServiceRegistry DESTINATION bin)

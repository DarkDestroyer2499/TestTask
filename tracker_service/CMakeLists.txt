cmake_minimum_required(VERSION 3.10)

project(TrackerService)

# Find necessary packages
find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(ZeroMQ REQUIRED libzmq)

# Add spdlog library
find_package(spdlog REQUIRED)

# Add executable
add_executable(TrackerService src/main.cpp src/TrackerService.cpp)

# Include directories for SDL2 and ZeroMQ
target_include_directories(TrackerService PRIVATE ${SDL2_INCLUDE_DIRS} ${ZeroMQ_INCLUDE_DIRS})

# Link libraries
target_link_libraries(TrackerService ${OpenCV_LIBS} ${SDL2_LIBRARIES} ${ZeroMQ_LIBRARIES} spdlog::spdlog rt)

# Install target
install(TARGETS TrackerService DESTINATION bin)

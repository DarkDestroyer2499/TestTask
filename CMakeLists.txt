cmake_minimum_required(VERSION 3.10)

# Set the toolchain file for vcpkg
#set(CMAKE_TOOLCHAIN_FILE "C:/Users/Reaper/Desktop/vcpkg-master/scripts/buildsystems/vcpkg.cmake")

project(MyProject)

# Set the build type (optional)
set(CMAKE_BUILD_TYPE Release)

# Add the subdirectories for each service
add_subdirectory(service_registry)
add_subdirectory(camera_service)
add_subdirectory(streamer_service)
add_subdirectory(tracker_service)
add_subdirectory(keyboard_input_service)

# Optionally, define an install target to install all services
install(DIRECTORY ${CMAKE_BINARY_DIR}/bin/ DESTINATION bin USE_SOURCE_PERMISSIONS)

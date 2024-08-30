cmake_minimum_required(VERSION 3.10)

project(KeyboardInputService)

find_package(SDL2 REQUIRED)
find_package(ZeroMQ CONFIG REQUIRED)

add_executable(KeyboardInputService src/main.cpp)

target_link_libraries(KeyboardInputService ${SDL2_LIBRARIES} zmq)

install(TARGETS KeyboardInputService DESTINATION bin)

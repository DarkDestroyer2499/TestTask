cmake_minimum_required(VERSION 3.10)

project(ServiceRegistry)

find_package(OpenCV REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(ServiceRegistry src/main.cpp)

target_link_libraries(ServiceRegistry ${OpenCV_LIBS} ${SDL2_LIBRARIES})

install(TARGETS ServiceRegistry DESTINATION bin)

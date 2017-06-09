cmake_minimum_required(VERSION 2.8)
project (Operating_Systems_Project)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -g")
include_directories ("${PROJECT_SOURCE_DIR}")

add_executable (dm dm_main.cpp dm_launcher.cpp)
target_link_libraries (dm pthread rt)

add_executable (fi fi.cpp)
target_link_libraries(fi)

add_executable (launcher Launcher.cpp)
target_link_libraries(launcher pthread rt)

add_executable(prog1 prog1.c)

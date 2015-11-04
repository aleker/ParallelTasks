cmake_minimum_required(VERSION 3.3)
project(ParallelTasks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Process.cpp Process.h File.cpp File.h)
add_executable(ParallelTasks ${SOURCE_FILES})
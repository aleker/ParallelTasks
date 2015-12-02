cmake_minimum_required(VERSION 3.3)
project(ParallelTasks)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Process.cpp Process.h File.cpp File.h)
add_executable(ParallelTasks ${SOURCE_FILES})
add_custom_target(ParallelTasks2 COMMAND make -C ${ParallelTasks_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR}/bin)
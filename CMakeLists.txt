cmake_minimum_required(VERSION 3.10)

# set the project name
project(AI_project_cpp)

add_subdirectory(googletest)
add_subdirectory(opennn)
include_directories(googletest/googletest/include)
# add the executable
add_executable(AI_project_cpp main.cpp main_func.h)
#add_executable(AI_project_cpp_test test_main_func.cpp)
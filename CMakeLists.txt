# Author: Adriel Ting (edgec_ting@gmail.com)

# CMake Version
cmake_minimum_required(VERSION 3.30)

# Project Overview
project(
    ToyRobot
    VERSION 1.0
    DESCRIPTION "Toy Robot"
    LANGUAGES CXX)

# C++ standard required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Targets
add_subdirectory(project)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

message ("C ${CMAKE_C_COMPILER}")
message ("C++ ${CMAKE_CXX_COMPILER}")

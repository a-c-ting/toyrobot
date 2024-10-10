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
set(CMAKE_CXX_STANDARD C23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Targets
add_subdirectory(project)

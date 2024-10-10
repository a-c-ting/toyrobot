# Author: Adriel Ting (edgec_ting@gmail.com)

cmake_minimum_required(VERSION 3.30)

project(ToyRobot VERSION 1.0
                 DESCRIPTION "Toy Robot"
                 LANGUAGES CXX)

# C++ standard required
set(CNAKE_CXX_STANDARD C23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Targets
add_subdirectory(project)
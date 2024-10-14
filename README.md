Environment:
Ubuntu-24.02/WSL
gcc 13.2.0 (C++23)
CMake 3.30

Disclaimer: Project is tested only in the environment above. It might work for lower version but is not guaranteed.

Ubuntu-24.02
    available for WSL
gcc-13.2.0
    apt-get on Ubuntu-24.02
    Note: gcc-13.2.0 has yet to fully implement all C++23 features. (<print> only on 14.1 onwards)
CMake 3.30
    sudo snap install cmake

How to build:
1. go to project root folder
2. cmake -S . -B build
3. cmake --build build

How to run test
0. go to project root folder
1. finish building
2. cd build
3. ctest -V

The executable (ToyRobot) should be in the build folder.

EasyLog is used in this project:
https://github.com/RealFaceCode/easyLog


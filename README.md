# Environment:
Ubuntu-24.02 (WSL)
gcc 13.2.0 (C++20)
CMake 3.30

## Easy ways to setup
Ubuntu-24.02 is already for WSL
    wsl -l -o
    wsl --install -d <DistroName>
gcc-13.2.0
    apt-get on Ubuntu-24.02
    Note: gcc-13.2.0 has yet to fully implement all C++23 features. (<print> only on 14.1 onwards)
CMake 3.30
    sudo snap install cmake

Disclaimer: Project is tested only in the environment above. Lower version not guaranteed.

# How to build:
1. go to project root folder
2. cmake -S . -B build
3. cmake --build build

# How to run test
1. cd build
2. ctest -V

# How to run
The executable (ToyRobot) should be in the build folder. 
1. ./ToyRobot <test_input.txt location>

If no input is given, it will select test_input.txt at current location.


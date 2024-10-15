# Toy Robot

## Environment:
Ubuntu-24.02 (WSL)</br>
gcc 13.2.0 (C++20)</br>
CMake 3.30</br>

## Env Setup:
Ubuntu-24.02 is already available for WSL
>wsl -l -o</br>
>wsl --install -d (DistroName)

gcc-13.2.0
>apt-get on Ubuntu-24.02

CMake 3.30
>sudo snap install cmake

Disclaimer: Project is tested only in the environment above.

## How to build:
1. go to project root folder
2. cmake -S . -B build
3. cmake --build build

## How to run test:
1. cd build
2. ctest -V

## How to run:
The executable (ToyRobot) should be in the build folder. 
>./ToyRobot <test_input.txt location>

One command per line in the input file. If no input is given, it will select test_input.txt at current working directory. 

See test_input.txt for a sample file.

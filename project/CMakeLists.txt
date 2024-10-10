# library
add_library(RobotLib robot_lib.cpp robot_lib.hpp)

# executable
add_executable(ToyRobot toyrobot.cpp)

# link
target_link_libraries(ToyRobot PRIVATE RobotLib)

enable_testing()


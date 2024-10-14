# Catch2
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

#add_executable(tests test.cpp)
#target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# library
add_library(RobotLib robot_lib.cpp robot_lib.hpp)

# executable
add_executable(ToyRobot toyrobot.cpp)
# link
target_link_libraries(ToyRobot PRIVATE RobotLib)

# test executable
add_executable(RobotTest robot_lib_test.cpp)
# link test
target_link_libraries(RobotTest PRIVATE RobotLib Catch2::Catch2WithMain)

enable_testing()

# test
add_test(
  NAME RobotTest
  COMMAND $<TARGET_FILE:RobotTest>
)

include(Catch)

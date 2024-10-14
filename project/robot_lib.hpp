#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <string_view>
#include <algorithm>

using namespace std;

enum RobotCommand {
    PLACE,
    MOVE,
    LEFT,
    RIGHT,
    REPORT,
    INVALID
};

enum FaceDirection {
    WEST,
    NORTH,
    EAST,
    SOUTH
};

string simple_lib_function();
FaceDirection transform_to_direction_enum(string raw_direction);

class Robot {
    private:
        bool first_valid_place = false;
        //map data
        int max_x = 5;
        int max_y = 5;
        int x = 0; //current pos
        int y = 0; //current pos
        FaceDirection fd;

    public:
        Robot();
        ~Robot();

        RobotCommand parse_command(string raw_command);
        void get_input(vector<string>);
        void place(string raw_place);
        void parse_raw_place(string raw_place_details);

        // void get_map_data();
};
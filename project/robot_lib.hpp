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

enum FDirection {
    WEST,
    NORTH,
    EAST,
    SOUTH
};

FDirection transformToFDirection(string raw_direction);
tuple<int, int, FDirection> getPLACECommandDetails(string details);
FDirection turnLeftRight(FDirection current, string turn_command);
string faceDirectionToString(FDirection direction);

class Robot {
    private:
        bool first_valid_place = false;
        //map data
        int map_size_x = 5;
        int map_size_y = 5;
        int x = 0; //current pos
        int y = 0; //current pos
        FDirection fd;

    public:
        Robot();
        ~Robot();

        RobotCommand parseCommand(string raw_command);
        string report();
        void processInput(vector<string>);
        void place(string raw_place);
        bool is_out_of_bounds(int x, int y);
        // void get_map_data();
};
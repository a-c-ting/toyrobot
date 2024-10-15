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
    INVALID,
};

// Origin at Southwest = 0,0
// moving along x-axis -> east/west
// moving along y-axis -> north/south
enum FDirection {
    WEST,
    NORTH,
    EAST,
    SOUTH,
};

//helpers
FDirection transformToFDirection(string raw_direction);
tuple<int, int, FDirection> getPLACECommandDetails(string details);
FDirection turnLeftRight(FDirection current, string turn_command);
string faceDirectionToString(FDirection direction);

class Robot {
    public:
        Robot();
        ~Robot();

        void processCommand(string line);
        void processInput(vector<string>);
        tuple<int, int, string> getRobotPosition();
        // void get_map_data();

    private:
        bool is_placed_on_table = false;
        int map_size_x = 5;
        int map_size_y = 5;
        int current_x = 0; //current pos
        int current_y = 0; //current pos
        //map data
        FDirection fd;

        RobotCommand parseCommand(string raw_command);
        void place(string raw_place);
        void moveRobot();
        string report();
        bool is_out_of_bounds(int x, int y);

};


#include "robot_lib.hpp"

void Robot::processInput(vector<string> raw) {
    for (auto & line : raw) {
        processCommand(line);
    }
}

// Process single command
void Robot::processCommand(string line) {
    auto input_line = parseCommand(line);
    switch (input_line)
    {
    case RobotCommand::PLACE:
        place(line);
        break;
    case RobotCommand::MOVE:
        moveRobot();
        break;
    case RobotCommand::LEFT:
        fd = turnLeftRight(fd, line);
        break;
    case RobotCommand::RIGHT:
        fd = turnLeftRight(fd, line);
        break;
    case RobotCommand::REPORT:
        cout << report() << endl;
        break;
    case RobotCommand::INVALID:
        if (!is_placed_on_table) {
            cout << "Error: 404 Robot Not Found. Please place robot on the table." << endl;
        } else {
            cout << "Error: Unknown command. Will be ignored." << endl;
        }
        break;
    default:
        break;
    }
}

void Robot::moveRobot() {
    int x_move = 0, y_move = 0;
    switch (fd)
    {
    case FDirection::WEST:
        x_move = -1;
        break;
    case FDirection::EAST:
        x_move = 1;
        break;
    case FDirection::NORTH:
        y_move = 1;
        break;
    case FDirection::SOUTH:
        y_move = -1;
        break;
    default:
        break;
    }

    if (is_out_of_bounds(current_x + x_move, current_y + y_move)) {
        cout << "Error: Cannot move further. Hit table limits." << endl;
    } else {
        current_x += x_move;
        current_y += y_move;
    }
}

// FDirection is arranged so a turn right increases the integer equivalent and turn left decreases
FDirection turnLeftRight(FDirection current, string turn_command) {
    int turn_modifier = (turn_command == "RIGHT") ? 1 : -1;

    auto new_direct = (current + turn_modifier) % 4; //0 to 3
    if (new_direct < 0)
        new_direct = FDirection::SOUTH;

    return FDirection(new_direct);
}

string Robot::report() {
    auto result = std::to_string(current_x) + "," + std::to_string(current_y) + "," + faceDirectionToString(fd);
    return result;
}

//Inconsistency: x,y param(stoi) ignores leading/trailing spaces. Direction doesn't. Might fix.
void Robot::place(string raw_place) {
    int OFFSET = 6; //"PLACE " takes 6 characters
    auto raw_place_details = raw_place.substr(OFFSET);
    try {
        auto [temp_x, temp_y, temp_fd] = getPLACECommandDetails(raw_place_details);

        //validate map bound
        if (is_out_of_bounds(temp_x, temp_y)) {
            throw std::runtime_error("Error: PLACE command out of bounds.");
        }

        current_x = temp_x;
        current_y = temp_y;
        fd = temp_fd;
    } catch (const exception& e) {
        current_x = 0;
        current_y = 0;
        is_placed_on_table = false;

        cout << e.what() << endl;
    }
}

//0, 0 origin
bool Robot::is_out_of_bounds(int x, int y) {
    auto max_x = map_size_x - 1, max_y = map_size_y - 1;
    return (x < 0) || (x > max_x) || (y < 0) || (y > max_y);
}

FDirection transformToFDirection(string raw_direction) {
    FDirection result;
    //case insensitive
    std::transform(raw_direction.begin(), raw_direction.end(), raw_direction.begin(), ::toupper);

    if ("WEST" == raw_direction) {
        result = FDirection::WEST;
    } else if ("NORTH" == raw_direction) {
        result = FDirection::NORTH;
    } else if ("EAST" == raw_direction) {
        result = FDirection::EAST;
    } else if ("SOUTH" == raw_direction) {
        result = FDirection::SOUTH;
    } else {
        throw std::runtime_error("Error: Invalid DIRECTION.");
    }
    return result;
}

string faceDirectionToString(FDirection direction) {
    auto result = "";
    switch (direction)
    {
    case FDirection::WEST:
        result = "WEST";
        break;
    case FDirection::NORTH:
        result = "NORTH";
        break;
    case FDirection::EAST:
        result = "EAST";
        break;
    case FDirection::SOUTH:
        result = "SOUTH";
        break;
    default:
        break;
    }
    return result;
}

RobotCommand Robot::parseCommand(string raw_command) {
    RobotCommand result;
    std::transform(raw_command.begin(), raw_command.end(), raw_command.begin(), ::toupper);
    if (true == raw_command.starts_with("PLACE ")) {
        result = RobotCommand::PLACE;
        is_placed_on_table = true;
    } else if (!is_placed_on_table) {
        result = RobotCommand::INVALID;
    } else if ("MOVE" == raw_command) {
        result = RobotCommand::MOVE;
    } else if ("LEFT" == raw_command) {
        result = RobotCommand::LEFT;
    } else if ("RIGHT" == raw_command) {
        result = RobotCommand::RIGHT;
    } else if ("REPORT" == raw_command) {
        result = RobotCommand::REPORT;
    } else {
        result = RobotCommand::INVALID;
    }

    return result;
};

//Output: x, y, direction facing
tuple<int, int, FDirection> getPLACECommandDetails(string details) {
    //tokenize
    vector<string> temp_details;
    string temp;
    stringstream ss(details);
    while(getline(ss, temp, ',')) {
        temp_details.push_back(temp);
    }

    //validate input
    if (3 != temp_details.size()) {// three params X,Y,Z
        throw std::runtime_error("Error: PLACE command parameter mismatch.");
    }

    //TODO: short wrapper for stoi might be a good idea since stoi exception desc is not good.
    return {stoi(temp_details[0]),
        stoi(temp_details[1]),
        transformToFDirection(temp_details[2])};
}

tuple<int, int, string> Robot::getRobotPosition() {
    return {current_x, current_y, faceDirectionToString(fd)};
}

Robot::Robot() {
}

Robot::~Robot() {
}

#include "robot_lib.hpp"

void Robot::processInput(vector<string> raw) {
    cout << "processInput start" << endl;

    for (auto & line : raw) {
        auto input_line = parseCommand(line);
        switch (input_line)
        {
        case RobotCommand::PLACE:
            Robot::place(line);
            break;
        case RobotCommand::MOVE:
            break;
        case RobotCommand::LEFT:
            fd = turnLeftRight(fd, line);
            break;
        case RobotCommand::RIGHT:
            fd = turnLeftRight(fd, line);
            break;
        case RobotCommand::REPORT:
            cout << "pos: " << report() << endl;
            break;
        case RobotCommand::INVALID:
            if (false == first_valid_place) {
                cout << "Error: 404 Robot Not Found. Please place robot on the table." << endl;
            } else {
                cout << "Error: Unknown command. Will be ignored." << endl;
            }
            break;
        default:
            break;
        }
    }

    cout << "processInput end" << endl;
}

// FDirection is arranged so a turn right increases the integer equivalent
// +1 right, -1 left
FDirection turnLeftRight(FDirection current, string turn_command) {
    int turn_modifier = (turn_command == "RIGHT") ? 1 : -1;

    auto new_direct = (current + turn_modifier) % 4; //0 to 3
    if (new_direct < 0)
        new_direct = FDirection::SOUTH;

    cout << "turning " + turn_command << ": " << current << " to " << new_direct << endl;

    return FDirection(new_direct);
}

string Robot::report() {
    auto result = std::to_string(x) + "," + std::to_string(y) + "," + faceDirectionToString(fd);
    return result;
}

//Inconsistency: x,y param(stoi) ignores leading/trailing spaces. Direction doesn't. Might fix.
void Robot::place(string raw_place) {
    int OFFSET = 6; //"PLACE " takes 6 characters
    auto raw_place_details = raw_place.substr(OFFSET);
    cout << "PLACE attempted" << endl;
    try {
        auto [temp_x, temp_y, temp_fd] = getPLACECommandDetails(raw_place_details);

        //validate map bound
        if (is_out_of_bounds(temp_x, temp_y)) {
            throw std::runtime_error("Error: PLACE command out of bounds.");
        }

        x = temp_x;
        y = temp_y;
        fd = temp_fd;
        cout << "PLACE successful" << endl;
    } catch (const exception& e) {
        first_valid_place = false;
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
        first_valid_place = true;
    } else if (false == first_valid_place) {
        result = RobotCommand::INVALID;
    } else if ("MOVE" == raw_command)
    {
        result = RobotCommand::MOVE;
    } else if ("LEFT" == raw_command)
    {
        result = RobotCommand::LEFT;
    } else if ("RIGHT" == raw_command)
    {
        result = RobotCommand::RIGHT;
    } else if ("REPORT" == raw_command)
    {
        result = RobotCommand::REPORT;
    } else
    {
        result = RobotCommand::INVALID;
    }

    return result;
};

//TODO: short short wrapper for stoi might be a good idea since stoi exception
//  doesn't have good description.
tuple<int, int, FDirection> getPLACECommandDetails(string details) {
    //tokenize
    vector<string> temp_details;
    string temp;
    stringstream ss(details);
    while(getline(ss, temp, ',')) {
        temp_details.push_back(temp);
    }

    //validate input
    if (3 != temp_details.size()) { // three params X,Y,Z
        throw std::runtime_error("Error: PLACE command parameter mismatch.");
    }

    //specs: x, y, direction facing
    return {stoi(temp_details[0]),
        stoi(temp_details[1]),
        transformToFDirection(temp_details[2])};
}

Robot::Robot() {
    // cout << "Constructor" << endl;
}

Robot::~Robot() {
    // cout << "Destructor" << endl;
}

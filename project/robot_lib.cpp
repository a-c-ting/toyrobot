// #include <string>
#include "robot_lib.hpp"

void Robot::get_input(vector<string> raw) {
    cout << "get_input start" << endl;

    for (auto & line : raw) {
        auto input_line = parse_command(line);
        switch (input_line)
        {
        case RobotCommand::PLACE:
            cout << "PLACE" << endl;

            Robot::place(line);
            break;
        case RobotCommand::MOVE:
            cout << "MOVE" << endl;
            break;
        case RobotCommand::LEFT:
            cout << "LEFT" << endl;
            break;
        case RobotCommand::RIGHT:
            cout << "RIGHT" << endl;
            break;
        case RobotCommand::REPORT:
            cout << "REPORT" << endl;
            break;
        case RobotCommand::INVALID:
            if (false == first_valid_place) {
                cout << "Error: Invalid PLACE command." << endl;
            } else {
                cout << "Error: Unknown command. Ignoring." << endl;
            }
            break;
        default:
            break;
        }
        cout << line << endl;
    }

    cout << "get_input end" << endl;
}

void Robot::place(string raw_place) {
    parse_raw_place(raw_place.substr(6));
};

void Robot::parse_raw_place(string raw_place_details) {
    try {
        vector<string> temp_details;
        string temp;
        stringstream ss(raw_place_details);
        while(getline(ss, temp, ',')) {
            temp_details.push_back(temp);
        }

        //validation
        if ((3 != temp_details.size())  //three params X,Y,F
            || (stoi(temp_details[0]) < 0) // boundary checks
            || (stoi(temp_details[0]) > 4)
            || (stoi(temp_details[1]) < 0)
            || (stoi(temp_details[1]) > 4)
        ) {
            throw std::runtime_error("Error: Invalid PLACE command.");
        }

        x = stoi(temp_details[0]);
        y = stoi(temp_details[1]);
        fd = transform_to_direction_enum(temp_details[2]);
    } catch (const exception& e) {
        first_valid_place = false;
        cout << e.what() << endl;
    }
}

FaceDirection transform_to_direction_enum(string raw_direction) {
    FaceDirection result;
    std::transform(raw_direction.begin(), raw_direction.end(), raw_direction.begin(), ::toupper);
    if ("WEST" == raw_direction) {
        result = FaceDirection::WEST;
    } else if ("NORTH" == raw_direction) {
        result = FaceDirection::NORTH;
    } else if ("EAST" == raw_direction) {
        result = FaceDirection::EAST;
    } else if ("SOUTH" == raw_direction) {
        result = FaceDirection::SOUTH;
    } else {
        throw std::runtime_error("Error: Invalid DIRECTION.");
    }
    return result;
}

RobotCommand Robot::parse_command(string raw_command) {
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

Robot::Robot() {
    cout << "Constructor" << endl;
}

Robot::~Robot() {
    cout << "Destructor" << endl;
}

string simple_lib_function() {
    return "Compiled in library";
}

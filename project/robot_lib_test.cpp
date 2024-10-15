#include <catch2/catch_all.hpp>
#include "robot_lib.hpp"

struct gFixture {
    string gPlace = "PLACE ";
    string gMove = "MOVE";
    string gReport = "REPORT";
    string gLeft = "LEFT";
    string gRight = "RIGHT";
    string west = "WEST";
    string north = "NORTH";
    string east = "EAST";
    string south = "SOUTH";

    Robot g;
};

TEST_CASE_METHOD(gFixture, "MOVE command boundary check", "[UT]") {
    vector<string> input = {
        "0,0,SOUTH", "1,0,SOUTH", "2,0,SOUTH", "3,0,SOUTH", "4,0,SOUTH",
        "0,4,NORTH", "1,4,NORTH", "2,4,NORTH", "3,4,NORTH", "4,4,NORTH",
        "0,0,WEST", "0,1,WEST", "0,2,WEST", "0,3,WEST", "0,4,WEST",
        "4,0,EAST", "4,1,EAST", "4,2,EAST", "4,3,EAST", "4,4,EAST",
    };

    for (auto & pos : input) {
        g.processCommand(gPlace + pos);
        auto [x1,y1,d1] = g.getRobotPosition();
        g.processCommand(gMove);
        auto [x2,y2,d2] = g.getRobotPosition();
        REQUIRE ( x1 == x2 ) ;
        REQUIRE ( y1 == y2 ) ;
        REQUIRE ( d1 == d2 ) ;
    }
}

TEST_CASE_METHOD(gFixture, "MOVE command normal move", "[UT]") {
    // tuple: (input, expected_x, expected_y)
    vector<tuple<string,int,int>> input_expected = {
        {"2,2,WEST",    1,2},
        {"2,2,NORTH",   2,3},
        {"2,2,EAST",    3,2},
        {"2,2,SOUTH",   2,1},
    };

    for (auto & [pos, expected_x, expected_y ] : input_expected) {
        g.processCommand(gPlace + pos);
        g.processCommand(gMove);
        auto [x,y,d] = g.getRobotPosition();
        REQUIRE( x == expected_x ) ;
        REQUIRE( y == expected_y ) ;
    }
}

TEST_CASE_METHOD( gFixture, "PLACE command with checks valid results", "[UT]" ) {
    vector<string> input = {
        "0,0,NORTH", "1,1,SOUTH", "4,4,EAST",
        "4,0,WEST", "2,2,SOUTH", "0,4,WEST",
    };

    for (auto & pos : input) {
        auto [x1,y1,d1] = getPLACECommandDetails(pos);
        REQUIRE_NOTHROW(g.processCommand(gPlace + pos));
        auto [x2,y2,d2] = g.getRobotPosition();
        REQUIRE( x1 == x2 );
        REQUIRE( y1 == y2 );
    }
}

TEST_CASE_METHOD( gFixture, "PLACE command with invalid coordinate", "[UT]")  {
    vector<string> input = {
        "-1,0", "-1,-1", "0,-1",
        "5,0", "0,5", "5,5",
        "-1,5", "5,-5", "5000000000,-5000",
    };

    //ignore place and reset robot x, y to 0,0
    for (auto & pos : input) {
        g.processCommand(gPlace + pos + "," + north);
        auto [x,y,d] = g.getRobotPosition();
        REQUIRE( x == 0 );
        REQUIRE( y == 0 );
    }
}

TEST_CASE( "Turn left/right should cycle", "[UT]" ) {
    vector<tuple<FDirection, FDirection>> test_right = {
        {FDirection::WEST,  FDirection::NORTH},
        {FDirection::NORTH, FDirection::EAST},
        {FDirection::EAST,  FDirection::SOUTH},
        {FDirection::SOUTH, FDirection::WEST},
    };

    for (auto & [input, expected] : test_right) {
        REQUIRE( expected == turnLeftRight(input ,"RIGHT"));
    }

    vector<tuple<FDirection, FDirection>> test_left = {
        {FDirection::WEST,  FDirection::SOUTH},
        {FDirection::NORTH, FDirection::WEST},
        {FDirection::EAST,  FDirection::NORTH},
        {FDirection::SOUTH, FDirection::EAST},
    };

    for (auto & [input, expected] : test_left) {
        REQUIRE( expected == turnLeftRight(input ,"LEFT"));
    }
}

TEST_CASE_METHOD( gFixture, "Travel to center clockwise", "[Integration]") {
    //start at 0,0,North,
    //travel to center in a clockwise fashion while hitting all tiles once
    vector<string> travel_commands = {
        gPlace + "0,0," + north, gMove, gMove, gMove, gMove, gRight,
        gReport,    //checkpoint 1
        gMove, gMove, gMove, gMove, gRight,
        gReport,    //2
        gMove, gMove, gMove, gMove, gRight,
        gReport,    //3
        gMove, gMove, gMove, gRight,
        gReport,    //4
        gMove, gMove, gMove, gRight,
        gReport,    //5
        gMove, gMove, gRight,
        gReport,    //6
        gMove, gMove, gRight,
        gReport,    //7
        gMove, gRight,
        gReport,    //8
        gMove,
        gReport,    //9 end
    };

    tuple<int,int,string> final_destination = {2,2,north};
    vector<tuple<int,int,string>> expected_Report = {
        {0, 4, east},       //1
        {4, 4, south},      //2
        {4, 0, west},       //3
        {1, 0, north},      //4
        {1, 3, east},       //5
        {3, 3, south},      //6
        {3, 1, west},       //7
        {2, 1, north},      //8
        final_destination,  //9 end
    };

    auto i = 0;
    for (auto & command : travel_commands) {
        g.processCommand(command);
        if (command == gReport) {
            auto [x,y,d] = g.getRobotPosition();
            auto [e_x, e_y, e_d] = expected_Report[i];

            REQUIRE( e_x == x );
            REQUIRE( e_y == y );
            REQUIRE( e_d == d );

            ++i;
        }
    }

    //test place a second time, using processInput
    g.processInput(travel_commands);
    auto final_position = g.getRobotPosition();
    REQUIRE( final_position == final_destination);
}


#include <catch2/catch_all.hpp>
#include "robot_lib.hpp"

TEST_CASE( "Test trial", "[dumdidum]" ) {
    REQUIRE( "Compiled in library" == simple_lib_function() );
}

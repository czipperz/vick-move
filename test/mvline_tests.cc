/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../src/move.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvline;

TEST_CASE("mvline", "[mvline]") {
    contents contents;
    contents.x = 1; // make sure set x to 0
    contents.push_back("hi");
    contents.push_back("bye");
    contents.push_back("aseuior");
    contents.push_back("etc");

    initscr();
    mvline(contents, 1);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);

    mvline(contents, -1);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);

    mvline(contents, 4);
    CHECK(contents.y == 3);
    CHECK(contents.x == 0);
    endwin();
}

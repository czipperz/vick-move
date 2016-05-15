#include <ncurses.h>

#include "../src/move.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvb;

TEST_CASE("mvb", "[mvb]") {
    contents contents(1, 0);
    contents.push_back("assert");
    contents.push_back("back");

    initscr();
    mvb(contents, 2);
    CHECK(contents.y == 0);
    CHECK(contents.x == 4);
    endwin();
}

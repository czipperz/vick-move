/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvb;

TEST_CASE("mvb", "[mvb]") {
    contents contents({"assert", "back"});
    contents.yx(1, 0);

    initscr();
    mvb(contents, 2);
    CHECK(contents.y == 0);
    CHECK(contents.x == 4);
    endwin();
}

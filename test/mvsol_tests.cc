/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../src/move.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvsol;

TEST_CASE("mvsol", "[mvsol]") {
    contents contents(0, 5);
    contents.push_back("    assert");

    initscr();
    mvsol(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
    endwin();
}

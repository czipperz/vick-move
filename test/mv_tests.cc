/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../src/move.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mv;

TEST_CASE("mv", "[mv]") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("blah");
    contents.push_back("hi");
    contents.push_back("nop");

    initscr();
    mv(contents, 1, 4); // past end
    CHECK(contents.y == 1);
    CHECK(contents.x == 3);

    mv(contents, 2, 0);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);

    mv(contents, 6, 2);
    CHECK(contents.y == 3);
    CHECK(contents.x == 2);
    endwin();
}

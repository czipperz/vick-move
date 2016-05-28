/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mveol;

TEST_CASE("mveol", "[mveol]") {
    contents contents;
    contents.push_back("Aesop");

    initscr();
    mveol(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 4);
    endwin();
}

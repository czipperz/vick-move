/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../src/move.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvfeow;

TEST_CASE("mvfeow", "[mvfeow]") {
    contents contents;
    contents.push_back(" a bunch of random text to test it");

    initscr();
    mvfeow(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);

    mvfeow(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 7);
    endwin();
}

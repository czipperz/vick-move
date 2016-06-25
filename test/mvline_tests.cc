/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("mvline", "[mvline]") {
    contents contents({"hi", "bye", "aseuior", "etc"});
    contents.yx(0, 1); // make sure set x to 0

    visual_setup _;
    line(contents, 1);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);

    line(contents, -1);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);

    line(contents, 4);
    CHECK(contents.y == 3);
    CHECK(contents.x == 0);
}

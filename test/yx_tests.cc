/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::yx 1", "[vick::move][vick::move::yx]") {
    contents contents({"assert", "blah", "hi", "nop"});

    yx(contents, 1, 7); // past end
    CHECK(contents.y == 1);
    CHECK(contents.x == 4);
    CHECK(contents.waiting_for_desired);
    CHECK(contents.desired_x.unwrap() == 7);

    yx(contents, 2, 0);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);
    CHECK_FALSE(contents.waiting_for_desired);

    yx(contents, 6, 2);
    CHECK(contents.y == 4);
    CHECK(contents.x == 0);
}

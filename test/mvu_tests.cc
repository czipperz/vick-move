/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvu;

TEST_CASE("mvu", "[mvu]") {
    contents contents({"hi", "Alabama"});
    contents.yx(1, 6);

    initscr();
    mvu(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);
    CHECK(contents.waiting_for_desired);
    CHECK(contents.desired_x == 6);
    endwin();
}

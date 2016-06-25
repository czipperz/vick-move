/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("mv", "[mv]") {
    contents contents({"assert", "blah", "hi", "nop"});

    yx(contents, 1, 4); // past end
    CHECK(contents.y == 1);
    CHECK(contents.x == 3);

    yx(contents, 2, 0);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);

    yx(contents, 6, 2);
    CHECK(contents.y == 3);
    CHECK(contents.x == 2);
}

/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("mveol", "[mveol]") {
    contents contents({"Aesop"});

    end_line(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 5);
}

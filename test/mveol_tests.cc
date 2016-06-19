/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mveol;

TEST_CASE("mveol", "[mveol]") {
    contents contents({"Aesop"});

    mveol(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 4);
}

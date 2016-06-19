/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvcol;

TEST_CASE("mvcol", "[mvcol]") {
    contents contents({"asert"});

    visual_setup _;
    mvcol(contents, 3);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);

    mvcol(contents, 10); // doesn't do anything
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);

    mvcol(contents, 0);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
}

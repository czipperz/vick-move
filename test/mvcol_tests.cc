/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("mvcol", "[mvcol]") {
    contents contents({"asert"});

    visual_setup _;
    column(contents, 3);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);
    CHECK_FALSE(contents.waiting_for_desired);

    column(contents, 5);
    CHECK(contents.y == 0);
    CHECK(contents.y == 5);
    CHECK_FALSE(contents.waiting_for_desired);

    column(contents, 10); // doesn't do anything
    CHECK(contents.y == 0);
    CHECK(contents.x == 5);
    CHECK(contents.desired_x == 10);
    CHECK(contents.waiting_for_desired);

    column(contents, 0);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
    CHECK_FALSE(contents.waiting_for_desired);
}

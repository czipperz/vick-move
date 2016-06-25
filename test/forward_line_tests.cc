/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::forward_line",
          "[vick::move][vick::move::forward_line]") {
    contents contents({"assert", "hello", "aseuirpo"});
    contents.x = 5;
    visual_setup _;

    forward_line(contents, 2);
    CHECK(contents.y == 2);
    CHECK(contents.x == 5);
    CHECK_FALSE(contents.waiting_for_desired);

    forward_line(contents, boost::none);
    CHECK(contents.y == 3);
    CHECK(contents.x == 0);
    CHECK(contents.waiting_for_desired);
    CHECK(contents.desired_x.unwrap() == 5);
}

TEST_CASE("vick::move::forward_line 2",
          "[vick::move][vick::move::forward_line]") {
    contents contents(
        {"CFLAGS=-lncurses -Wall", "O=out", "S=src", "T=test"});
    contents.yx(0, 20);
    visual_setup _;

    forward_line(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 5);
    CHECK(contents.waiting_for_desired);
    CHECK(contents.desired_x.unwrap() == 20);

    contents.x = 2;

    forward_line(contents, boost::none);
    CHECK(contents.y == 2);
    CHECK(contents.x == 5);
    CHECK(contents.waiting_for_desired);
    CHECK(contents.desired_x.unwrap() == 20);
}

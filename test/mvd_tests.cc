/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("mvd", "[mvd]") {
    contents contents({"assert", "hello", "aseuirpo"});
    contents.x = 5;

    forward_line(contents, 2);
    CHECK(contents.y == 2);
    CHECK(contents.x == 5);

    forward_line(contents, boost::none);
    CHECK(contents.y == 2);
    CHECK(contents.x == 5);
}

TEST_CASE("mvd_2", "[mvd]") {
    contents contents(
        {"CFLAGS=-lncurses -Wall", "O=out", "S=src", "T=test"});
    contents.yx(0, 21);

    forward_line(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 5);
    CHECK(contents.desired_x == 21);
    CHECK(contents.waiting_for_desired);

    forward_line(contents, boost::none);
    CHECK(contents.y == 2);
    CHECK(contents.x == 5);
    CHECK(contents.desired_x == 21);
    CHECK(contents.waiting_for_desired);
}

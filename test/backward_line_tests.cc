/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::backward_line",
          "[vick::move][vick::move::backward_line]") {
    contents contents({"as", "hello", "aseuirpo"});
    // aseui|rpo
    contents.yx(2, 5);
    visual_setup _;

    // hello|
    backward_line(contents, 1);
    CHECK(contents.y == 1);
    CHECK(contents.x == 5);
    CHECK_FALSE(contents.waiting_for_desired);

    // as|
    backward_line(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 2);
    CHECK(contents.waiting_for_desired);
    CHECK(contents.desired_x == 5);
}

TEST_CASE("vick::move::backward_line 2",
          "[vick::move][vick::move::backward_line]") {
    contents contents(
        {"CFLAGS=-lncurses -Wall", "O=out", "S=src", "T=test"});
    // -Wa|ll  but S=src
    contents.yx(2, 20);
    visual_setup _;

    backward_line(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 5);
    CHECK(contents.waiting_for_desired);
    CHECK(contents.desired_x == 20);

    SECTION("continued") {
        backward_line(contents, boost::none);
        CHECK(contents.y == 0);
        CHECK(contents.x == 20);
        CHECK_FALSE(contents.waiting_for_desired);
    }
    SECTION("broken") {
        contents.waiting_for_desired = false;
        backward_line(contents, boost::none);
        CHECK(contents.y == 0);
        CHECK(contents.x == 5);
        CHECK_FALSE(contents.waiting_for_desired);
    }
}

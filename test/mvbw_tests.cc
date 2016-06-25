/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("mvbw", "[mvbw]") {
    contents contents({" a bunch of random text to test it"});
    contents.x = contents.cont[0].size() - 1;

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 32);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 27);
}

TEST_CASE("mvbw_2", "[mvbw]") {
    contents contents({" {-# LANGUAGE CPP #-}"});
    contents.yx(0, 5);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);
}

TEST_CASE("mvbw_3", "[mvbw]") {
    contents contents({"  {-# LANGUAGE CPP #-}"});
    contents.yx(0, 6);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 2);
}

TEST_CASE("mvbw_4", "[mvbw]") {
    contents contents({"{-# LANGUAGE CPP #-}"});
    contents.yx(0, 4);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
}

TEST_CASE("mvbw_over_lines", "[mvbw]") {
    contents contents(
        {"", "", "#endif", "", "import Development.Shake"});
    contents.yx(4, 10);

    backward_begin_word(contents);
    CHECK(contents.y == 4);
    CHECK(contents.x == 7);

    backward_begin_word(contents);
    CHECK(contents.y == 4);
    CHECK(contents.x == 0);

    backward_begin_word(contents);
    CHECK(contents.y == 2);
    CHECK(contents.x == 1);

    backward_begin_word(contents);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
}

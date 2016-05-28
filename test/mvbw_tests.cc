/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvbw;

TEST_CASE("mvbw", "[mvbw]") {
    contents contents;
    contents.push_back(" a bunch of random text to test it");
    contents.x = contents.cont[0].size() - 1;

    initscr();
    mvbw(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 32);

    mvbw(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 27);
    endwin();
}

TEST_CASE("mvbw_2", "[mvbw]") {
    contents contents;
    contents.push_back(" {-# LANGUAGE CPP #-}");
    contents.x = 5;
    REQUIRE(contents.y == 0);

    initscr();
    mvbw(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);
    endwin();
}

TEST_CASE("mvbw_3", "[mvbw]") {
    contents contents;
    contents.push_back("  {-# LANGUAGE CPP #-}");
    contents.x = 6;
    REQUIRE(contents.y == 0);

    initscr();
    mvbw(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 2);
    endwin();
}

TEST_CASE("mvbw_4", "[mvbw]") {
    contents contents;
    contents.push_back("{-# LANGUAGE CPP #-}");
    contents.x = 4;
    REQUIRE(contents.y == 0);

    initscr();
    mvbw(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
    endwin();
}

TEST_CASE("mvbw_over_lines", "[mvbw]") {
    contents contents;
    contents.push_back("");
    contents.push_back("");
    contents.push_back("#endif");
    contents.push_back("");
    contents.push_back("import Development.Shake");

    contents.y = 4;
    contents.x = 10;

    initscr();
    mvbw(contents);
    CHECK(contents.y == 4);
    CHECK(contents.x == 7);

    mvbw(contents);
    CHECK(contents.y == 4);
    CHECK(contents.x == 0);

    mvbw(contents);
    CHECK(contents.y == 2);
    CHECK(contents.x == 1);

    mvbw(contents);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);

    mvbw(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
    endwin();
}

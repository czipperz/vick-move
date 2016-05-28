/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvd;

TEST_CASE("mvd", "[mvd]") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("hello");
    contents.push_back("aseuirpo");

    initscr();
    mvd(contents, 2);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);

    mvd(contents, boost::none);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);
    endwin();
}

TEST_CASE("mvd_2", "[mvd]") {
    contents contents;
    contents.push_back("CFLAGS=-lncurses -Wall");
    contents.push_back("O=out");
    contents.push_back("S=src");
    contents.push_back("T=test");

    contents.y = 0;
    contents.x = 21;

    initscr();
    mvd(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 4);
    CHECK(contents.desired_x == 21);
    CHECK(contents.waiting_for_desired);

    mvd(contents, boost::none);
    CHECK(contents.y == 2);
    CHECK(contents.x == 4);
    CHECK(contents.desired_x == 21);
    CHECK(contents.waiting_for_desired);
    endwin();
}

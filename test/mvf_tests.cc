/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvf;

TEST_CASE("mvf", "[mvf]") {
    contents contents({"assert", "hello"});

    initscr();
    mvf(contents, 3);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);

    mvf(contents, 4);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
    endwin();
}

TEST_CASE("mvf_2", "[mvf]") {
    contents contents({"CFLAGS=-lncurses -Wall", "O=out", "S=src",
                       "T=test", "TO=testout", "CC=g++"});

    contents.y = 0;
    contents.x = 21;

    initscr();
    mvf(contents, 2);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
    endwin();
}

TEST_CASE("mvf_over_empty_lines", "[mvf]") {
    contents contents({"hi", "", "hi"});
    contents.yx(0, 1);

    initscr();
    mvf(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);
    endwin();
}

TEST_CASE("mvf_over_tabs", "[mvf]") {
    contents contents({"testVI: ${files} $O/main.o",
                       "\t${CC} -o testVI $^ $(CFLAGS)"});
    contents.yx(0, 25);

    initscr();
    mvf(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);

    mvf(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
    endwin();
}

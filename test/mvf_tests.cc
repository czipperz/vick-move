/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("mvf", "[mvf]") {
    contents contents({"assert", "hello"});

    forward_char(contents, 3);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);

    forward_char(contents, 4);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
}

TEST_CASE("mvf_2", "[mvf]") {
    contents contents({"CFLAGS=-lncurses -Wall", "O=out", "S=src",
                       "T=test", "TO=testout", "CC=g++"});
    contents.yx(0, 21);

    forward_char(contents, 2);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
}

TEST_CASE("mvf_over_empty_lines", "[mvf]") {
    contents contents({"hi", "", "hi"});
    contents.yx(0, 1);

    forward_char(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 2);

    forward_char(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);

    forward_char(contents, boost::none);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);
}

TEST_CASE("mvf_over_tabs", "[mvf]") {
    contents contents({"testVI: ${files} $O/main.o",
                       "\t${CC} -o testVI $^ $(CFLAGS)"});
    contents.yx(0, 25);

    forward_char(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 26);

    forward_char(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);

    forward_char(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
}

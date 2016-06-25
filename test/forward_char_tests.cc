/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::forward_char 1",
          "[vick::move][vick::move::forward_char]") {
    contents c({"asdf"});
    visual_setup _;

    forward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 1);

    forward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 2);

    forward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 3);

    forward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 4);

    forward_char(c);
    CHECK(c.y == 1);
    CHECK(c.x == 0);

    forward_char(c);
    CHECK(c.y == 1);
    CHECK(c.x == 0);
}

TEST_CASE("vick::move::forward_char 2",
          "[vick::move][vick::move::forward_char]") {
    contents c;

    REQUIRE(c.cont.size() == 1);
    REQUIRE(c.cont[0].size() == 0);

    visual_setup _;
    forward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 0);
}

TEST_CASE("vick::move::forward_char 3",
          "[vick::move][vick::move::forward_char]") {
    contents contents({"assert", "hello"});

    forward_char(contents, 3);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);

    forward_char(contents, 5);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
}

TEST_CASE("vick::move::forward_char 4",
          "[vick::move][vick::move::forward_char]") {
    contents contents({"CFLAGS=-lncurses -Wall", "O=out", "S=src",
                       "T=test", "TO=testout", "CC=g++"});
    contents.yx(0, 21);

    forward_char(contents, 2);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);
}

TEST_CASE("vick::move::forward_char over empty lines",
          "[vick::move][vick::move::forward_char]") {
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

TEST_CASE("vick::move::forward_char over tabs",
          "[vick::move][vick::move::forward_char]") {
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

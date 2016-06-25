/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "catch.hpp"

#include "../lib.hh"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::forward_begin_word 1",
          "[vick::move][vick::move::forward_begin_word]") {
    contents c({"a s d f"});

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 2);

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 4);

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 6);

    forward_begin_word(c);
    REQUIRE(c.y == 1);
    REQUIRE(c.x == 0);
}

TEST_CASE("vick::move::forward_begin_word 2",
          "[vick::move][vick::move::forward_begin_word]") {
    contents c({"  a    b ", " \t c d  "});

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 2);

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 7);

    forward_begin_word(c);
    REQUIRE(c.y == 1);
    REQUIRE(c.x == 3);

    forward_begin_word(c);
    REQUIRE(c.y == 1);
    REQUIRE(c.x == 5);

    forward_begin_word(c);
    REQUIRE(c.y == 2);
    REQUIRE(c.x == 0);

    forward_begin_word(c);
    REQUIRE(c.y == 2);
    REQUIRE(c.x == 0);
}

TEST_CASE("vick::move::forward_begin_word 3",
          "[vick::move][vick::move::forward_begin_word]") {
    contents c({"\tword", "", "", " ", "", " asdf"});

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 1);

    forward_begin_word(c);
    REQUIRE(c.y == 5);
    REQUIRE(c.x == 1);

    forward_begin_word(c);
    REQUIRE(c.y == 6);
    REQUIRE(c.x == 0);
}

TEST_CASE("vick::move::forward_begin_word 4",
          "[vick::move][vick::move::forward_begin_word]") {
    // DELIMINATORS for testing includes {()}
    contents c({"word {a(b)c}"});

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 5);

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 6);

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 7);

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 8);

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 9);

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 10);

    forward_begin_word(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 11);

    forward_begin_word(c);
    REQUIRE(c.y == 1);
    REQUIRE(c.x == 0);
}

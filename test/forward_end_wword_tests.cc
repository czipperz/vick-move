/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "catch.hpp"

#include "../lib.hh"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::forward_end_wword 1",
          "[vick::move][vick::move::forward_end_wword]") {
    contents c({"a s d f"});

    forward_end_wword(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 1);

    forward_end_wword(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 3);

    forward_end_wword(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 5);

    forward_end_wword(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 7);
}

TEST_CASE("vick::move::forward_end_wword 2",
          "[vick::move][vick::move::forward_end_wword]") {
    contents c({"a    b ", " \t c d  "});

    forward_end_wword(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 1);

    forward_end_wword(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 6);

    forward_end_wword(c);
    REQUIRE(c.y == 1);
    REQUIRE(c.x == 4);

    forward_end_wword(c);
    REQUIRE(c.y == 1);
    REQUIRE(c.x == 6);

    forward_end_wword(c);
    REQUIRE(c.y == 2);
    REQUIRE(c.x == 0);

    forward_end_wword(c);
    REQUIRE(c.y == 2);
    REQUIRE(c.x == 0);
}

TEST_CASE("vick::move::forward_end_wword 3",
          "[vick::move][vick::move::forward_end_wword]") {
    contents c({"word", "", "", " ", "", " asdf"});

    forward_end_wword(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 4);

    forward_end_wword(c);
    REQUIRE(c.y == 5);
    REQUIRE(c.x == 5);
}

TEST_CASE("vick::move::forward_end_wword 4",
          "[vick::move][vick::move::forward_end_wword]") {
    contents c({"word {a(b)c}"});

    forward_end_wword(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 4);

    forward_end_wword(c);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 12);

    forward_end_wword(c);
    REQUIRE(c.y == 1);
    REQUIRE(c.x == 0);
}

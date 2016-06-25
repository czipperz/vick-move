/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "catch.hpp"

#include "../lib.hh"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::start_text 1",
          "[vick::move][vick::move::start_text]") {
    contents c({"   asdf", "ayy"});

    start_text(c);
    REQUIRE(c.x == 3);

    // repeat
    start_text(c);
    REQUIRE(c.x == 3);

    c.y = 1;

    start_text(c);
    REQUIRE(c.x == 0);

    // repeat
    start_text(c);
    REQUIRE(c.x == 0);
}

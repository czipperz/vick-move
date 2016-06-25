/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "catch.hpp"

#include "../lib.hh"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::end_text 1",
          "[vick::move][vick::move::end_text]") {
    contents c({"asdf   ", "ayy"});

    end_text(c);
    REQUIRE(c.x == 4);

    // repeat
    end_text(c);
    REQUIRE(c.x == 4);

    c.y = 1;

    end_text(c);
    REQUIRE(c.x == 3);

    // repeat
    end_text(c);
    REQUIRE(c.x == 3);
}

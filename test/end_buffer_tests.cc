/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::end_buffer 1",
          "[vick::move][vick::move::end_buffer]") {
    contents contents({"assert", "blah", "hi", "nop"});

    end_buffer(contents);
    CHECK(contents.y == 4);
    CHECK(contents.x == 0);

    contents.cont.pop_back();

    end_buffer(contents);
    CHECK(contents.y == 3);
    CHECK(contents.x == 3);
}

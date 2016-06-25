/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::start_buffer",
          "[vick::move][vick::move::start_buffer]") {
    contents contents({"    assert"});
    contents.yx(0, 5);

    start_buffer(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
}

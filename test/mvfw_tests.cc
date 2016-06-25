/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("mvfw", "[mvfw]") {
    contents contents({" a bunch of random text to test it"});

    forward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);

    forward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);
}

/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("mvfeow", "[mvfeow]") {
    contents contents({" a bunch of random text to test it"});

    forward_end_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 2);

    forward_end_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 8);

    // space before 'it'
    contents.x = contents.cont[0].size() - 4;

    forward_end_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == contents.cont[0].size());
}

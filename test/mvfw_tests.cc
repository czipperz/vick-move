/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvfw;

TEST_CASE("mvfw", "[mvfw]") {
    contents contents;
    contents.push_back(" a bunch of random text to test it");

    initscr();
    mvfw(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);

    mvfw(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);
    endwin();
}

/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::backward_begin_wword",
          "[vick::move][vick::move::backward_begin_wword]") {
    contents contents({" a bunch of random text to test it"});
    contents.x = contents.cont[0].size();

    // |it
    backward_begin_wword(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 32);

    // |test
    backward_begin_wword(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 27);

    // b|unch
    contents.x = 4;

    // |bunch
    backward_begin_wword(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);

    // |a bun
    backward_begin_wword(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);

}

TEST_CASE("vick::move::backward_begin_wword 2",
          "[vick::move][vick::move::backward_begin_wword]") {
    contents contents({" {-# LANGUAGE CPP #-}"});
    // |LANG
    contents.yx(0, 5);

    // sob
    backward_begin_wword(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);
}

TEST_CASE("vick::move::backward_begin_wword 3",
          "[vick::move][vick::move::backward_begin_wword]") {
    contents contents({"  {-# LANGUAGE CPP #-}"});
    // |LANG
    contents.yx(0, 6);

    // sob
    backward_begin_wword(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 2);
}

TEST_CASE("vick::move::backward_begin_wword 4",
          "[vick::move][vick::move::backward_begin_wword]") {
    contents contents({"{-# LANGUAGE CPP #-}"});
    // |LANG
    contents.yx(0, 4);

    // sob
    backward_begin_wword(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
}

TEST_CASE("vick::move::backward_begin_wword over lines",
          "[vick::move][vick::move::backward_begin_wword]") {
    contents contents(
        {"", "", "#endif", "", "import Development.Shake"});
    // Dev|e
    contents.yx(4, 10);

    // |Deve
    backward_begin_wword(contents);
    CHECK(contents.y == 4);
    CHECK(contents.x == 7);

    // |import
    backward_begin_wword(contents);
    CHECK(contents.y == 4);
    CHECK(contents.x == 0);

    // |#endif
    backward_begin_wword(contents);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);

    // sob
    backward_begin_wword(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
}

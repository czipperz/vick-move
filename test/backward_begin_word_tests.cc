/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::backward_begin_word",
          "[vick::move][vick::move::backward_begin_word]") {
    contents contents({" a bunch of random text to test it"});
    contents.x = contents.cont[0].size();

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 32);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 27);

    contents.x = 4;

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);

}

TEST_CASE("vick::move::backward_begin_word 2",
          "[vick::move][vick::move::backward_begin_word]") {
    contents contents({" {-# LANGUAGE CPP #-}"});
    // L
    contents.yx(0, 5);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);
}

TEST_CASE("vick::move::backward_begin_word 3",
          "[vick::move][vick::move::backward_begin_word]") {
    contents contents({"  {-# LANGUAGE CPP #-}"});
    // L
    contents.yx(0, 6);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 2);
}

TEST_CASE("vick::move::backward_begin_word 4",
          "[vick::move][vick::move::backward_begin_word]") {
    contents contents({"{-# LANGUAGE CPP #-}"});
    // L
    contents.yx(0, 4);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
}

TEST_CASE("vick::move::backward_begin_word over lines",
          "[vick::move][vick::move::backward_begin_word]") {
    contents contents(
        {"", "", "#endif", "", "import Development.Shake"});
    // Dev|e
    contents.yx(4, 10);

    // |Deve
    backward_begin_word(contents);
    CHECK(contents.y == 4);
    CHECK(contents.x == 7);

    backward_begin_word(contents);
    CHECK(contents.y == 4);
    CHECK(contents.x == 0);

    // #|endif
    backward_begin_word(contents);
    CHECK(contents.y == 2);
    CHECK(contents.x == 1);

    backward_begin_word(contents);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);

    backward_begin_word(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
}

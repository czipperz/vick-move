#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::backward_end_word 1",
          "[vick::move][vick::move::backward_end_word]") {
    contents c({"word", "", "", " ", "", " asdf"});
    c.y = 6;
    visual_setup _;

    backward_end_word(c);
    CHECK(c.y == 5);
    CHECK(c.x == 5);

    backward_end_word(c);
    CHECK(c.y == 0);
    CHECK(c.x == 4);

    backward_end_word(c);
    CHECK(c.y == 0);
    CHECK(c.x == 0);
}

TEST_CASE("vick::move::backward_end_word 2",
          "[vick::move][vick::move::backward_end_word]") {
    contents c({"  word   ", "", "", " ", "", " asdf   "});
    c.y = 6;
    visual_setup _;

    backward_end_word(c);
    CHECK(c.y == 5);
    CHECK(c.x == 5);

    backward_end_word(c);
    CHECK(c.y == 0);
    CHECK(c.x == 6);

    backward_end_word(c);
    CHECK(c.y == 0);
    CHECK(c.x == 0);
}

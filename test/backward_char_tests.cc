#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using namespace vick::move;

TEST_CASE("vick::move::backward_char 2",
          "[vick::move][vick::move::backward_char]") {
    contents c({"asdf"});
    c.y = 1;
    visual_setup _;

    backward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 4);

    backward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 3);

    backward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 2);

    backward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 1);

    backward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 0);

    backward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 0);
}

TEST_CASE("vick::move::backward_char 1",
          "[vick::move][vick::move::backward_char]") {
    contents c;

    REQUIRE(c.cont.size() == 1);
    REQUIRE(c.cont[0].size() == 0);

    visual_setup _;
    backward_char(c);
    CHECK(c.y == 0);
    CHECK(c.x == 0);
}

TEST_CASE("vick::move::backward_char over lines",
          "[vick::move][vick::move::backward_char]") {
    contents contents({"assert", "back"});
    contents.yx(1, 0);

    backward_char(contents, 2);
    CHECK(contents.y == 0);
    CHECK(contents.x == contents.cont[0].size() - 1);
    CHECK(contents.x == 5);

    contents.cont.insert(contents.cont.begin() + 1, "");
    contents.yx(2, 0);

    backward_char(contents);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);
    CHECK(contents.x == contents.cont[contents.y].size());

    backward_char(contents);
    CHECK(contents.y == 0);
    CHECK(contents.x == 6);
    CHECK(contents.x == contents.cont[contents.y].size());
}


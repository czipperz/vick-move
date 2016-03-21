#include <ncurses.h>

#include "../src/move.hh"
#include "../../../test/catch.hpp"

using namespace vick;
using vick::move::mveol;

TEST_CASE("mveol", "[mveol]") {
    contents contents;
    contents.push_back("Aesop");

    initscr();
    mveol(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 4);
    endwin();
}

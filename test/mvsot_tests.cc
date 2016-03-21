#include <ncurses.h>

#include "../src/move.hh"
#include "../../../test/catch.hpp"

using namespace vick;
using vick::move::mvsot;

TEST_CASE("mvsot", "[mvsot]") {
    contents contents;
    contents.push_back("    hello");

    initscr();
    mvsot(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 4);
    endwin();
}

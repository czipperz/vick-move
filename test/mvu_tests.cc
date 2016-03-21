#include <ncurses.h>

#include "../src/move.hh"
#include "../../../test/catch.hpp"

using namespace vick;
using vick::move::mvu;

TEST_CASE("mvu", "[mvu]") {
    contents contents(1, 6);
    contents.push_back("hi");
    contents.push_back("Alabama");

    initscr();
    mvu(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 1);
    CHECK(contents.waiting_for_desired);
    CHECK(contents.desired_x == 6);
    endwin();
}

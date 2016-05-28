/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include <ncurses.h>

#include "../lib.hh"
#include "catch.hpp"

using namespace vick;
using vick::move::mvf;

TEST_CASE("mvf", "[mvf]") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("hello");

    initscr();
    mvf(contents, 3);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);

    mvf(contents, 4);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
    endwin();
}

TEST_CASE("mvf_2", "[mvf]") {
    contents contents;
    contents.push_back("CFLAGS=-lncurses -Wall");
    contents.push_back("O=out");
    contents.push_back("S=src");
    contents.push_back("T=test");
    contents.push_back("TO=testout");
    contents.push_back("CC=g++");

    contents.y = 0;
    contents.x = 21;

    initscr();
    mvf(contents, 2);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
    endwin();
}

TEST_CASE("mvf_over_empty_lines", "[mvf]") {
    contents contents(0, 1);
    contents.push_back("hi");
    contents.push_back("");
    contents.push_back("hi");

    initscr();
    mvf(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);
    endwin();
}

TEST_CASE("mvf_over_tabs", "[mvf]") {
    contents contents(0, 25);
    contents.push_back("testVI: ${files} $O/main.o");
    contents.push_back("\t${CC} -o testVI $^ $(CFLAGS)");

    initscr();
    mvf(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);

    mvf(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
    endwin();
}

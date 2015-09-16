#include <iostream>
#include <ncurses.h>
#include <boost/optional.hpp>

#include "move.hh"
#include "configuration.hh"
#include "visual.hh"
#include "catch.hpp"

TEST_CASE("mvline") {
    contents contents;
    contents.x = 1; // make sure set x to 0
    contents.push_back("hi");
    contents.push_back("bye");
    contents.push_back("aseuior");
    contents.push_back("etc");

    initscr();
    mvline(contents, 1); // 1 = "bye"
    int y1 = contents.y, // 1
        x1 = contents.x; // 1

    mvline(contents, -1); // -1 should go to 0
    int y2 = contents.y; // 0

    mvline(contents, 4); // 4 > len, go to 3
    int y3 = contents.y; // 3
    endwin();

    REQUIRE(x1 == 0);
    REQUIRE(y1 == 1);
    REQUIRE(y2 == 0);
    REQUIRE(y3 == 3);
}

TEST_CASE("mv") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("blah");
    contents.push_back("hi");
    contents.push_back("nop");

    initscr();
    mv(contents, 1, 4); // past end
    int y1 = contents.y,
        x1 = contents.x;

    mv(contents, 2, 0);
    int y2 = contents.y,
        x2 = contents.x;

    mv(contents, 6, 2);
    int y3 = contents.y,
        x3 = contents.x;
    endwin();

    REQUIRE(y1 == 1);
    REQUIRE(x1 == 3);
    REQUIRE(y2 == 2);
    REQUIRE(x2 == 0);
    REQUIRE(y3 == 3);
    REQUIRE(x3 == 2);
}

TEST_CASE("mvcol") {
    contents contents;
    contents.push_back("asert");

    initscr();
    mvcol(contents, 3);
    int y1 = contents.y,
        x1 = contents.x;

    mvcol(contents, 10); //doesn't do anything
    int y2 = contents.y,
        x2 = contents.x;

    mvcol(contents, 0);
    int y3 = contents.y,
        x3 = contents.x;
    endwin();

    REQUIRE(0 == y1);
    REQUIRE(0 == y2);
    REQUIRE(0 == y3);
    REQUIRE(3 == x1);
    REQUIRE(3 == x2);
    REQUIRE(0 == x3);
}

TEST_CASE("mvsot") {
    contents contents;
    contents.push_back("    hello");

    initscr();
    mvsot(contents, boost::none);
    endwin();

    REQUIRE(0 == contents.y);
    REQUIRE(4 == contents.x);
}

TEST_CASE("mveol") {
    contents contents;
    contents.push_back("Aesop");

    initscr();
    mveol(contents, boost::none);
    int y = contents.y,
        x = contents.x;
    endwin();

    REQUIRE(4 == x);
    REQUIRE(0 == y);
}

TEST_CASE("mvsol") {
    contents contents (0,5);
    contents.push_back("    assert");

    initscr();
    mvsol(contents, boost::none);
    int y = contents.y,
        x = contents.x;
    endwin();

    REQUIRE(0 == y);
    REQUIRE(0 == x);
}

TEST_CASE("mvd") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("hello");
    contents.push_back("aseuirpo");

    initscr();
    mvd(contents,2);
    int y = contents.y,
        x = contents.x;
    mvd(contents, boost::none);
    int y1 = contents.y,
        x1 = contents.x;
    endwin();

    REQUIRE(0 == x);
    REQUIRE(0 == x1);
    REQUIRE(2 == y);
    REQUIRE(2 == y1);
}

TEST_CASE("mvd_2") {
    contents contents;
    contents.push_back("CFLAGS=-lncurses -Wall");
    contents.push_back("O=out");
    contents.push_back("S=src");
    contents.push_back("T=test");

    initscr();
    mveol(contents, boost::none);
    int y = contents.y,
        x = contents.x;
    mvd(contents, boost::none);
    int y1 = contents.y,
        x1 = contents.x;
    int d1 = contents.desired_x;
    bool w1 = contents.waiting_for_desired;
    mvd(contents, boost::none);
    int y2 = contents.y,
        x2 = contents.x;
    int d2 = contents.desired_x;
    bool w2 = contents.waiting_for_desired;
    endwin();

    REQUIRE(0 == y);
    REQUIRE(21 == x);

    REQUIRE(1 == y1);
    REQUIRE(4 == x1);
    REQUIRE(21 == d1);
    REQUIRE(true == w1);

    REQUIRE(2 == y2);
    REQUIRE(4 == x2);
    REQUIRE(21 == d2);
    REQUIRE(true == w2);
}

TEST_CASE("mvu") {
    contents contents (1,6);
    contents.push_back("hi");
    contents.push_back("Alabama");

    initscr();
    mvu(contents, boost::none);
    int y1 = contents.y,
        x1 = contents.x;
    endwin();

    REQUIRE(0 == y1);
    REQUIRE(1 == x1);
    REQUIRE(true == contents.waiting_for_desired);
    REQUIRE(6 == contents.desired_x);
}

TEST_CASE("mvf") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("hello");

    initscr();
    mvf(contents,3);
    int y = contents.y,
        x = contents.x;
    mvf(contents,4);
    int y1 = contents.y,
        x1 = contents.x;
    endwin();

    REQUIRE(0 == y);
    REQUIRE(3 == x);
    REQUIRE(1 == y1);
    REQUIRE(1 == x1);
}

TEST_CASE("mvf_2") {
    contents contents;
    contents.push_back("CFLAGS=-lncurses -Wall");
    contents.push_back("O=out");
    contents.push_back("S=src");
    contents.push_back("T=test");
    contents.push_back("TO=testout");
    contents.push_back("CC=g++");

    initscr();
    mveol(contents, boost::none);
    int y = contents.y,
        x = contents.x;
    mvf(contents,2);
    int y1 = contents.y,
        x1 = contents.x;
    endwin();

    REQUIRE(0 == y);
    REQUIRE(21 == x);
    REQUIRE(1 == y1);
    REQUIRE(1 == x1);
}

TEST_CASE("mvf_over_empty_lines") {
    contents contents (0,1);
    contents.push_back("hi");
    contents.push_back("");
    contents.push_back("hi");

    initscr();
    mvf(contents, boost::none);
    endwin();

    REQUIRE(0 == contents.x);
    REQUIRE(1 == contents.y);
}

TEST_CASE("mvf_over_tabs") {
    contents contents (0,25);
    contents.push_back("testVI: ${files} $O/main.o");
    contents.push_back("\t${CC} -o testVI $^ $(CFLAGS)");

    initscr();
    mvf(contents, boost::none);
    int y,x;
    y = contents.y;
    x = contents.x;
    mvf(contents, boost::none);
    int y1,x1;
    y1= contents.y;
    x1= contents.x;
    endwin();

    REQUIRE(1 == y);
    REQUIRE(0 == x);
    REQUIRE(1 == y1);
    REQUIRE(1 == x1);
}

TEST_CASE("mvb") {
    contents contents (1,0);
    contents.push_back("assert");
    contents.push_back("back");

    initscr();
    mvb(contents,2);
    int y = contents.y,
        x = contents.x;
    endwin();

    REQUIRE(0 == y);
    REQUIRE(4 == x);
}


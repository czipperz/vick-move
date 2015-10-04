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
    mvline(contents, 1);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);

    mvline(contents, -1);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);

    mvline(contents, 4);
    CHECK(contents.y == 3);
    CHECK(contents.x == 0);
    endwin();
}

TEST_CASE("mv") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("blah");
    contents.push_back("hi");
    contents.push_back("nop");

    initscr();
    mv(contents, 1, 4); // past end
    CHECK(contents.y == 1);
    CHECK(contents.x == 3);

    mv(contents, 2, 0);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);

    mv(contents, 6, 2);
    CHECK(contents.y == 3);
    CHECK(contents.x == 2);
    endwin();
}

TEST_CASE("mvcol") {
    contents contents;
    contents.push_back("asert");

    initscr();
    mvcol(contents, 3);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);

    mvcol(contents, 10); //doesn't do anything
    CHECK(contents.y == 0);
    CHECK(contents.y == 0);

    mvcol(contents, 0);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
    endwin();
}

TEST_CASE("mvsot") {
    contents contents;
    contents.push_back("    hello");

    initscr();
    mvsot(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 4);
    endwin();
}

TEST_CASE("mveol") {
    contents contents;
    contents.push_back("Aesop");

    initscr();
    mveol(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 4);
    endwin();
}

TEST_CASE("mvsol") {
    contents contents (0,5);
    contents.push_back("    assert");

    initscr();
    mvsol(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 0);
    endwin();
}

TEST_CASE("mvd") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("hello");
    contents.push_back("aseuirpo");

    initscr();
    mvd(contents,2);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);

    mvd(contents, boost::none);
    CHECK(contents.y == 2);
    CHECK(contents.x == 0);
    endwin();
}

TEST_CASE("mvd_2") {
    contents contents;
    contents.push_back("CFLAGS=-lncurses -Wall");
    contents.push_back("O=out");
    contents.push_back("S=src");
    contents.push_back("T=test");

    initscr();
    mveol(contents, boost::none);
    CHECK(contents.y == 0);
    CHECK(contents.x == 21);

    mvd(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 4);
    CHECK(contents.desired_x == 21);
    CHECK(contents.waiting_for_desired);

    mvd(contents, boost::none);
    CHECK(contents.y == 2);
    CHECK(contents.x == 4);
    CHECK(contents.desired_x == 21);
    CHECK(contents.waiting_for_desired);
    endwin();
}

TEST_CASE("mvu") {
    contents contents (1,6);
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

TEST_CASE("mvf") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("hello");

    initscr();
    mvf(contents,3);
    CHECK(contents.y == 0);
    CHECK(contents.x == 3);

    mvf(contents,4);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
    endwin();
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
    CHECK(contents.y == 0);
    CHECK(contents.x == 21);

    mvf(contents,2);
    CHECK(contents.y == 1);
    CHECK(contents.x == 1);
    endwin();
}

TEST_CASE("mvf_over_empty_lines") {
    contents contents (0,1);
    contents.push_back("hi");
    contents.push_back("");
    contents.push_back("hi");

    initscr();
    mvf(contents, boost::none);
    CHECK(contents.y == 1);
    CHECK(contents.x == 0);
    endwin();
}

TEST_CASE("mvf_over_tabs") {
    contents contents (0,25);
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

TEST_CASE("mvb") {
    contents contents (1,0);
    contents.push_back("assert");
    contents.push_back("back");

    initscr();
    mvb(contents,2);
    CHECK(contents.y == 0);
    CHECK(contents.x == 4);
    endwin();

}


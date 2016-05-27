/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "configuration.hh"
#include "contents.hh"
#include "move.hh"
#include "show_message.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
mvmatch(contents& contents, boost::optional<int>) {
    if (MATCHES.size() % 2 != 0) {
        show_message(
            "MATCHES variable doesn't have an even number of "
            "elements, don't know how to make matches");
        return boost::none;
    }

    auto y = contents.y;
    size_t x_fin =
        contents.cont[y].find_first_of(MATCHES, contents.x);

    while (x_fin == std::string::npos) {
        if (++y >= contents.cont.size()) {
            show_message("Can't find any matches in string");
            return boost::none;
        }
        x_fin = contents.cont[y].find_first_of(MATCHES);
    }

    size_t index_match =
        MATCHES.find_first_of(contents.cont[y][x_fin]);
    bool forward = index_match % 2 == 0;
    char match = MATCHES[index_match + (forward ? 1 : -1)];
    char skipme = MATCHES[index_match];
    std::string both{match, skipme, '\0'};

    size_t x_beg = x_fin;
    int numskipped = 0;
#define dasif                                                        \
    if (contents.cont[y][x_beg] == skipme) {                         \
        numskipped++;                                                \
    } else if (numskipped) {                                         \
        numskipped--;                                                \
    } else {                                                         \
        goto set;                                                    \
    }
#define testnumskipped(expr, direction, check0)                      \
    while (x_beg != std::string::npos and                            \
           (not check0 or x_beg != 0)) {                             \
        dasif;                                                       \
        x_beg = contents.cont[y].find_##direction##_of(both,         \
                                                       x_beg expr);  \
    }                                                                \
    if (check0 and x_beg == 0) {                                     \
        dasif;                                                       \
    }
#define testforward testnumskipped(+1, first, false)
#define testbackward testnumskipped(-1, last, true)

    if (forward) {
        x_beg = contents.cont[y].find_first_of(both, x_beg + 1);
        testforward;

        while (x_beg == std::string::npos) {
            if (++y >= contents.cont.size()) {
                show_message(
                    std::string(
                        "Can't find any matches in string for ") +
                    match);
                return boost::none;
            }
            x_beg = contents.cont[y].find_first_of(both);
            testforward;
        }
    } else {
        x_beg = contents.cont[y].find_last_of(both, x_beg - 1);
        testbackward;

        while (x_beg == std::string::npos or x_beg == 0) {
            if (y == 0) {
                show_message(
                    std::string(
                        "Can't find corresponding match for ") +
                    match);
                return boost::none;
            }
            x_beg = contents.cont[--y].find_last_of(both);
            testbackward;
        }
    }

set:
    contents.y = y;
    contents.x = x_beg;

    return boost::none;
}
}
}

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../lib.hh"
#include "move_word_p.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
mvfeow(contents& contents, boost::optional<int> op) {
    if (op and op.get() < 0)
        return mvbw(contents, -op.get());
    int num = op ? op.get() : 1;
    if (num == 0)
        return boost::none;
// move at least one forward
// move over whitespace
// if delimitor then move until not delimitor
// else move until delimitor or whitespace
// move back one
#define boundsCheck                                                  \
    if ((contents.y >= contents.cont.size()) or                      \
        (contents.y == contents.cont.size() - 1 and                  \
         contents.x >= contents.cont[contents.y].size()) or          \
        (contents.x == 0 and not isWhitespace(ch) and                \
         contents.cont[contents.y].size() != 0)) {                   \
        mvb(contents);                                               \
        return boost::none;                                          \
    }
#define ch contents.cont[contents.y][contents.x]
    mvf(contents);
    while (isWhitespace(ch)) {
        mvf(contents);
        boundsCheck;
    }
    if (isDeliminator(ch)) {
        do {
            mvf(contents);
            boundsCheck;
        } while (isDeliminator(ch));
        mvb(contents);
    } else {
        do {
            mvf(contents);
            boundsCheck;
        } while (not isDeliminator(ch) and not isWhitespace(ch));
        mvb(contents);
    }
    if (num > 1)
        mvfeow(contents, num - 1);
    return boost::none;
#undef boundsCheck
#undef ch
}
}
}

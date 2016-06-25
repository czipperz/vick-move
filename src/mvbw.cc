/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../lib.hh"
#include "move_word_p.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
backward_begin_word(contents& contents, boost::optional<int> op) {
    if (op and op.get() < 0)
        return forward_begin_word(contents, -op.get());
    const int num = op ? op.get() : 1;
    if (num == 0)
        return boost::none;
// move back one then
// if delimitor then move back until no delimitor
// else if whitespace then move back until not whitespace then
//   move back consistently over delimitors or word chars
// else /*word char*/ move back until not word char or
//   whitespace
// move forward one
#define boundsCheck                                                  \
    if (contents.x == 0 and                                          \
        (contents.y == 0 or                                          \
         not contents.cont[contents.y].empty()) and                  \
        (contents.y == 0 or not isWhitespace(ch) or                  \
         contents.cont[contents.y].empty())) {                       \
        if (contents.x == contents.cont[contents.y].size() - 1)      \
            forward_char(contents);                                  \
        return boost::none;                                          \
    }
#define ch contents.cont[contents.y][contents.x]
    if (contents.y == 0 and contents.x == 0)
        return boost::none;
    backward_char(contents);
    while (contents.cont[contents.y].empty() or isWhitespace(ch)) {
        boundsCheck;
        backward_char(contents);
    }
    if (isDeliminator(ch)) {
        while (isDeliminator(ch)) {
            boundsCheck;
            backward_char(contents);
        }
        forward_begin_word(contents);
    } else if (contents.x == 0 and
               not contents.cont[contents.y].empty()) {
        return boost::none;
    } else {
        while (not(isDeliminator(ch) or isWhitespace(ch))) {
            boundsCheck;
            backward_char(contents);
        }
        forward_begin_word(contents);
    }
    if (num > 1)
        backward_begin_word(contents, num - 1);
    return boost::none;
#undef boundsCheck
#undef ch
}
}
}

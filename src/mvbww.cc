/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../lib.hh"
#include "move_word_p.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
backward_begin_wword(contents& contents, boost::optional<int> op) {
    if (op and op.get() < 0)
        return forward_begin_wword(contents, -op.get());
    int num = op ? op.get() : 1;
    if (num == 0 or num == -0)
        return boost::none;
#define boundsCheck                                                  \
    if ((static_cast<move_ts>(contents.y) < 0) or                    \
        (contents.y == 0 and contents.x <= 0) or                     \
        (contents.x == 0 and not isWhitespace(ch))) {                \
        if (contents.x == contents.cont[contents.y].size() - 1)      \
            forward_char(contents);                                  \
        return boost::none;                                          \
    }
#define ch contents.cont[contents.y][contents.x]
    backward_char(contents);
    while (isWhitespace(ch)) {
        backward_char(contents);
        boundsCheck;
    }
    do {
        backward_char(contents);
        boundsCheck;
    } while (not isWhitespace(ch));
    forward_char(contents);
    return boost::none;
#undef boundsCheck
#undef ch
}
}
}

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../lib.hh"
#include "move_word_p.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
forward_end_wword(contents& contents, boost::optional<int> op) {
    if (op and op.get() < 0)
        // end
        return backward_begin_wword(contents, -op.get());
    int num = op ? op.get() : 1;
    if (num == 0)
        return boost::none;
#define boundsCheck                                                  \
    if ((contents.y >= contents.cont.size()) or                      \
        (contents.y == contents.cont.size() - 1 and                  \
         contents.x >= contents.cont[contents.y].size()) or          \
        (contents.cont[contents.y].size() and contents.x == 0 and    \
         not isWhitespace(ch))) {                                    \
        backward_char(contents);                                     \
        return boost::none;                                          \
    }
#define ch contents.cont[contents.y][contents.x]
    forward_char(contents);
    while (isWhitespace(ch)) {
        forward_char(contents);
        boundsCheck;
    }
    do {
        forward_char(contents);
        boundsCheck;
    } while (not isWhitespace(ch));
    backward_char(contents);
    return boost::none;
#undef boundsCheck
#undef ch
}
}
}

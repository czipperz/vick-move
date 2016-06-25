/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../lib.hh"
#include "move_word_p.hh"

namespace vick {
namespace move {

// boost::optional<std::shared_ptr<change> >
// forward_end_word(contents& contents, boost::optional<int> op) {
//     if (op and op.get() < 0)
//         return backward_begin_word(contents, -op.get());
//     int num = op ? op.get() : 1;
//     if (num == 0)
//         return boost::none;
// // move at least one forward
// // move over whitespace
// // if delimitor then move until not delimitor
// // else move until delimitor or whitespace
// // move back one
// #define boundsCheck                                                  \
//     if ((contents.y >= contents.cont.size()) or                      \
//         (contents.y == contents.cont.size() - 1 and                  \
//          contents.x >= contents.cont[contents.y].size()) or          \
//         (contents.x == 0 and not isWhitespace(ch) and                \
//          contents.cont[contents.y].size() != 0)) {                   \
//         backward_char(contents);                                     \
//         return boost::none;                                          \
//     }
// #define ch contents.cont[contents.y][contents.x]
//     forward_char(contents);
//     while (isWhitespace(ch)) {
//         forward_char(contents);
//         boundsCheck;
//     }
//     if (isDeliminator(ch)) {
//         do {
//             forward_char(contents);
//             boundsCheck;
//         } while (isDeliminator(ch));
//         backward_char(contents);
//     } else {
//         do {
//             forward_char(contents);
//             boundsCheck;
//         } while (not isDeliminator(ch) and not isWhitespace(ch));
//         backward_char(contents);
//     }
//     if (num > 1)
//         forward_end_word(contents, num - 1);
//     return boost::none;
// #undef boundsCheck
// #undef ch
// }
}
}

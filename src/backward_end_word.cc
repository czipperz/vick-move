/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../lib.hh"
#include "vick-predicates/lib.hh"

namespace vick {
namespace move {

std::shared_ptr<change>
backward_end_word(contents& contents, boost::optional<int> op) {
    if (op and op.get() < 0)
        return forward_end_word(contents, -op.get());
    int num;
    if (op) {
        num = *op;
        if (num == 0) {
            return nullptr;
        }
    } else {
        num = 1;
    }

    contents.waiting_for_desired = false;

    // go backwards until reach different type, then go forward one
    for (; num != 0; --num) {
        backward_char(contents);

        if (predicates::end_of_line(contents) or
            predicates::at_whitespace(contents)) {
            // below
        } else if (predicates::at_deliminator(contents)) {
            while (not predicates::start_of_buffer(contents) and
                   (predicates::end_of_line(contents) or
                    predicates::at_deliminator(contents))) {
                backward_char(contents);
            }
        } else {
            while (not predicates::start_of_buffer(contents) and
                   (predicates::end_of_line(contents) or
                    predicates::at_regular(contents))) {
                backward_char(contents);
            }
        }

        while (not predicates::start_of_buffer(contents) and
                (predicates::end_of_line(contents) or
                predicates::at_whitespace(contents))) {
            backward_char(contents);
        }
    }

    // go past end of word unless at start of buffer
    if (not predicates::start_of_buffer(contents)) {
        forward_char(contents);
    }

    return nullptr;
}

}
}

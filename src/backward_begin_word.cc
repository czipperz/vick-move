/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../lib.hh"
#include "vick-predicates/lib.hh"

namespace vick {
namespace move {

std::shared_ptr<change>
backward_begin_word(contents& contents, boost::optional<int> op) {
    if (op and op.get() < 0)
        return forward_begin_word(contents, -op.get());
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

    for (; num != 0; --num) {
        backward_char(contents);

        // go to end of previous word
        while (not predicates::start_of_buffer(contents) and
               (predicates::end_of_line(contents) or
                predicates::at_whitespace(contents))) {
            backward_char(contents);
        }

        // until current type runs out, move forward
        if (predicates::at_deliminator(contents)) {
            do {
                backward_char(contents);
            } while (not predicates::start_of_line(contents) and
                     predicates::at_deliminator(contents));
            if (not predicates::at_deliminator(contents)) {
                forward_char(contents);
            }
        } else {
            do {
                backward_char(contents);
            } while (not predicates::start_of_line(contents) and
                     predicates::at_regular(contents));
            if (not predicates::at_regular(contents)) {
                forward_char(contents);
            }
        }
    }

    return nullptr;
}
}
}

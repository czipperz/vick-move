/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../lib.hh"
#include "vick-predicates/lib.hh"

namespace vick {
namespace move {

std::shared_ptr<change>
forward_begin_wword(contents& contents, boost::optional<int> op) {
    if (op and op.get() < 0)
        return backward_begin_wword(contents, -op.get());
    int num = op ? op.get() : 1;

    for (; num != 0; --num) {
        while (not predicates::end_of_line(contents) and
               not predicates::at_whitespace(contents)) {
            forward_char(contents);
        }
        while (not predicates::end_of_buffer(contents) and
               (predicates::end_of_line(contents) or
                predicates::at_whitespace(contents))) {
            forward_char(contents);
        }
    }

    return nullptr;
}
}
}

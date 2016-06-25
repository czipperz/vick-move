/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <boost/optional.hpp>

#include "../lib.hh"
#include "contents.hh"
#include "show_message.hh"
#include "visual.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
forward_line(contents& contents, boost::optional<int> op) {
    int times = op ? op.get() : 1;
    if (times < 0 ? contents.y < static_cast<move_t>(-times)
                  : contents.y + static_cast<move_t>(times) >=
                        contents.cont.size()) {
        show_message(
            "Can't move to that location (start/end of buffer)");
        return boost::none;
    }

    visual_t old_visx = to_visual(contents.cont[contents.y], contents.x);
    contents.y += times;
    move_t new_x = from_visual(contents.cont[contents.y], old_visx);
    size_t len = contents.cont[contents.y].length();

    if (contents.waiting_for_desired) {
        contents.x = from_visual(contents.cont[contents.y],
                                 contents.desired_x);
        contents.waiting_for_desired = false;
    } else {
        contents.x = new_x;
    }
    if (contents.x > len) {
        contents.desired_x = to_visual(contents.cont[contents.y],
                                       contents.x);
        contents.waiting_for_desired = true;
        contents.x = len;
    }

    // if (contents.waiting_for_desired) {
    //     if (contents.x > len) {
    //         contents.x = len;
    //     } else if ((contents.desired_x > contents.x and
    //                 contents.desired_x < len) or
    //                contents.desired_x == 0) {
    //         // x  desired  len
    //         contents.x = contents.desired_x;
    //         contents.waiting_for_desired = false;
    //     } else {
    //         // x  len  desired
    //         contents.x = len - 1;
    //     }
    // } else if (len < contents.x and len > 0) {
    //     contents.waiting_for_desired = true;
    //     contents.desired_x = contents.x;
    //     contents.x = len;
    // } else {
    //     auto des = contents.x;
    //     contents.x = from_visual(contents.cont[contents.y], vis);
    //     if (len == 0) {
    //         contents.waiting_for_desired = true;
    //         contents.desired_x = des;
    //     }
    // }
    // contents.x =
    //     static_cast<move_ts>(contents.x) >= 0 ? contents.x : 0;
    return boost::none;
}
}
}

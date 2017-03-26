/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <boost/optional.hpp>

#include "../lib.hh"
#include "contents.hh"
#include "visual.hh"

namespace vick {
namespace move {

std::shared_ptr<change>
yx(contents& contents, move_t y, move_t x) {
    if (y >= contents.cont.size()) {
        y = contents.cont.size() - 1;
    }
    if (x > contents.cont[y].size()) {
        contents.waiting_for_desired = true;
        contents.desired_x = to_visual(contents.cont[contents.y], x);
        x = contents.cont[y].size();
    } else {
        contents.waiting_for_desired = false;
    }
    contents.y = y;
    contents.x = x;
    return nullptr;
}
}
}

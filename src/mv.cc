/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <boost/optional.hpp>

#include "contents.hh"
#include "../lib.hh"

namespace vick {
namespace move {

void mv(contents& contents, move_t y, move_t x) {
    if (y >= contents.cont.size())
        y = contents.cont.size() - 1;
    if (x >= contents.cont[y].size())
        x = contents.cont[y].size() - 1;
    contents.y = y;
    contents.x = x;
}
}
}

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <boost/optional.hpp>

#include "../lib.hh"
#include "contents.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
start_text(contents& contents, boost::optional<int>) {
    contents.waiting_for_desired = false;
    contents.x = 0;
    for (auto c : contents.cont[contents.y]) {
        if (std::isblank(c)) {
            contents.x++;
        } else {
            break;
        }
    }
    return boost::none;
}
}
}

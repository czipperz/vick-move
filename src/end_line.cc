/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <boost/optional.hpp>

#include "../lib.hh"
#include "contents.hh"
#include "prompt.hh"
#include "show_message.hh"

namespace vick {
namespace move {

std::shared_ptr<change>
end_line(contents& contents, boost::optional<int>) {
    if (contents.cont.empty()) {
        return column(contents, 0);
    } else {
        return column(contents, contents.cont[contents.y].size());
    }
}
}
}

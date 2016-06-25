/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <boost/optional.hpp>

#include "../lib.hh"
#include "contents.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
end_buffer(contents& contents, boost::optional<int>) {
    if (contents.cont.empty()) {
        return yx(contents, 0, 0);
    } else {
        return yx(contents, contents.cont.size() - 1,
                  contents.cont.back().size());
    }
}
}
}

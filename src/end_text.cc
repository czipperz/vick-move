/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../lib.hh"
#include "vick-predicates/lib.hh"

namespace vick {
namespace move {

std::shared_ptr<change>
end_text(contents& contents, boost::optional<int>) {
    contents.waiting_for_desired = false;
    contents.x = contents.cont[contents.y].size();
    for (auto i = contents.cont[contents.y].rbegin(),
              rend = contents.cont[contents.y].rend();
         i != rend; ++i) {
        if (predicates::is_whitespace(*i)) {
            --contents.x;
        } else {
            break;
        }
    }
    return nullptr;
}
}
}

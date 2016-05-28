/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <boost/optional.hpp>

#include "contents.hh"
#include "prompt.hh"
#include "show_message.hh"
#include "../lib.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
mvcol(contents& contents, boost::optional<int> col) {
    if (col) {
        size_t len = contents.cont[contents.y].length();
        if (len >= static_cast<decltype(len)>(col.get())) {
            contents.x = col.get();
            contents.waiting_for_desired = false;
        } else {
            show_message(std::string("Can't move to column: ") +
                         std::to_string(col.get()));
        }
    } else {
        boost::optional<std::string> str = prompt("Goto column: ");
        while (true) {
            if (not str)
                return boost::none;
            try {
                return mvcol(contents, std::stoi(*str));
            } catch (const std::invalid_argument&) {
            }
            str = prompt("Goto column (last answer not an int): ");
        }
    }
    return boost::none;
}
}
}

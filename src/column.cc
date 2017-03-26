/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <boost/optional.hpp>

#include "../lib.hh"
#include "contents.hh"
#include "prompt.hh"
#include "show_message.hh"
#include "visual.hh"

namespace vick {
namespace move {

std::shared_ptr<change>
column(contents& contents, boost::optional<int> col) {
    if (col) {
        size_t len = contents.cont[contents.y].length();
        if (len >= static_cast<size_t>(col.get())) {
            contents.x = static_cast<move_t>(col.get());
            contents.waiting_for_desired = false;
        } else {
            contents.waiting_for_desired = true;
            contents.desired_x =
                to_visual(contents.cont[contents.y],
                          static_cast<move_t>(col.get()));
            show_message(std::string("Can't move to column: ") +
                         std::to_string(col.get()));
        }
    } else {
        boost::optional<std::string> str = prompt("Goto column: ");
        while (true) {
            if (not str) {
                return nullptr;
            }
            try {
                return column(contents, std::stoi(*str));
            } catch (const std::invalid_argument&) {
                str =
                    prompt("Goto column (last answer not an int): ");
            }
        }
    }
    return nullptr;
}
}
}

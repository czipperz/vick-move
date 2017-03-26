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
line(contents& contents, boost::optional<int> line) {
    if (line) {
        contents.x = 0;
        int cont = line.get();
        if (cont < 0) {
            show_message("Can't move to a negative line!");
            contents.y = 0;
            return nullptr;
        }
        contents.y = static_cast<move_t>(cont);
        if (static_cast<decltype(contents.cont.size())>(cont) >=
            contents.cont.size()) {
            contents.y = contents.cont.size() - 1;
            show_message("Can't move past end of buffer!");
        }
    } else {
        boost::optional<std::string> str = prompt("Goto line: ");
        while (true) {
            if (not str)
                return nullptr;
            try {
                return move::line(contents, std::stoi(*str));
            } catch (const std::invalid_argument&) {
            }
            str = prompt("Goto line (last answer not an int): ");
        }
    }
    return nullptr;
}
}
}

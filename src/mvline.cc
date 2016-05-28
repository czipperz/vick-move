/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <boost/optional.hpp>

#include "contents.hh"
#include "../lib.hh"
#include "prompt.hh"
#include "show_message.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
mvline(contents& contents, boost::optional<int> line) {
    if (line) {
        contents.x = 0;
        int cont = line.get();
        if (cont < 0) {
            show_message("Can't move to a negative line!");
            contents.y = 0;
            return boost::none;
        }
        contents.y = cont;
        if (static_cast<decltype(contents.cont.size())>(cont) >=
            contents.cont.size()) {
            contents.y = contents.cont.size() - 1;
            show_message("Can't move past end of buffer!");
        }
    } else {
        boost::optional<std::string> str = prompt("Goto line: ");
        while (true) {
            if (not str)
                return boost::none;
            try {
                return mvline(contents, std::stoi(*str));
            } catch (const std::invalid_argument&) {
            }
            str = prompt("Goto line (last answer not an int): ");
        }
    }
    return boost::none;
}

boost::optional<std::shared_ptr<change> >
mveol(contents& contents, boost::optional<int>) {
    if (contents.cont[contents.y].empty())
        contents.x = 0;
    else
        contents.x = contents.cont[contents.y].length() - 1;
    return boost::none;
}

boost::optional<std::shared_ptr<change> >
mvsol(contents& contents, boost::optional<int>) {
    return mvcol(contents, 0);
}

boost::optional<std::shared_ptr<change> >
mvsop(contents& contents, boost::optional<int>) {
    contents.y = 0;
    contents.x = 0;
    contents.waiting_for_desired = false;
    return boost::none;
}

boost::optional<std::shared_ptr<change> >
mveop(contents& contents, boost::optional<int>) {
    contents.y = contents.cont.size() - 1;
    contents.x = 0;
    contents.waiting_for_desired = false;
    return boost::none;
}
}
}

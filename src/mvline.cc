#include <boost/optional.hpp>

#include "move.hh"
#include "../../../src/contents.hh"
#include "../../../src/show_message.hh"
#include "../../../src/prompt.hh"

boost::optional< std::shared_ptr<change> > mvline(contents& contents, boost::optional<int> line) {
    if(line) {
        contents.x = 0;
        int cont = line.get();
        if(cont < 0) {
            show_message("Can't move to a negative line!");
            contents.y = 0;
            return boost::none;
        }
        contents.y = cont;
        if(static_cast<decltype(contents.cont.size())>(cont) >= contents.cont.size()) {
            contents.y = contents.cont.size() - 1;
            show_message("Can't move past end of buffer!");
        }
    } else {
        std::string str = prompt("Goto line: ");
        while(true) {
            try {
                return mvline(contents, std::stoi(str));
            } catch(const std::invalid_argument&) {}
            str = prompt("Goto line (last answer not an int): ");
        }
    }
    return boost::none;
}

boost::optional< std::shared_ptr<change> > mveol(contents& contents, boost::optional<int>) {
    return mvcol(contents,contents.cont[contents.y].length() - 1);
}
boost::optional< std::shared_ptr<change> > mvsol(contents& contents, boost::optional<int>) {
    return mvcol(contents,0);
}

boost::optional< std::shared_ptr<change> > mvsop(contents& contents, boost::optional<int>) {
    contents.y = 0;
    contents.x = 0;
    contents.waiting_for_desired = false;
    return boost::none;
}
boost::optional< std::shared_ptr<change> > mveop(contents& contents, boost::optional<int>) {
    contents.y = contents.cont.size() - 1;
    contents.x = 0;
    contents.waiting_for_desired = false;
    return boost::none;
}

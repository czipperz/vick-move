#include <boost/optional.hpp>

#include "move.hh"
#include "../../../src/contents.hh"
#include "../../../src/show_message.hh"
#include "../../../src/prompt.hh"

void mvline(contents& contents, boost::optional<int> line) {
    if(line) {
        contents.x = 0;
        int cont = line.get();
        if(cont < 0) {
            show_message("Can't move to a negative line!");
            contents.y = 0;
            return;
        }
        contents.y = cont;
        if(cont >= contents.cont.size()) {
            contents.y = contents.cont.size() - 1;
            show_message("Can't move past end of buffer!");
        }
    } else {
        while(true) {
            std::string str = prompt("Goto line: ");
            try {
                int res = std::stoi(str);
                mvline(contents, res);
                return;
            } catch(std::invalid_argument) {
                continue;
            }
        }
    }
}

void mveol(contents& contents, boost::optional<int>) {
    mvcol(contents,contents.cont[contents.y].length() - 1);
}
void mvsol(contents& contents, boost::optional<int>) {
    mvcol(contents,0);
}

void mvsop(contents& contents, boost::optional<int>) {
    contents.y = 0;
    contents.x = 0;
    contents.waiting_for_desired = false;
}
void mveop(contents& contents, boost::optional<int>) {
    contents.y = contents.cont.size() - 1;
    contents.x = 0;
    contents.waiting_for_desired = false;
}

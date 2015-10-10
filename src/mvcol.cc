#include <boost/optional.hpp>

#include "../../../src/contents.hh"
#include "../../../src/prompt.hh"
#include "../../../src/show_message.hh"

void mvcol(contents& contents, boost::optional<int> col) {
    if(col) {
        unsigned int len = contents.cont[contents.y].length();
        if(len >= col.get()) {
            contents.x = col.get();
            contents.waiting_for_desired = false;
        } else {
            show_message(std::string("Can't move to column: ")
                         + std::to_string(col.get()));
        }
    } else {
        while(true) {
            std::string str = prompt("Goto column: ");
            try {
                int res = std::stoi(str);
                mvcol(contents, res);
                return;
            } catch(std::invalid_argument) {
                continue;
            }
        }
    }
}

#include "../../../src/contents.hh"
#include "../../../src/configuration.hh"
#include "../../../src/show_message.hh"
#include "move.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> > mvmatch(contents& contents, boost::optional<int>) {
    if(MATCHES.size() % 2 != 0) {
        show_message("MATCHES variable doesn't have an even number of elements, don't know how to make matches");
        return boost::none;
    }

    auto y = contents.y;
    size_t x_fin = contents.cont[y].find_first_of(MATCHES, contents.x);

    while(x_fin == std::string::npos) {
        if(++y >= contents.cont.size()) {
            show_message("Can't find any matches in string");
            return boost::none;
        }
        x_fin = contents.cont[y].find_first_of(MATCHES);
    }

    size_t index_match = MATCHES.find_first_of(contents.cont[y][x_fin]);
    bool forward = index_match % 2 == 0;
    if(forward) index_match++;
    else index_match--;
    char match = MATCHES[index_match];

    size_t x_beg;

    if(forward) {
        x_beg = contents.cont[y].find_first_of(match, x_fin+1);

        while(x_beg == std::string::npos) {
            if(++y >= contents.cont.size()) {
                show_message(std::string("Can't find any matches in string for ") + match);
                return boost::none;
            }
            x_beg = contents.cont[y].find_first_of(MATCHES);
        }
    } else {
        x_beg = contents.cont[y].find_last_of(match, x_fin-1);

        while(x_beg == std::string::npos) {
            if(--y < contents.cont.size()) {
                show_message(std::string("Can't find corresponding match for ") + match);
                return boost::none;
            }
            x_beg = contents.cont[y].find_last_of(match);
        }
    }

    contents.y = y;
    contents.x = x_beg;

    return boost::none;
}

}
}

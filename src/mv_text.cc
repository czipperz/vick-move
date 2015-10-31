#include <boost/optional.hpp>

#include "move.hh"
#include "../../../src/contents.hh"

boost::optional< std::shared_ptr<change> > mvsot(contents& contents, boost::optional<int>) {
    contents.x = 0;
    for(auto x : contents.cont[contents.y]) {
        if(x == ' ' || x == '\t') contents.x++;
        else break;
    }
    return boost::none;
}

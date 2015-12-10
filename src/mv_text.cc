#include <boost/optional.hpp>

#include "move.hh"
#include "../../../src/contents.hh"

namespace vick {
namespace move {

boost::optional< std::shared_ptr<change> > mvsot(contents& contents, boost::optional<int>) {
    contents.waiting_for_desired = false;
    contents.x = 0;
    for(auto x : contents.cont[contents.y]) {
        if(x == ' ' || x == '\t') contents.x++;
        else break;
    }
    return boost::none;
}

}
}

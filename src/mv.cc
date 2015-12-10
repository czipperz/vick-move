#include <boost/optional.hpp>

#include "../../../src/contents.hh"

namespace vick {
namespace move {

void mv(contents& contents, move_t y, move_t x) {
    contents.y = y;
    contents.x = x;
    if(static_cast<move_ts>(contents.y) < 0) contents.y = 0;
    if(contents.y >= contents.cont.size())
        contents.y = contents.cont.size() - 1;
    if(static_cast<move_ts>(contents.x) < 0) contents.x = 0;
    if(contents.x >= contents.cont[contents.y].size())
        contents.x = contents.cont[contents.y].size() - 1;
    return boost::none;
}

}
}

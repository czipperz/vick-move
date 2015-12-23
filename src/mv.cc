 #include <boost/optional.hpp>

#include "../../../src/contents.hh"

namespace vick {
namespace move {

void mv(contents& contents, move_t y, move_t x) {
    if (static_cast<move_ts>(y) < 0) y = 0;
    if (y >= contents.cont.size())
        y = contents.cont.size() - 1;
    if (static_cast<move_ts>(x) < 0) x = 0;
    if (x >= contents.cont[y].size())
        x = contents.cont[y].size() - 1;
    contents.y = y;
    contents.x = x;
}

}
}

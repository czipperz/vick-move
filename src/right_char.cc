#include "../lib.hh"

namespace vick {
namespace move {
std::shared_ptr<change>
right_char(contents& contents, boost::optional<int> op) {
    int times = op ? *op : 1;
    if (times < 0) {
        return left_char(contents, -times);
    }
    if (contents.x + times > contents.cont[contents.y].size()) {
        contents.x = contents.cont[contents.y].size();
    } else {
        contents.x += times;
    }
    return nullptr;
}
}
}

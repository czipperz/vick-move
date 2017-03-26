#include "../lib.hh"

namespace vick {
namespace move {
std::shared_ptr<change>
left_char(contents& contents, boost::optional<int> op) {
    int times = op ? *op : 1;
    if (times < 0) {
        return right_char(contents, -times);
    }
    if (contents.x <= times) {
        contents.x = 0;
    } else {
        contents.x -= times;
    }
    return nullptr;
}
}
}

#include "../lib.hh"
#include "vick-predicates/lib.hh"

namespace vick {
namespace move {

std::shared_ptr<change>
backward_char(contents& contents, boost::optional<int> op) {
    int times = op ? *op : 1;
    if (times < 0) {
        return forward_char(contents, times);
    }
    for (; times != 0; --times) {
        if (predicates::start_of_line(contents)) {
            if (not predicates::start_of_buffer(contents)) {
                --contents.y;
                contents.x = contents.cont[contents.y].size();
            }
        } else {
            --contents.x;
        }
    }
    return nullptr;
}
}
}

#include "../lib.hh"
#include "vick-predicates/lib.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
forward_char(contents& contents, boost::optional<int> op) {
    int times = op ? *op : 1;
    if (times < 0) {
        return backward_char(contents, times);
    }
    for (; times != 0; --times) {
        if (predicates::end_of_line(contents)) {
            if (not predicates::end_of_buffer(contents)) {
                ++contents.y;
                contents.x = 0;
            }
        } else {
            ++contents.x;
        }
    }
    return boost::none;
}
}
}

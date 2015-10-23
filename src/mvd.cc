#include <boost/optional.hpp>

#include "../../../src/contents.hh"
#include "../../../src/show_message.hh"
#include "../../../src/visual.hh"

boost::optional< std::shared_ptr<change> > mvd(contents& contents, boost::optional<int> op) {
    int times = op ? op.get() : 1;
    if(long(contents.y + times) < 0 || contents.y + times >= contents.cont.size()) {
        show_message("Can't move to that location (start/end of buffer)");
        return boost::none;
    }
    int vis = to_visual(contents.cont[contents.y], contents.x);
    contents.y += times;
    size_t len = contents.cont[contents.y].length();
    if(contents.waiting_for_desired) {
        if((long)contents.x < 0) {
            contents.x = len - 1;
            auto vis = from_visual(contents.cont[contents.y],
                                   contents.desired_x);
            if(vis < contents.x) {
                contents.x = vis;
                contents.waiting_for_desired = false;
            }
        } else if(contents.x >= len) {
            contents.x = len - 1;
        } else if((contents.desired_x > contents.x
                   && contents.desired_x < len)
                  || contents.desired_x == 0) {
            // x  desired  len
            contents.x = contents.desired_x;
            contents.waiting_for_desired = false;
        } else {
            // x  len  desired
            contents.x = len - 1;
        }
    } else if(len <= contents.x && len > 0) {
        contents.waiting_for_desired = true;
        contents.desired_x = contents.x;
        contents.x = len - 1;
    } else {
        int des = contents.x;
        contents.x = from_visual(contents.cont[contents.y],vis);
        if(len == 0) {
            contents.waiting_for_desired = true;
            contents.desired_x = des;
        }
    }
    contents.x = (long) contents.x >= 0 ? contents.x : 0;
    return boost::none;
}

boost::optional< std::shared_ptr<change> > mvu(contents& contents, boost::optional<int> op) {
    return mvd(contents, op ? -op.get() : -1);
}

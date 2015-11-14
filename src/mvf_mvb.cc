#include "../../../src/show_message.hh"
#include "move.hh"

namespace vick {
namespace move {

template<class T>
inline static T fixLen(T len) {
    return len ? len : 1;
}
boost::optional< std::shared_ptr<change> > mvf(contents& contents, boost::optional<int> op) {
    if (contents.y == contents.cont.size() - 1 &&
        contents.x == contents.cont[contents.y].size() - 1) {
        show_message("Can't move to that location (start/end of buffer)");
        return boost::none;
    }
    int times = op ? op.get() : 1;
    move_ts newx = contents.x + times;
    try {
        while (static_cast<move_ts>(
                   fixLen(contents.cont.at(contents.y).length())) <= newx) {
            newx -= fixLen(contents.cont[contents.y].length());
            contents.y++;
        }
    } catch(const std::out_of_range&) { }
    if(contents.y >= contents.cont.size()) contents.y = contents.cont.size() - 1;
    contents.x = static_cast<move_ts>(contents.x) < 0 ? 0 : newx;
    contents.waiting_for_desired = false;
    return boost::none;
}
boost::optional< std::shared_ptr<change> > mvb(contents& contents, boost::optional<int> op) {
    if (contents.y == 0 && contents.x == 0) {
        show_message("Can't move to that location (start/end of buffer)");
        return boost::none;
    }
    int times = op ? op.get() : 1;
    long newx = contents.x - times;
    try {
        while(newx < 0) {
            contents.y--;
            newx += fixLen(contents.cont.at(contents.y).length());
        }
    } catch(const std::out_of_range&) {}
    if(newx < 0) contents.x = 0;
    else         contents.x = newx;
    contents.waiting_for_desired = false;
    return boost::none;
}

}
}

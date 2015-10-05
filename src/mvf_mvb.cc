#include "move.hh"

inline static unsigned int fixLen(unsigned int len) {
    return len ? len : 1;
}
void mvf(contents& contents, boost::optional<int> op) {
    int times = op ? op.get() : 1;
    long newx = contents.x + times;
    try {
        while(fixLen(contents.cont.at(contents.y).length()) <= newx) {
            newx -= fixLen(contents.cont[contents.y].length());
            contents.y++;
        }
    } catch(...) { }
    if(contents.y >= contents.cont.size()) contents.y = contents.cont.size() - 1;
    if((long) contents.x < 0) contents.x = 0;
    else                      contents.x = newx;
    contents.waiting_for_desired = false;
}
void mvb(contents& contents, boost::optional<int> op) {
    int times = op ? op.get() : 1;
    if(contents.y == 0 && contents.x == 0) return;
    long newx = contents.x - times;
    try {
        while(newx < 0) {
            contents.y--;
            newx += fixLen(contents.cont.at(contents.y).length());
        }
    } catch(...) { }
    if(newx < 0) contents.x = 0;
    else         contents.x = newx;
    contents.waiting_for_desired = false;
}

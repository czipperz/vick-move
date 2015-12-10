#include "move.hh"
#include "move_word_p.hh"

namespace vick {
namespace move {

boost::optional< std::shared_ptr<change> > mvbww(contents& contents, boost::optional<int> op) {
    if(op && op.get() < 0) return mvfww(contents, op.get() * -1);
    int num = op ? op.get() : 1;
    if(num == 0 || num == -0) return boost::none;
#define boundsCheck if ((static_cast<move_ts>(contents.y) < 0) or       \
                        (contents.y == 0 and contents.x <= 0) or        \
                        (contents.x == 0 and not isWhitespace(ch))) {   \
        if(contents.x == contents.cont[contents.y].size() - 1)          \
            mvf(contents);                                              \
        return boost::none;                                             \
    }
#define ch contents.cont[contents.y][contents.x]
    mvb(contents);
    while(isWhitespace(ch)) {
        mvb(contents);
        boundsCheck;
    }
    do {
        mvb(contents);
        boundsCheck;
    } while(not isWhitespace(ch));
    mvf(contents);
    return boost::none;
#undef boundsCheck
#undef ch
}

}
}

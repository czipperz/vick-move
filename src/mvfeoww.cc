#include "move.hh"
#include "move_word_p.hh"

namespace vick {
namespace move {

boost::optional< std::shared_ptr<change> > mvfeoww(contents& contents, boost::optional<int> op) {
    if (op and op.get() < 0) return mvbww(contents, -op.get());
    int num = op ? op.get() : 1;
    if (num == 0) return boost::none;
#define boundsCheck                                                            \
    if ((contents.y >= contents.cont.size()) or                                \
        (contents.y == contents.cont.size() - 1 and                            \
         contents.x >= contents.cont[contents.y].size()) or                    \
        (contents.cont[contents.y].size() and contents.x == 0 and              \
         not isWhitespace(ch))) {                                              \
        mvb(contents);                                                         \
        return boost::none;                                                    \
    }
#define ch contents.cont[contents.y][contents.x]
    mvf(contents);
    while (isWhitespace(ch)) {
        mvf(contents);
        boundsCheck;
    }
    do {
        mvf(contents);
        boundsCheck;
    } while (not isWhitespace(ch));
    mvb(contents);
    return boost::none;
#undef boundsCheck
#undef ch
}

}
}

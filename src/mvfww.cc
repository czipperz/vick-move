#include "move.hh"
#include "move_word_p.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
mvfww(contents& contents, boost::optional<int> op)
{
    if (op and op.get() < 0)
        return mvbww(contents, op.get() * -1);
    int num = op ? op.get() : 1;
    if (num == 0) return boost::none;
#define boundsCheck                                                            \
    if ((contents.y >= contents.cont.size()) or                                \
        (contents.y == contents.cont.size() - 1 and                            \
         contents.x >= contents.cont[contents.y].size()))                      \
        return boost::none;
#define ch contents.cont[contents.y][contents.x]
    auto y_ = contents.y;
    mvf(contents);
    if (y_ == contents.y) while (not isWhitespace(ch)) {
        auto y = contents.y;
        mvf(contents);
        if (contents.y != y) break;
        boundsCheck;
    }
    if (contents.cont[contents.y].size()) {}
    while (isWhitespace(ch)) {
        mvf(contents);
        boundsCheck;
    }
    return boost::none;
#undef boundsCheck
#undef ch
}

}
}

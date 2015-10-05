#include "move.hh"
#include "move_word_p.hh"

void mvfww(contents& contents, boost::optional<int> op) {
    if(op && op.get() < 0) return mvbww(contents, op.get() * -1);
    int num = op ? op.get() : 1;
    if(num == 0 || num == -0) return;
    #define boundsCheck if((contents.y >= contents.cont.size()) or      \
                           (contents.y == contents.cont.size() - 1 and  \
                            contents.x >= contents.cont[contents.y].size())) return;
    #define ch contents.cont[contents.y][contents.x]
    auto y_ = contents.y;
    mvf(contents);
    if(y_ == contents.y) while(!isWhitespace(ch)) {
        auto y = contents.y;
        mvf(contents);
        if(contents.y != y) break;
        boundsCheck;
    }
    if(contents.cont[contents.y].size()) {}
    while(isWhitespace(ch)) {
        mvf(contents);
        boundsCheck;
    }
    #undef boundsCheck
    #undef ch
}

#include "move.hh"
#include "move_word_p.hh"

namespace vick {
namespace move {

boost::optional< std::shared_ptr<change> > mvfeow(contents& contents, boost::optional<int> op) {
    if(op && op.get() < 0) return mvbw(contents, op.get() * -1);
    int num = op ? op.get() : 1;
    if(num == 0 || num == -0) return boost::none;
    //move at least one forward
    //move over whitespace
    //if delimitor then move until not delimitor
    //else move until delimitor or whitespace
    //move back one
    #define boundsCheck                                              \
      if ((contents.y >= contents.cont.size()) ||                    \
          (contents.y == contents.cont.size() - 1 &&                 \
           contents.x >= contents.cont[contents.y].size()) ||        \
          (contents.x == 0 && !isWhitespace(ch) &&                   \
           contents.cont[contents.y].size() != 0)) {                 \
        mvb(contents);                                               \
        return boost::none;                                          \
      }
    #define ch contents.cont[contents.y][contents.x]
    mvf(contents);
    while(isWhitespace(ch)) {
        mvf(contents);
        boundsCheck;
    }
    if(isDeliminator(ch)) {
        do {
            mvf(contents);
            boundsCheck;
        } while(isDeliminator(ch));
        mvb(contents);
    } else {
        do {
            mvf(contents);
            boundsCheck;
        } while(!isDeliminator(ch) && !isWhitespace(ch));
        mvb(contents);
    }
    if(num > 1) mvfeow(contents,num - 1);
    return boost::none;
    #undef boundsCheck
    #undef ch
}

}
}

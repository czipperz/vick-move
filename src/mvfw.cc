#include "move.hh"
#include "move_word_p.hh"

boost::optional< std::shared_ptr<change> > mvfw(contents& contents, boost::optional<int> op) {
    if(op && op.get() < 0) return mvbw(contents, op.get() * -1);
    int num = op ? op.get() : 1;
    if(num == 0 || num == -0) return boost::none;
    //if whitespace move forward until not whitespace
    //else if deliminator then move forward until not deliminator then move over whitespace
    //else move foward until deliminator or whitespace
#define boundsCheck if(contents.cont[contents.y].size() == 0 and contents.cont.size() - 1 != contents.y) {} \
        else if((contents.y >= contents.cont.size()) or                 \
                (contents.y == contents.cont.size() - 1 and             \
                 contents.x >= contents.cont[contents.y].size() - 1) or     \
                (contents.x == 0 and not isWhitespace(ch))) return boost::none;
    #define ch contents.cont[contents.y][contents.x]
    if(isWhitespace(ch)) {
        do {
            mvf(contents);
            boundsCheck;
        } while(isWhitespace(ch));
    } else if(isDeliminator(ch)) {
        do {
            mvf(contents);
            boundsCheck;
        } while(isDeliminator(ch));
        while(isWhitespace(ch)) {
            mvf(contents);
            boundsCheck;
        }
    } else /* word character */ {
        do {
            mvf(contents);
            boundsCheck;
        } while(!isDeliminator(ch) && !isWhitespace(ch));
        while(isWhitespace(ch)) {
            mvf(contents);
            boundsCheck;
        }
    }
    if(num > 1) mvfw(contents,num - 1);
    return boost::none;
    #undef boundsCheck
    #undef ch
}

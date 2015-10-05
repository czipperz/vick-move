#include "move.hh"
#include "move_word_p.hh"

void mvfw(contents& contents, boost::optional<int> op) {
    if(op && op.get() < 0) return mvbw(contents, op.get() * -1);
    int num = op ? op.get() : 1;
    if(num == 0 || num == -0) return;
    //if whitespace move forward until not whitespace
    //else if deliminator then move forward until not deliminator then move over whitespace
    //else move foward until deliminator or whitespace
    #define boundsCheck if(contents.cont[contents.y].size() == 0) {}    \
        else if((contents.y >= contents.cont.size()) or                 \
                (contents.y == contents.cont.size() - 1 and             \
                 contents.x >= contents.cont[contents.y].size()) or     \
                (contents.x == 0 and not isWhitespace(ch))) return;
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
    #undef boundsCheck
    #undef ch
}

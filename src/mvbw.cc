#include "move.hh"
#include "move_word_p.hh"

void mvbw(contents& contents, boost::optional<int> op) {
    if(op && op.get() < 0) return mvfw(contents, op.get() * -1);
    int num = op ? op.get() : 1;
    if(num == 0 || num == -0) return;
    //move back one then
    //if delimitor then move back until no delimitor
    //else if whitespace then move back until not whitespace then
    //   move back consistently over delimitors or word chars
    //else /*word char*/ move back until not word char or
    //   whitespace
    //move forward one
    #define boundsCheck if(((long) contents.y < 0) or                   \
                           (contents.y == 0 and contents.x == 0) or     \
                           (contents.x == 0 and not isWhitespace(ch))) { \
            if(contents.x == contents.cont[contents.y].size() - 1)      \
                mvf(contents);                                          \
            return;                                                     \
        }
    #define ch contents.cont[contents.y][contents.x]
    mvb(contents);
    while(isWhitespace(ch)) {
        mvb(contents);
        boundsCheck;
    }
    if(isDeliminator(ch)) {
        do {
            mvb(contents);
            if(((long) contents.y < 0) or
               (contents.y == 0 and contents.x == 0) or
               (contents.x == 0 and not isWhitespace(ch))) {
                mvf(contents);
                return;
            }
        } while(isDeliminator(ch));
        mvf(contents);
    } else {
        if(contents.x == 0 and contents.cont[contents.y].size()) return;
        do {
            mvb(contents);
            boundsCheck;
        } while(!isDeliminator(ch) && !isWhitespace(ch));
        mvf(contents);
    }
    if(num > 1) mvbw(contents,num - 1);
    #undef boundsCheck
    #undef ch
}
#include "move.hh"
#include "move_word_p.hh"

void mvfeoww(contents& contents, boost::optional<int> op) {
    if(op && op.get() < 0) return mvbww(contents, op.get() * -1);
    int num = op ? op.get() : 1;
    if(num == 0 || num == -0) return;
}

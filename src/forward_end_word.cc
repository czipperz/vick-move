#include "../lib.hh"
#include "move_word_p.hh"

namespace vick {
namespace move {

boost::optional<std::shared_ptr<change> >
forward_end_word(contents& contents, boost::optional<int> op) {
    if (op and op.get() < 0)
        return backward_begin_word(contents, -op.get());
    int num;
    if (op) {
        num = *op;
        if (num == 0) {
            return boost::none;
        }
    } else {
        num = 1;
    }
    if (num == 0) {
        return boost::none;
    }

#define ch contents.cont[contents.y][contents.x]
start:
    // go to start of next word
    while (isWhitespace(ch)) {
        forward_char(contents);
    }
    if (isDeliminator(ch)) {
        do {
            forward_char(contents);
        } while (isDeliminator(ch));
    }

    if (num > 1) {
        --num;
        goto start;
    }
    return boost::none;
}

}
}

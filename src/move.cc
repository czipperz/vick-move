#include <algorithm>
#include <string>
#include <vector>
#include <boost/optional.hpp>
#include <locale>

#include "../../../src/prompt.hh"
#include "../../../src/configuration.hh"
#include "../../../src/to_str.hh"
#include "../../../src/show_message.hh"
#include "../../../src/visual.hh"
#include "move.hh"

void mvline(contents& contents, boost::optional<int> line) {
    if(line) {
        contents.x = 0;
        int cont = line.get();
        if(cont < 0) {
            show_message("Can't move to a negative line!");
            contents.y = 0;
            return;
        }
        contents.y = cont;
        if(cont >= contents.cont.size()) {
            contents.y = contents.cont.size() - 1;
            show_message("Can't move past end of buffer!");
        }
    } else {
        while(true) {
            std::string str = prompt("Goto line: ");
            try {
                int res = std::stoi(str);
                mvline(contents, res);
                return;
            } catch(std::invalid_argument) {
                continue;
            }
        }
    }
}
void mv(contents& contents, unsigned long _y, unsigned long _x) {
    contents.y = _y;
    contents.x = _x;
    if((long) contents.y < 0) contents.y = 0;
    if(contents.y >= contents.cont.size())
        contents.y = contents.cont.size() - 1;
    if((long) contents.x < 0) contents.x = 0;
    if(contents.x >= contents.cont[contents.y].size())
        contents.x = contents.cont[contents.y].size() - 1;
}

void mvrel(contents& contents, long y, long x) {
    if(y < 0) mvu(contents,-y);
    else      mvd(contents, y);
    if(x < 0) mvb(contents,-x);
    else      mvf(contents, x);
}

void mvcol(contents& contents, boost::optional<int> col) {
    if(col) {
        unsigned int len = contents.cont[contents.y].length();
        if(len >= col.get()) {
            contents.x = col.get();
            contents.waiting_for_desired = false;
        } else {
            show_message((std::string("Can't move to column: ")
                          + int_to_str(col.get())).c_str());
        }
    } else {
        while(true) {
            std::string str = prompt("Goto column: ");
            try {
                int res = std::stoi(str);
                mvcol(contents, res);
                return;
            } catch(std::invalid_argument) {
                continue;
            }
        }
    }
}

void mvsot(contents& contents, boost::optional<int> op) {
    mvsol(contents, op);
    const std::string& str = contents.cont[contents.y];
    for(unsigned int i = 0; i < str.length(); i++) {
        if(str[i] == ' ' || str[i] == '\t')
            mvf(contents, op);
        else break;
    }
}

void mveol(contents& contents, boost::optional<int>) {
    mvcol(contents,contents.cont[contents.y].length() - 1);
}
void mvsol(contents& contents, boost::optional<int>) {
    mvcol(contents,0);
}

void mvsop(contents& contents, boost::optional<int>) {
    contents.y = 0;
    contents.x = 0;
    contents.waiting_for_desired = false;
    contents.y_offset = 0;
}
void mveop(contents& contents, boost::optional<int>) {
    contents.y = contents.cont.size() - 1;
    contents.x = 0;
    contents.y_offset = contents.y - contents.max_y + 2;
    contents.waiting_for_desired = false;
}

void mvd(contents& contents, boost::optional<int> op) {
    int times = op ? op.get() : 1;
    if(contents.y + times < 0 || contents.y + times >= contents.cont.size()) {
        show_message("Can't move to that location (start/end of buffer)");
        return;
    }
    int vis = to_visual(contents.cont[contents.y],contents.x);
    contents.y += times;
    unsigned int len = contents.cont[contents.y].length();
    if(contents.waiting_for_desired) {
        if((int)contents.x < 0) {
            contents.x = len - 1;
            unsigned int vis = from_visual(contents.cont[contents.y],
                                           contents.desired_x);
            if(vis < contents.x) {
                contents.x = vis;
                contents.waiting_for_desired = false;
            }
        } else if(contents.x >= len) {
            contents.x = len - 1;
        } else if((contents.desired_x > contents.x
                   && contents.desired_x < len)
                  || contents.desired_x == 0) {
            // x  desired  len
            contents.x = contents.desired_x;
            contents.waiting_for_desired = false;
        } else {
            // x  len  desired
            contents.x = len - 1;
        }
    } else if(len <= contents.x && len > 0) {
        contents.waiting_for_desired = true;
        contents.desired_x = contents.x;
        contents.x = len - 1;
    } else {
        int des = contents.x;
        contents.x = from_visual(contents.cont[contents.y],vis);
        if(len == 0) {
            contents.waiting_for_desired = true;
            contents.desired_x = des;
        }
    }
    contents.x = (long) contents.x >= 0 ? contents.x : 0;
    if(contents.y - contents.y_offset >= contents.max_y)
        contents.y_offset = contents.y - contents.y_offset + 1;
    if(contents.y < contents.y_offset)
        contents.y_offset = contents.y;
}
void mvu(contents& contents, boost::optional<int> op) {
    if(op) mvd(contents,-op.get());
    else mvd(contents,-1);
}


inline static bool isDeliminator(char ch) {
    return std::find(DELIMINATORS.begin(), DELIMINATORS.end(), ch)
                                        != DELIMINATORS.end();
}
inline static bool isWhitespace(char ch) {
    static const std::locale loc;
    return std::isspace(ch, loc);
}
void mvfw(contents& contents, boost::optional<int> op) {
    if(op && op.get() < 0) return mvbw(contents, op.get() * -1);
    int num = op ? op.get() : 1;
    if(num == 0 || num == -0) return;
    if(num < 0) return mvbw(contents, -op.get());
    //if deliminator then move forward until not deliminator then move over whitespace
    //else move foward until (whitespace -> move till not whitespace) or (deliminator -> stop)
    #define boundsCheck if(contents.y >= contents.cont.size() || \
                           (contents.y == contents.cont.size() - 1 &&   \
                            contents.x >= contents.cont[contents.y].size())) return;
    #define ch contents.cont[contents.y][contents.x]
    if(isDeliminator(ch)) {
        do {
            mvf(contents);
            boundsCheck;
        } while(isDeliminator(ch));
        while(isWhitespace(ch)) {
            mvf(contents);
            boundsCheck;
        }
    } else {
        while(!isDeliminator(ch) and !isWhitespace(ch)) {
            mvf(contents);
            boundsCheck;
        }
        if(isWhitespace(ch)) {
            while(isWhitespace(ch)) {
                mvf(contents);
                boundsCheck;
            }
        } else {
            while(isDeliminator(ch)) {
                mvf(contents);
                boundsCheck;
            }
        }
    }
    #undef boundsCheck
    if(num > 0) mvfw(contents,num - 1);
}
void mvfeow(contents& contents, boost::optional<int> op) {
    //move at least one forward
    //move over non deliminators
    //move over deliminators
}
void mvbw(contents& contents, boost::optional<int> op) {
    //move back one then
    //if delimitor then move back until no delimitor
    //else if whitespace then move back until not whitespace then
    //   move back consistently over delimitors or word chars
    //else /*word char*/ move back until not word char or
    //   whitespace
    //move forward one
}


inline static unsigned int fixLen(unsigned int len) {
    return len ? len : 1;
}
void mvf(contents& contents, boost::optional<int> op) {
    int times = op ? op.get() : 1;
    long newx = contents.x + times;
    try {
        while(fixLen(contents.cont.at(contents.y).length()) <= newx) {
            newx -= fixLen(contents.cont[contents.y].length());
            contents.y++;
        }
    } catch(...) { }
    if(contents.y >= contents.cont.size()) contents.y = contents.cont.size() - 1;
    if(contents.x < 0) contents.x = 0;
    else               contents.x = newx;
    contents.waiting_for_desired = false;
}
void mvb(contents& contents, boost::optional<int> op) {
    int times = op ? op.get() : 1;
    if(contents.y == 0 && contents.x == 0) return;
    long newx = contents.x - times;
    try {
        while(newx < 0) {
            contents.y--;
            newx += fixLen(contents.cont.at(contents.y).length());
        }
    } catch(...) { }
    if(newx < 0) contents.x = 0;
    else         contents.x = newx;
    contents.waiting_for_desired = false;
}

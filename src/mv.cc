#include <boost/optional.hpp>

#include "../../../src/contents.hh"

void mv(contents& contents, unsigned long y, unsigned long x) {
    contents.y = y;
    contents.x = x;
    if((long) contents.y < 0) contents.y = 0;
    if(contents.y >= contents.cont.size())
        contents.y = contents.cont.size() - 1;
    if((long) contents.x < 0) contents.x = 0;
    if(contents.x >= contents.cont[contents.y].size())
        contents.x = contents.cont[contents.y].size() - 1;
}

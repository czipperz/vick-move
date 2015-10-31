#include <boost/optional.hpp>

#include "../../../src/contents.hh"

boost::optional< std::shared_ptr<change> > mv(contents& contents, move_t y, move_t x) {
    contents.y = y;
    contents.x = x;
    if((long) contents.y < 0) contents.y = 0;
    if(contents.y >= contents.cont.size())
        contents.y = contents.cont.size() - 1;
    if((long) contents.x < 0) contents.x = 0;
    if(contents.x >= contents.cont[contents.y].size())
        contents.x = contents.cont[contents.y].size() - 1;
    return boost::none;
}

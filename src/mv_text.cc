#include <boost/optional.hpp>

#include "move.hh"
#include "../../../src/contents.hh"

void mvsot(contents& contents, boost::optional<int> op) {
    mvsol(contents, op);
    const std::string& str = contents.cont[contents.y];
    for(unsigned int i = 0; i < str.length(); i++) {
        if(str[i] == ' ' || str[i] == '\t')
            mvf(contents, op);
        else break;
    }
}

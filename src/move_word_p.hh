#include <locale>

#include "../../../src/configuration.hh"

namespace vick {

inline static bool isDeliminator(char ch) {
    return std::find(DELIMINATORS.begin(), DELIMINATORS.end(), ch) !=
           DELIMINATORS.end();
}

inline static bool isWhitespace(char ch) {
    static const std::locale loc;
    return std::isspace(ch, loc);
}
}

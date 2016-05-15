#include <locale>

#include "configuration.hh"

namespace vick {

inline static bool isDeliminator(char ch) {
    return std::find(DELIMINATORS.begin(), DELIMINATORS.end(), ch) !=
           DELIMINATORS.end();
}

inline static bool isWhitespace(char ch) {
    return std::isspace(ch, std::locale());
}
}

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

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

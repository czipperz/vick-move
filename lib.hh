/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_NEW_MOVE_H
#define HEADER_GUARD_NEW_MOVE_H

#include <string>
#include <vector>

#include "contents.hh"

namespace vick {
namespace move {

/*!
 * \file vick-move/lib.hh
 * \brief Basic movement functionality is defined here
 *
 * A word is deliminated by `DELIMINATORS`
 *
 * A wword is deliminated by a character that passes `std::isspace()`
 */

/*!
 * \brief Moves to the line given as a prefix argument or prompts the
 * user for one.
 */
std::shared_ptr<change>
line(contents& contents, boost::optional<int> line);

/*!
 * \brief Moves contents.y and contents.x to the given location and
 * checks they are in the boundaries of the buffer.
 */
std::shared_ptr<change>
yx(contents& contents, move_t y, move_t x);


/*!
 * \brief Moves the cursor forward until it finds a character in
 * MATCHES, then finds the corresponding matching character and moves
 * to it.
 */
std::shared_ptr<change>
match(contents& contents, boost::optional<int> = boost::none);

/*!
 * \brief Moves contents.x to the given prefix location or prompts
 * user for a column to move to if no prefix is given
 */
std::shared_ptr<change>
column(contents& contents, boost::optional<int> col);


/*!
 * \brief Moves contents.x to the first non whitespace character.
 * Ignores the prefix argument.
 */
std::shared_ptr<change>
start_text(contents& contents, boost::optional<int> unused = boost::none);
/*!
 * \brief Moves contents.x to the first non whitespace character.
 * Ignores the prefix argument.
 */
std::shared_ptr<change>
end_text(contents& contents, boost::optional<int> unused = boost::none);


/*!
 * \brief Moves contents.x to the firstt character of the line.
 * Ignores the prefix argument.
 */
std::shared_ptr<change>
start_line(contents& contents, boost::optional<int> unused = boost::none);
/*!
 * \brief Moves contents.x to the last character of the line.
 * Ignores the prefix argument.
 */
std::shared_ptr<change>
end_line(contents& contents, boost::optional<int> unused = boost::none);


/*!
 * \brief Moves to the very beginning of the buffer
 * Ignores the prefix argument.
 */
std::shared_ptr<change>
start_buffer(contents& contents, boost::optional<int> unused = boost::none);
/*!
 * \brief Moves to the very beginning of the buffer
 * Ignores the prefix argument
 */
std::shared_ptr<change>
end_buffer(contents& contents, boost::optional<int> unused = boost::none);


/*!
 * \brief Moves down a given number of lines or one.
 */
std::shared_ptr<change>
forward_line(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves up a given number of lines or one.
 */
std::shared_ptr<change>
backward_line(contents& contents, boost::optional<int> times = 1);


/*!
 * \brief Moves forward a given number of whitespace delineated words,
 * or one.
 */
std::shared_ptr<change>
forward_begin_wword(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves backward a given number of delineated whitespace
 * words, or one.
 */
std::shared_ptr<change>
backward_begin_wword(contents& contents, boost::optional<int> times = 1);


/*!
 * \brief Moves forward to the end of a given number of delineated
 * whitespace words, or one.
 */
std::shared_ptr<change>
forward_end_wword(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves backward a given number of delineated whitespace
 * words, or one.
 */
std::shared_ptr<change>
backward_end_wword(contents& contents, boost::optional<int> times = 1);


/*!
 * \brief Moves forward a given number of words, or one.
 */
std::shared_ptr<change>
forward_begin_word(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves backward a given number of words, or one.
 */
std::shared_ptr<change>
backward_begin_word(contents& contents, boost::optional<int> times = 1);


/*!
 * \brief Moves forward to the end of a given number of words, or one.
 */
std::shared_ptr<change>
forward_end_word(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves backward to the end of a given number of words, or one.
 */
std::shared_ptr<change>
backward_end_word(contents& contents, boost::optional<int> times = 1);


/*!
 * \brief Moves forward a given number of characters, or one.
 */
std::shared_ptr<change>
forward_char(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves backward a given number of characters, or one.
 */
std::shared_ptr<change>
backward_char(contents& contents, boost::optional<int> times = 1);


/*!
 * \brief Moves left a given number of characters, or one.
 */
std::shared_ptr<change>
left_char(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves right a given number of characters, or one.
 */
std::shared_ptr<change>
right_char(contents& contents, boost::optional<int> times = 1);
}
}

#endif

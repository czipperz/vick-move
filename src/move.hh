#ifndef HEADER_GUARD_NEW_MOVE_H
#define HEADER_GUARD_NEW_MOVE_H

#include <string>
#include <vector>
#include "../../../src/file_contents.hh"

/*!
 * \file move.hh
 * \brief Basic movement functionality is defined here
 */

/*!
 * \brief Moves to the line given as a prefix argument or prompts the
 * user for one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] line The line to move to.  If none is given, prompts user
 * for one.
 *
 * \post ``contents.y`` will be between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvline(contents& contents, boost::optional<int> line);
/*!
 * \brief Moves contents.y and contents.x to the given location and
 * checks they are in the boundaries of the buffer.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] y The vertical y coordinate to move to
 * \param[in] x The horizontal x coordinate to move to
 *
 * \post ``contents.y`` will be between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 * \post ``contents.x`` will be between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mv(contents& contents, move_t y, move_t x);

/*!
 * \brief Moves contents.x to the given prefix location or prompts
 * user for a column to move to if no prefix is given
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] col The column to move to, or if one isn't provided, it
 * will be prompted interactively.
 *
 * \post ``contents.x`` will be between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvcol(contents& contents, boost::optional<int> col);

/*!
 * \brief Moves contents.x to the first non whitespace character.
 * Ignores the prefix argument.
 *
 * \param[in,out] contents The contents object to move on
 * \param unused Unused prefix argument
 *
 * \post ``contents.x`` will be between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvsot(contents& contents, boost::optional<int> unused = boost::none);

/*!
 * \brief Moves contents.x to the last character of the line.
 * Ignores the prefix argument.
 *
 * \param[in,out] contents The contents object to move on
 * \param unused Unused prefix argument
 *
 * \post ``contents.x == contents.cont[contents.y].size() - 1``
 */
boost::optional < std::shared_ptr<change> > mveol(contents& contents, boost::optional<int> unused = boost::none);
/*!
 * \brief Moves contents.x to the firstt character of the line.
 * Ignores the prefix argument.
 *
 * \param[in,out] contents The contents object to move on
 * \param unused Unused prefix argument
 *
 * \post ``contents.x == 0``
 */
boost::optional < std::shared_ptr<change> > mvsol(contents& contents, boost::optional<int> unused = boost::none);

/*!
 * \brief Moves to the very beginning of the buffer
 * Ignores the prefix argument.
 *
 * \param[in,out] contents The contents object to move on
 * \param unused Unused prefix argument
 *
 * \post ``contents.x == 0``
 * \post ``contents.y == 0``
 */
boost::optional < std::shared_ptr<change> > mvsop(contents& contents, boost::optional<int> unused = boost::none);
/*!
 * \brief Moves to the very beginning of the buffer
 * Ignores the prefix argument
 *
 * \param[in,out] contents The contents object to move on
 * \param unused Unused prefix argument
 *
 * \post ``contents.x == 0``
 * \post ``contents.y == contents.cont.size() - 1``
 */
boost::optional < std::shared_ptr<change> > mveop(contents& contents, boost::optional<int> unused = boost::none);

/*!
 * \brief Moves down a given number of lines or one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] times The number of lines to move down
 *
 * \post ``contents.x`` is between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 * \post ``contents.y`` is between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvd(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves up a given number of lines or one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] times The number of lines to move up
 *
 * \post ``contents.x`` is between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 * \post ``contents.y`` is between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvu(contents& contents, boost::optional<int> times = 1);

/*!
 * \brief Moves forward a given number of whitespace delineated words,
 * or one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] times The number of whitespace delineated words to move
 * forward
 *
 * \post ``contents.x`` is between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 * \post ``contents.y`` is between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvfww(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves forward to the end of a given number of delineated
 * whitespace words, or one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] times The number of whitespace delineated words to move
 * forward to the end of
 *
 * \post ``contents.x`` is between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 * \post ``contents.y`` is between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvfeoww(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves backward a given number of delineated whitespace
 * words, or one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] times The number of whitespace delineated words to move
 * backward
 *
 * \post ``contents.x`` is between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 * \post ``contents.y`` is between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvbww(contents& contents, boost::optional<int> times = 1);

/*!
 * \brief Moves forward a given number of words, or one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] times The number of words to move forward
 *
 * \post ``contents.x`` is between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 * \post ``contents.y`` is between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvfw(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves forward to the end of a given number of words, or one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] times The number of words to move to the end of
 *
 * \post ``contents.x`` is between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 * \post ``contents.y`` is between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvfeow(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves backward a given number of words, or one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] times The number of words to move backward
 *
 * \post ``contents.x`` is between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 * \post ``contents.y`` is between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvbw(contents& contents, boost::optional<int> times = 1);

/*!
 * \brief Moves forward a given number of characters, or one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] times The number of characters to move forward
 *
 * \post ``contents.x`` is between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 * \post ``contents.y`` is between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvf(contents& contents, boost::optional<int> times = 1);
/*!
 * \brief Moves backward a given number of characters, or one.
 *
 * \param[in,out] contents The contents object to move on
 * \param[in] times The number of characters to move forward
 *
 * \post ``contents.x`` is between ``0`` and
 * ``contents.cont[contents.y].size() - 1``, inclusive
 * \post ``contents.y`` is between ``0`` and
 * ``contents.cont.size() - 1``, inclusive
 */
boost::optional < std::shared_ptr<change> > mvb(contents& contents, boost::optional<int> times = 1);

#endif

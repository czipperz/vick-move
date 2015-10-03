#ifndef HEADER_GUARD_NEW_MOVE_H
#define HEADER_GUARD_NEW_MOVE_H

#include <string>
#include <vector>
#include "file_contents.hh"

/// prompts for int if not given one
void mvline (contents&, boost::optional<int>);
void mv     (contents&, unsigned long y, unsigned long x);

void mvrel  (contents&, long y,          long x);

void mvcol  (contents&, boost::optional<int>);

void mvsot  (contents&, boost::optional<int> = boost::none);

void mveol  (contents&, boost::optional<int> = boost::none);
void mvsol  (contents&, boost::optional<int> = boost::none);

void mvsop  (contents&, boost::optional<int> = boost::none);
void mveop  (contents&, boost::optional<int> = boost::none);

void mvd    (contents&, boost::optional<int> = 1);
void mvu    (contents&, boost::optional<int> = 1);

void mvfw   (contents&, boost::optional<int> = 1);
void mvfeow (contents&, boost::optional<int> = 1);
void mvbw   (contents&, boost::optional<int> = 1);

void mvf    (contents&, boost::optional<int> = 1);
void mvb    (contents&, boost::optional<int> = 1);

#endif

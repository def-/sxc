// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright (C) 2008 Dennis Felsing, Andreas Waidler

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*}}}*/

/* $Id$ */

// INCLUDE/*{{{*/

#include <gloox/gloox.h>

/*}}}*/


#ifndef GENERATEERRORTEXT_HXX
#define GENERATEERRORTEXT_HXX


//string &generateErrorText(connectionE, streamE, streamEText, authE);/*{{{*/

/**
 * @author Dennis Felsing
 * @brief Generate an error text.
 *
 * @param connectionError The connection error.
 * @param streamError More verbose information about a stream error.
 * @param streamErrorText An additional information text about the stream
 *        error.
 * @param authError More verbose information about an authentication error.
 * @return The generated text.
 */
std::string &generateErrorText(
    gloox::ConnectionError connectionError,
    gloox::StreamError streamError,
    const std::string &streamErrorText,
    gloox::AuthenticationError authError);

/*}}}*/


#endif // GENERATEERRORTEXT_HXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

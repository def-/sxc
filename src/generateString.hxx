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
#include <gloox/presence.h>
#include <gloox/message.h>

/*}}}*/


#ifndef GENERATESTRING_HXX
#define GENERATESTRING_HXX


//string &genConnErrorString(connE, streamE, streamEText, authE, debug=0);/*{{{*/

/**
 * @brief Generate a connection error text.
 *
 * @param connectionError The connection error.
 * @param streamError More verbose information about a stream error.
 * @param streamErrorText An additional information text about the stream
 *        error.
 * @param authError More verbose information about an authentication error.
 * @return The generated text.
 */
std::string &genConnErrorString(
    gloox::ConnectionError connectionError,
    gloox::StreamError streamError,
    const std::string &streamErrorText,
    gloox::AuthenticationError authError,
    bool isDebug = false);

/*}}}*/
//std::string &genPresenceString(gloox::Presence::PresenceType presence);/*{{{*/

/**
 * @brief Generate a presence text.
 *
 * @param presence The presence.
 * @return The generated text.
 */
std::string &genPresenceString(gloox::Presence::PresenceType presence);

/*}}}*/
//std::string &genStanzaErrorString(gloox::StanzaError error)/*{{{*/

/**
 * @brief Generate a stanza error text.
 *
 * @param error The stanza error.
 * @return The generated text.
 */
std::string &genStanzaErrorString(
    gloox::StanzaError error);

/*}}}*/
//std::string &genMsgTypeString(gloox::Message::MessageType type);/*{{{*/

/**
 * @brief Generate a text from a message type.
 *
 * @param type The message type.
 * @return The generated text.
 */
std::string &genMsgTypeString(gloox::Message::MessageType type);

/*}}}*/


#endif // GENERATESTRING_HXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

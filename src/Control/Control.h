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

/**
 *
 */


#ifndef CONTROL_CONTROL_H
#define CONTROL_CONTROL_H

// INCLUDE/*{{{*/

#include <string>
#include <gloox/jid.h>
#include <gloox/presence.h>

/*}}}*/


namespace Control
{
    class Control
    {
        public:
            //enum ReturnCode/*{{{*/

            /**
             * The return codes of the program.
             */
            enum ReturnCode
            {
                ReturnOk = 0,
                ReturnParametersInvalid,
                ReturnPortUnspecified = 21,
                ReturnPortInvalid,
                ReturnJidInvalid
            };

/*}}}*/
            //static ReturnCode initialize(const gloox::JID jid, int port = -1);/*{{{*/

            /**
             * Initialize the connection, the roster, and the control files.
             *
             * @param JID A valid JID.
             * @param port The port on the server to connect to. -1 to use the
             * default one.
             *
             * @return The return code @ref ReturnCode
             */
            static ReturnCode initialize(const gloox::JID jid, int port = -1);

/*}}}*/
            //static bool setPresence(/*{{{*/

            /**
             * Set the presence.
             *
             * @param presence The presence type. @ref
             * gloox::Presence::PresenceType
             * @param priority The priority ranging from -128 to 127.
             * @param status A message describing the status.
             *
             * @return Whether it was possible to set the presence.
             */
            static bool setPresence(
                gloox::Presence::PresenceType presence,
                int priority = 0,
                const std::string &status=gloox::EmptyString);

/*}}}*/
            //static int printError(/*{{{*/

            /**
             * Print an error to stderr.
             *
             * @param returnCode The return code of the error. @ref ReturnCode
             * @param text Additional information some return codes can have.
             *
             * @return The return code.
             */
            static int printError(
                ReturnCode returnCode,
                std::string text = gloox::EmptyString);

/*}}}*/

        private:
            //static const std::string outputPrefix;/*{{{*/

            /**
             * The text printed before every output to the console.
             */
            static const std::string outputPrefix;

/*}}}*/
            //static const std::string errorPrefix;/*{{{*/

            /**
             * The text printed before every error output to the console.
             */
            static const std::string errorPrefix;

/*}}}*/
            //static Control::Roster roster;/*{{{*/

            /**
             * The roster.
             */
            //static Control::Roster roster;

/*}}}*/
            //static Control::File::In input;/*{{{*/

            /**
             * The input file.
             */
            //static Control::File::In input;

/*}}}*/
            //static Control::File::Out output;/*{{{*/

            /**
             * The output file.
             */
            //static Control::File::Out output;

/*}}}*/
    };
}


#endif // CONTROL_CONTROL_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

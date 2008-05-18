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


#ifndef CONTROL_CONTROL_H
#define CONTROL_CONTROL_H

// INCLUDE/*{{{*/

#include <string>
#include <gloox/jid.h>
#include <gloox/presence.h>

#include "../Singleton.h"
#include "Error.h"

/*}}}*/


namespace Control
{
    class Control : public Singleton<Control>
    {
        public:
            //Error initialize(const gloox::JID jid, int port = -1);/*{{{*/

            /** Initialize the connection, the roster, and the control files.
             *
             * @param JID A valid JID.
             * @param port The port on the server to connect to. -1 to use the
             *        default one.
             * @return The return code @ref Error
             */
            Error initialize(const gloox::JID jid, int port = -1);

/*}}}*/
            //bool setPresence(/*{{{*/

            /** Set the presence.
             *
             * @param presence The presence type. @ref
             *        gloox::Presence::PresenceType
             * @param priority The priority ranging from -128 to 127.
             * @param status A message describing the status.
             * @return Whether it was possible to set the presence.
             */
            bool setPresence(
                gloox::Presence::PresenceType presence,
                int priority = 0,
                const std::string &status=gloox::EmptyString);

/*}}}*/
            //int printError(/*{{{*/

            /** Print an error to stderr.
             *
             * @param errorType The return code of the error. @ref Error
             * @param message Additional information some return codes can
             *        have.
             * @return The return code.
             */
            int printError(
                Error errorType,
                std::string message = gloox::EmptyString);

/*}}}*/
            //void handleError(/*{{{*/

            /** Handle an error that occured while sxc is active.
             *
             * @param errorType The return code of the error. @ref Error
             * @param message Additional information some return codes can
             *        have.
             * @param isCritical On true print output to cerr and exit sxc,
             *        else only print to Control::Control::Out
             * @return The return code.
             */
            void handleError(
                Error errorType,
                std::string message = gloox::EmptyString,
                bool isCritical = false);

/*}}}*/

        private:
            //static const std::string outputPrefix;/*{{{*/

            /// The text printed before every output to the console.
            static const std::string outputPrefix;

/*}}}*/
            //static const std::string errorPrefix;/*{{{*/

            /// The text printed before every error output to the console.
            static const std::string errorPrefix;

/*}}}*/
            //gloox::JID jid;/*{{{*/

            /// The JID, stored until the Client is initialized.
            gloox::JID jid;

/*}}}*/
            //Control::Roster roster;/*{{{*/

            /// The roster.
            //Control::Roster roster;

/*}}}*/
            //Control::File::In input;/*{{{*/

            /// The input file.
            //Control::File::In input;

/*}}}*/
            //Control::File::Out output;/*{{{*/

            /// The output file.
            //Control::File::Out output;

/*}}}*/
    };
}


#endif // CONTROL_CONTROL_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

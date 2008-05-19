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
#include <gloox/client.h>

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
             * @warning The parameters won't be checked for validity.
             *
             * @param newJid A valid JID.
             * @param newPort The port on the server to connect to. -1 to use
             *        the default one.
             */
            void initialize(const gloox::JID newJid, int newPort = -1);

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
            //int print(std::string text);/*{{{*/

            /** Print a text to the output file.
             *
             * @param text The raw text to print.
             */
            void print(std::string text);

/*}}}*/
            //int printStdErr(std::string text);/*{{{*/

            /** Print a text to stderr.
             *
             * @param text The raw text to print.
             */
            void printStdErr(std::string text);

/*}}}*/

        private:
            //static const std::string outputPrefix;/*{{{*/

            /// The text printed before every output to the console.
            static const std::string outputPrefix;

/*}}}*/
            //gloox::JID jid;/*{{{*/

            /// The JID, stored until the Client is initialized.
            gloox::JID jid;

/*}}}*/
            //int port;/*{{{*/

            /// The server's port, stored until the Client is initialized.
            int port;

/*}}}*/
            //std::string password;/*{{{*/

            /// The password of the user.
            std::string password;

/*}}}*/
            //gloox::Client client;/*{{{*/

            /// The XMPP client.
            gloox::Client *client;

/*}}}*/
            //Roster roster;/*{{{*/

            /// The roster.
            //Roster roster;

/*}}}*/
            //Control::File::Input input;/*{{{*/

            /// The input file.
            //Control::File::Input input;

/*}}}*/
            //Control::File::Output output;/*{{{*/

            /// The output file.
            //Control::File::Output output;

/*}}}*/
    };
}


#endif // CONTROL_CONTROL_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

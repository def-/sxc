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

#include <sstream>
#include <gloox/jid.h>

#include "Control/Control.h"

/*}}}*/


int main(int argc, char *argv[])/*{{{*/
{
    int port = -2; // Set to undefined.
    gloox::JID jid;

    try {
        if (argc > 4 || argc < 2)
            throw Control::Control::ErrorParametersInvalid;

        for (int i = 1; argv[i]; ++i) {/*{{{*/
            if (std::string(argv[i]) == "-p") {
                if (port >= -1) // The port can only be specified once.
                    throw Control::Control::ErrorParametersInvalid;
                if (!argv[++i])
                    throw Control::Control::ErrorPortUnspecified;

                std::istringstream instream;
                instream.str(std::string(argv[i]));
                if (!(instream >> port) // Specified port is no integer.
                || port < -1 // Explicitly use default port.
                || port > 65535)
                    throw Control::Control::ErrorPortInvalid;
            } else if (argv[i][0] == '-')
                throw Control::Control::ErrorParametersInvalid;
            // The JID can only be specified once.
            else if (jid.username().empty()) {
                if (!jid.setJID(argv[i]) || jid.username().empty())
                    throw Control::Control::ErrorJidInvalid;
            } else
                throw Control::Control::ErrorParametersInvalid;
        }/*}}}*/

        if (port == -2) port = -1; // Port was not set by parameter.
            throw Control::Control::getInstance().initialize(jid, port);
    } catch (const Control::Control::Error returnCode) {
        return Control::Control::getInstance().printError(returnCode, argv[0]);
    }
}/*}}}*/

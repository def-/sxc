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

#include <iostream>

#include "Control.h"

/*}}}*/


namespace Control
{
    const std::string Control::outputPrefix = "sxc: ";

    const std::string Control::errorPrefix = outputPrefix + "Error: ";


    Control::Error Control::initialize(const gloox::JID jid, int port)/*{{{*/
    {
        return ErrorNoError;
    }/*}}}*/

    bool Control::setPresence(/*{{{*/
        gloox::Presence::PresenceType presence,
        int priority,
        const std::string &status)
    {
        //if (client.presence
    }/*}}}*/

    int Control::printError(/*{{{*/
        Error returnCode,
        const std::string text)
    {
        std::string errorOutput = "";

        switch (returnCode) {
        case Control::ErrorNoError:
            break;

        case Control::ErrorParametersInvalid:
            std::cerr
                << outputPrefix << "Usage: " << text /* filename */
                << " jid [-p port]" << std::endl
                << outputPrefix << "JID: node@domain[/resource]" << std::endl
                << outputPrefix << "Port: 0 - 65535 or -1 for default"
                << std::endl;
            errorOutput = "Invalid parameters.";
            break;

        case Control::ErrorPortUnspecified:
            errorOutput = "No port specified.";
            break;

        case Control::ErrorPortInvalid:
            errorOutput = "Invalid port specified.";
            break;

        case Control::ErrorJidInvalid:
            errorOutput = "Invalid JID specified.";
            break;

        default: // An unknown error occured.
            errorOutput = "Unknown error.";
        }

        if (!errorOutput.empty())
            std::cerr << errorPrefix << errorOutput << std::endl;

        return returnCode;
    }/*}}}*/
}

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


    Control::ReturnCode Control::initialize(const gloox::JID jid, int port)/*{{{*/
    {
        return ReturnOk;
    }/*}}}*/

    bool Control::setPresence(/*{{{*/
        gloox::Presence::PresenceType presence,
        int priority,
        const std::string &status)
    {
        //if (client.presence
    }/*}}}*/

    int Control::printError(/*{{{*/
        ReturnCode returnCode,
        const std::string text)
    {
        std::string errorOutput = "";

        switch (returnCode) {
        case Control::ReturnParametersInvalid:
            std::cerr
                << outputPrefix << "Usage: " << text /* filename */
                << " jid [-p port]" << std::endl
                << outputPrefix << "JID: node@domain[/resource]" << std::endl
                << outputPrefix << "Port: 0 - 65535 or -1 for default"
                << std::endl;
            errorOutput = "Invalid parameters.";
            break;

        case Control::ReturnPortUnspecified:
            errorOutput = "No port specified.";
            break;

        case Control::ReturnPortInvalid:
            errorOutput = "Invalid port specified.";
            break;

        case Control::ReturnJidInvalid:
            errorOutput = "Invalid JID specified.";
            break;
        }

        if (!errorOutput.empty())
            std::cerr << errorPrefix << errorOutput << std::endl;

        return returnCode;
    }/*}}}*/
}

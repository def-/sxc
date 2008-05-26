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

#include "Error.h"
#include "Control.h"

/*}}}*/


namespace Control
{
    const std::string Error::outputPrefix = "Error: ";
    const std::string Error::outputDebugPrefix = "Debug: ";

    Error::Error(/*{{{*/
        Type errorType,
        std::string message,
        Severity severity)
    {
        switch (severity) {
        case SeverityNormal:
            Control::getInstance().print(
                outputPrefix + format(errorType, message));
            break;

        case SeverityCritical: {
            if (errorType == ErrorParametersInvalid) {
                Control::getInstance().printStdErr(
                    "Usage: " + message /* Filename */ + " jid [-p port]");
                Control::getInstance().printStdErr(
                    "JID: node@domain[/resource]");
                Control::getInstance().printStdErr(
                    "Port: 0 - 65535 or -1 for default");
            }

            const std::string errorOutput = format(errorType, message);

            if (!errorOutput.empty())
                Control::getInstance().printStdErr(outputPrefix + errorOutput);

            exit(errorType);
            break;
        }

        case SeverityDebug:
            Control::getInstance().printStdErr(outputDebugPrefix + message);
            break;
        }
    }/*}}}*/

    const std::string Error::format(/*{{{*/
        Type errorType,
        std::string message)
    {
        switch (errorType) {
        case ErrorNoError:
            return "";
            break;

        case ErrorParametersInvalid:
            return "Invalid parameters.";
            break;

        case ErrorPortInvalid:
            return "Invalid port specified.";
            break;

        case ErrorJidInvalid:
            return "Invalid JID specified.";
            break;

        default: // An unknown error occured.
            return "Unknown error.";
        }
    }/*}}}*/
}
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

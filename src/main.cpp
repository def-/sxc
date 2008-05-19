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
#include "Control/Error.h"

/*}}}*/

/**
 * @file main.cpp
 * @author Dennis Felsing
 * @brief The starting point of sxc.
 *
 * Parse the parameters the program was started with and then initialize the
 * @ref Control::Control.
 */

int main(int argc, char *argv[])/*{{{*/
{
    int port = -2; // Set to undefined.
    gloox::JID jid;

    try {
        if (argc > 4 || argc < 2)
            throw Control::Error::ErrorParametersInvalid;

        // Parsing arguments./*{{{*/
        for (int i = 1; argv[i]; ++i) {
            if (std::string(argv[i]) == "-p") {
                if (port >= -1) // The port can only be specified once.
                    throw Control::Error::ErrorParametersInvalid;
                if (!argv[++i])
                    throw Control::Error::ErrorPortInvalid;

                std::istringstream instream;
                instream.str(std::string(argv[i]));
                instream >> port;

                if (instream.bad() // Specified port is no integer.
                || !instream.eof() // Port doesn't end after integer.
                || port < -1       // Allow to explicitely use default port.
                || port > 65535)
                    throw Control::Error::ErrorPortInvalid;
            } else if (argv[i][0] == '-') { // No other parameters.
                throw Control::Error::ErrorParametersInvalid;
            // The JID can only be specified once.
            } else if (jid.username().empty()) {
                if (!jid.setJID(argv[i]) || jid.username().empty())
                    throw Control::Error::ErrorJidInvalid;
            } else {
                throw Control::Error::ErrorParametersInvalid;
            }
        }/*}}}*/

        // Port was not set by parameter, use the default one.
        if (port == -2) port = -1;

        Control::Control::getInstance().initialize(jid, port);
        pause(); // Run forever (until a signal is received).
    } catch (const Control::Error::Type e) {
        Control::Error(e, argv[0], Control::Error::SeverityCritical);
    }
}/*}}}*/
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

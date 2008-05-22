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
#include <gloox/jid.h>
#include <gloox/presence.h>

#include "Control.h"

/*}}}*/


namespace Control
{
    const std::string Control::outputPrefix = "sxc: ";


    void Control::initialize(const gloox::JID newJid, int newPort)/*{{{*/
    {
        jid = newJid;
        port = newPort;

        //output = File::Output(jid.bare());
        //input = File::Input(jid.bare());
    }/*}}}*/

    bool Control::setPresence(/*{{{*/
        gloox::Presence::PresenceType presence,
        int priority,
        const std::string &status)
    {
        if (!client)
            // TODO: delete
            client = new gloox::Client(jid, password, port);
        //if (client.presence
    }/*}}}*/

    void Control::print(std::string text)/*{{{*/
    {
        //output.write(text);
    }/*}}}*/

    void Control::printStdErr(std::string text)/*{{{*/
    {
        std::cerr << outputPrefix << text << std::endl;
    }/*}}}*/
}
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

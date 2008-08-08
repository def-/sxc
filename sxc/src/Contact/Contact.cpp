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

#include <gloox/clientbase.h>
#include <gloox/messagesession.h>

#include <Contact/Contact.h>

/*}}}*/


namespace Contact
{
    Contact::Contact(gloox::ClientBase *client, const gloox::JID jid)/*{{{*/
    {
        _session = new gloox::MessageSession(client, jid);
        _session->registerMessageHandler(this);

        //_input = new File::Input(jid.bare());
        //_output = new File::Output(jid.bare());
    }/*}}}*/

    Contact::~Contact()/*{{{*/
    {
        delete _session;
    }/*}}}*/

    void Contact::handleMessage(/*{{{*/
        const gloox::Message &msg,
        gloox::MessageSession *session)
    {
        //_output->write(msg->body());
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

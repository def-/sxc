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

#include <string>

#include <gloox/clientbase.h>
#include <gloox/messagesession.h>
#include <gloox/presence.h>

#include <Contact/Contact.hxx>

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#endif

#ifdef DEBUG
#   include <sstream>

#   include <libsxc/generateString.hxx>

#   include <print.hxx>
#endif

/*}}}*/


namespace Contact
{
    Contact::Contact(gloox::ClientBase *client, const gloox::JID &jid)/*{{{*/
    : _client(client),
      _session(new gloox::MessageSession(client, jid))
    {
#       ifdef DEBUG
            printErr("Create contact: \"" + jid.bare() + "\".");
#       endif
        _session->registerMessageHandler(this);

        //_input = new File::Input(jid.bare());
        //_output = new File::Output(jid.bare());
    }/*}}}*/
    Contact::~Contact()/*{{{*/
    {
#       ifdef DEBUG
            printErr("Delete contact: \"" + _session->target().bare() + "\".");
#       endif
        // This deletes the session. Else the destructor of gloox::ClientBase
        // would handle this.
        _client->disposeMessageSession(_session);
    }/*}}}*/

    void Contact::printPresenceUpdate(
        const std::string &resource,
        gloox::Presence::PresenceType presence,
        const std::string &message)
    {
        // FIXME
    }
    void Contact::handleMessage(/*{{{*/
        const gloox::Message &msg,
        gloox::MessageSession *session)
    {
#       ifdef DEBUG
            std::ostringstream ss;
            ss << "Contact received message: (jid: \"" << msg.from().full();
            if (session)
                ss << "\", thread id: \"" << session->threadID() << "\"";
            else
                ss << "\", no session";
            ss << ", type: \"" << libsxc::genMsgTypeString(msg.subtype());
            ss << "\" (" << msg.subtype();
            ss << "), subject: \"" << msg.subject();
            ss << "\", body: \"" << msg.body() << "\").";
            printLog(ss.str());
#       endif
        //_output->write(msg->body());
    }/*}}}*/
    const gloox::JID Contact::getJid()/*{{{*/
    {
        return _session->target();
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright (C) 2008 Dennis Felsing, Andreas Waidler

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*}}}*/


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

  void Contact::printPresenceUpdate(/*{{{*/
    const std::string &resource,
    gloox::Presence::PresenceType presence,
    const std::string &message)
  {
    // FIXME
  }/*}}}*/
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
  const gloox::JID &Contact::getJid()/*{{{*/
  {
    return _session->target();
  }/*}}}*/
  void Contact::sendMessage(const std::string &message)/*{{{*/
  {
    // FIXME
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

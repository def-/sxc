#line 2 "sxc:Contact/Contact.cxx"
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
#include <sstream>

#include <gloox/clientbase.h>
#include <gloox/messagesession.h>
#include <gloox/presence.h>

#include <Contact/Contact.hxx>
#include <Account/Roster.hxx>

#include <libsxc/generateString.hxx>

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <libsxc/Debug/Logger.hxx>

/*}}}*/

namespace Contact
{
  Contact::Contact(Account::Roster &roster, const gloox::JID &jid, ::File::AbcOutput &out)/*{{{*/
  : _roster(roster)
  , _session(roster.createMessageSession(this, jid))
  , _out(out)
  // FIXME: Files
  {
    LOG2("Create contact: \"" + jid.bare() + "\".");

    //_session->registerMessageHandler(this);
  }/*}}}*/
  Contact::~Contact()/*{{{*/
  {
    LOG2("Delete contact: \"" + _session->target().bare() + "\".");

    // This deletes the session. Else the destructor of gloox::ClientBase
    // would handle this.
    //_client->disposeMessageSession(_session);
    _roster.disposeMessageSession(_session);

    delete &_out;
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
    LOG2(ss.str());

    //_output->write(msg->body());
  }/*}}}*/
  const gloox::JID &Contact::getJid()/*{{{*/
  {
    return _session->target();
  }/*}}}*/

  void Contact::sendMessage(const std::string &message)/*{{{*/
  {
    _roster.sendMessage(getJid(), message);
  }/*}}}*/
  void Contact::add()/*{{{*/
  {
    _roster.addContact(getJid(), /* isPermanent = */ true);
  }/*}}}*/
  void Contact::remove()/*{{{*/
  {
    _roster.removeContact(getJid());
  }/*}}}*/
  void Contact::subscribe(const std::string &message)/*{{{*/
  {
    _roster.subscribe(getJid(), message);
  }/*}}}*/
  void Contact::unsubscribe(const std::string &message)/*{{{*/
  {
    _roster.unsubscribe(getJid(), message);
  }/*}}}*/
  void Contact::acknowledgeSubscription()/*{{{*/
  {
    _roster.acknowledgeSubscription(getJid());
  }/*}}}*/
  void Contact::declineSubscription()/*{{{*/
  {
    _roster.declineSubscription(getJid());
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

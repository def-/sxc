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

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <string>
#include <sstream>

#include <gloox/clientbase.h>
#include <gloox/messagesession.h>
#include <gloox/presence.h>

#include <Contact/Contact.hxx>
#include <Account/Roster.hxx>

#include <libsxc/generateString.hxx>
#include <libsxc/Debug/Logger.hxx>

/*}}}*/

namespace Contact
{
  Contact::Contact(/*{{{*/
    Account::Roster &roster,
    const gloox::JID &accountJid,
    const gloox::JID &contactJid)
  : _roster(roster)
  , _session(roster.createMessageSession(this, contactJid))
  , _in(*this, accountJid.bare(), contactJid.bare())
  , _out(accountJid.bare(), contactJid.bare())
  , _nfo(accountJid.bare(), contactJid.bare())
  {
    LOG("Create contact: \"" + contactJid.bare() + "\".");

    _in.listen();
  }/*}}}*/
  Contact::~Contact()/*{{{*/
  {
    LOG("Delete contact: \"" + _session->target().bare() + "\".");

    _roster.disposeMessageSession(_session); // Will be deleted.
  }/*}}}*/

  void Contact::updatePresence(/*{{{*/
    const std::string &resource,
    gloox::Presence::PresenceType presence,
    const std::string &message)
  {
    _nfo.setPresence(presence);
    _nfo.setMessage(message);
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
    LOG(ss.str());

    _out.writeIncomming(msg.body());
  }/*}}}*/

  void Contact::sendMessage(const std::string &message)/*{{{*/
  {
    LOG("Sending message: \"" + message + "\"");
    _session->send(message);
    _out.writeOutgoing(message);
  }/*}}}*/
  void Contact::add()/*{{{*/
  {
    _roster.addContact(_getJid());
  }/*}}}*/
  void Contact::remove()/*{{{*/
  {
    _roster.removeContact(_getJid());
  }/*}}}*/
  void Contact::subscribe(const std::string &message)/*{{{*/
  {
    _roster.subscribe(_getJid(), message);
  }/*}}}*/
  void Contact::unsubscribe(const std::string &message)/*{{{*/
  {
    _roster.unsubscribe(_getJid(), message);
  }/*}}}*/
  void Contact::acknowledgeSubscription()/*{{{*/
  {
    _roster.acknowledgeSubscription(_getJid());
  }/*}}}*/
  void Contact::declineSubscription()/*{{{*/
  {
    _roster.declineSubscription(_getJid());
  }/*}}}*/
  const gloox::JID &Contact::_getJid()/*{{{*/
  {
    return _session->target();
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

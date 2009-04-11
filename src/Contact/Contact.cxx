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
#include <gloox/delayeddelivery.h>
#include <gloox/gloox.h>
#include <gloox/error.h>

#include <Contact/Contact.hxx>
#include <Account/Roster.hxx>
#include <Account/RosterType.hxx>
#include <File/AbcOutput.hxx>

#include <libsxc/generateString.hxx>
#include <libsxc/Debug/Logger.hxx>

/*}}}*/

namespace Contact
{
  Contact::Contact(/*{{{*/
    Account::Roster &roster,
    ::File::AbcOutput &accountOut,
    const gloox::JID &accountJid,
    const gloox::JID &contactJid)
  : _roster(roster)
  , _session(roster.createMessageSession(this, contactJid))
  , _accountOut(accountOut)
  , _in(*this, accountJid.bare(), contactJid.bare())
  , _out(accountJid.bare(), contactJid.bare())
  , _nfo(accountJid.bare(), contactJid.bare())
  , _sub(gloox::S10nNone)
  , _subSet(false)
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
  void Contact::updateRoster(Account::RosterType type)/*{{{*/
  {
    _nfo.setRoster(type);
  }/*}}}*/
  gloox::SubscriptionType Contact::updateSub(/*{{{*/
    gloox::SubscriptionType type)
  {
    _nfo.setSub(type);

    gloox::SubscriptionType ret;
    if (_subSet) {
      ret = _sub;
    } else {
      ret = type;
      _subSet = true;
    }
    _sub = type;
    return ret;
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
    ss << "\", body: \"" << msg.body();
    if (msg.error()) {
      ss << "\", error: \""
         << libsxc::genStanzaErrorString(msg.error()->error())
         << "\", error text: \"" << msg.error()->text();

    }
    ss << "\").";
    LOG(ss.str());

    if (gloox::Message::Error == msg.subtype() || msg.error()) {
      std::string text =  "Error occured: " + msg.from().bare() +
        "\nMessage: " + msg.body();
      if (msg.error()) {
        text += "\nError: " +
          libsxc::genStanzaErrorString(msg.error()->error()) +
          "\nText: " + msg.error()->text();
      } else {
        text += "\nError: \nText: ";
      }
      _accountOut.write(text);
    } else if (gloox::Message::Invalid == msg.subtype()) {
      LOG("Invalid message received, ignoring.");
    } else if (msg.when()) {
      LOG("Delayed delivery: " + msg.when()->stamp());

      // FIXME: _out.writeIncomming(msg.body(), msg.when()->stamp());
      _out.writeIncomming(msg.body());
    } else {
      _out.writeIncomming(msg.body());
    }
  }/*}}}*/

  void Contact::sendMessage(const std::string &message)/*{{{*/
  {
    LOG("Sending message: \"" + message + "\"");
    _session->send(message);
    // FIXME: Find out if connection is still stable. Should work, as send is
    // blocking. Get from Roster.
    _out.writeOutgoing(message);
  }/*}}}*/
  void Contact::remove()/*{{{*/
  {
    _nfo.remove();
  }/*}}}*/
  bool Contact::isNew()/*{{{*/
  {
    return _nfo.isNew();
  }/*}}}*/
  const gloox::JID &Contact::_getJid()/*{{{*/
  {
    return _session->target();
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

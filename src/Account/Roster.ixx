#line 2 "sxc:Account/Roster.ixx"
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
#include <map>
#include <sstream>

#include <gloox/clientbase.h>
#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/iq.h>
#include <gloox/message.h>
#include <gloox/messagesession.h>
#include <gloox/messagehandler.h>

#include <libsxc/generateString.hxx>
#include <libsxc/Exception/GlooxException.hxx>

#include <Account/Account.hxx>

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <libsxc/Debug/Logger.hxx>

/*}}}*/

namespace Account
{
  template <class Entry> Roster<Entry>::Roster(Account *account, gloox::Client *client)/*{{{*/
  : RosterListener(),
    _account(account),
    _client(client),
    _contacts()
  {
    // Asynchronous subscription request handling.
    _client->rosterManager()->registerRosterListener(this, false);
  }/*}}}*/
  template <class Entry> Roster<Entry>::~Roster()/*{{{*/
  {
    _client->rosterManager()->removeRosterListener();

    for(
    typename contactList<Entry>::Type::iterator entry = _contacts.begin();
    entry != _contacts.end();
    ++entry) {
      delete entry->second;
    }
  }/*}}}*/

  template <class Entry> void Roster<Entry>::sendMessage(const gloox::JID &jid, const std::string &message)/*{{{*/
  {
    // FIXME
  }/*}}}*/

  template <class Entry> void Roster<Entry>::addContact(/*{{{*/
    const gloox::JID &jid,
    bool isPermanent)
  {
    _addContactLocal(jid);
    if (isPermanent)
      _addContactRemote(jid);
  }/*}}}*/
  template <class Entry> void Roster<Entry>::removeContact(const gloox::JID &jid) const/*{{{*/
  {
    _checkClient();

    LOG2("Remove contact from the roster: \"" + jid.bare() + "\".");

    _client->rosterManager()->remove(jid);
    _client->rosterManager()->synchronize();
  }/*}}}*/

  template <class Entry> void Roster<Entry>::subscribe(/*{{{*/
    const gloox::JID &jid,
    const std::string &message) const
  {
    _checkClient();

    LOG2(
      "Sending subscription request: (jid: \"" + jid.bare() +
      "\", message: \"" + message + "\").");

    const gloox::StringList groups;
    _client->rosterManager()->subscribe(jid, jid.bare(), groups, message);
    _client->rosterManager()->synchronize();
  }/*}}}*/
  template <class Entry> void Roster<Entry>::unsubscribe(/*{{{*/
    const gloox::JID &jid,
    const std::string &message) const
  {
    _checkClient();

    LOG2(
      "Sending unsubscription request: (jid: \"" + jid.bare() +
      "\", message: \"" + message + "\").");

    _client->rosterManager()->unsubscribe(jid, message);
    _client->rosterManager()->synchronize();
  }/*}}}*/

  template <class Entry> void Roster<Entry>::acknowledgeSubscription(const gloox::JID &jid) const/*{{{*/
  {
    LOG2(
      "Acknowledge subscription request: \"" + jid.bare() + "\".");

    _client->rosterManager()->ackSubscriptionRequest(jid, true);
  }/*}}}*/
  template <class Entry> void Roster<Entry>::declineSubscription(const gloox::JID &jid) const/*{{{*/
  {
    LOG2(
      "Decline subscription request: \"" + jid.bare() + "\".");

    _client->rosterManager()->ackSubscriptionRequest(jid, false);
  }/*}}}*/

  template <class Entry> void Roster<Entry>::handleMessage(/*{{{*/
    const gloox::Message &msg,
    gloox::MessageSession *session)
  {
    addContact(msg.from(), false); // Local only.

    typename contactList<Entry>::Type::iterator contact = _getContact(msg.from().bare());
    if (_contacts.end() == contact)
      return;

    contact->second->handleMessage(msg, session);
  }/*}}}*/

  template <class Entry> gloox::MessageSession *Roster<Entry>::createMessageSession(/*{{{*/
    gloox::MessageHandler *handler,
    const gloox::JID &jid)
  {
    gloox::MessageSession *session = new gloox::MessageSession(_client, jid);
    session->registerMessageHandler(handler);
    return session;
  }/*}}}*/
  template <class Entry> void Roster<Entry>::disposeMessageSession(gloox::MessageSession *session)/*{{{*/
  {
    _client->disposeMessageSession(session);
  }/*}}}*/

  template <class Entry> void Roster<Entry>::handleItemAdded(const gloox::JID &jid)/*{{{*/
  {
    LOG2("Item added to the roster: \"" + jid.bare() + "\".");

    _addContactLocal(jid);
  }/*}}}*/
  template <class Entry> void Roster<Entry>::handleItemSubscribed(const gloox::JID &jid)/*{{{*/
  {
    LOG2("Item subscribed: \"" + jid.bare() + "\".");
  }/*}}}*/
  template <class Entry> void Roster<Entry>::handleItemRemoved(const gloox::JID &jid)/*{{{*/
  {
    LOG2("Item removed from the roster: \"" + jid.bare() + "\".");

    typename contactList<Entry>::Type::iterator contact = _getContact(jid.bare());
    if (_contacts.end() == contact)
      return;
    delete contact->second;
    _contacts.erase(contact);

    _account->print("Contact removed: \"" + jid.bare() + "\".");
  }/*}}}*/
  template <class Entry> void Roster<Entry>::handleItemUpdated(const gloox::JID &jid)/*{{{*/
  {
    LOG2("Item updated: \"" + jid.bare() + "\".");
  }/*}}}*/
  template <class Entry> void Roster<Entry>::handleItemUnsubscribed(const gloox::JID &jid)/*{{{*/
  {
    LOG2(
      "Item unsubscribed: \"" + jid.bare() + "\".");
  }/*}}}*/
  template <class Entry> void Roster<Entry>::handleRoster(const gloox::Roster &roster)/*{{{*/
  {
    LOG2("Initial roster received from the server.");

    for(
    gloox::Roster::const_iterator entry = roster.begin();
    entry != roster.end();
    ++entry) {
      _addContactLocal(entry->first);
    }
  }/*}}}*/
  template <class Entry> void Roster<Entry>::handleRosterPresence(/*{{{*/
    const gloox::RosterItem &item,
    const std::string &resource,
    gloox::Presence::PresenceType presence,
    const std::string &msg)
  {
    std::ostringstream ss;
    ss << "Status changed: (jid: \"" << item.jid()
       << "/" << resource << "\", presence: \""
       << libsxc::genPresenceString(presence) << "\" (" << presence
       << "), message: \"" << msg << "\").";
    LOG2(ss.str());

    typename contactList<Entry>::Type::iterator contact = _getContact(item.jid());
    if (_contacts.end() == contact)
      return;
    contact->second->printPresenceUpdate(resource, presence, msg);
  }/*}}}*/
  template <class Entry> void Roster<Entry>::handleSelfPresence(/*{{{*/
    const gloox::RosterItem &item,
    const std::string &resource,
    gloox::Presence::PresenceType presence,
    const std::string &msg)
  {
    std::ostringstream ss;
    ss << "Self-status changed: (jid: \"" << item.name()
       << "\", resource: \"" << resource << "\", presence: "
       << presence << ", message: \"" << msg << "\").";
    LOG2(ss.str());
  }/*}}}*/
  template <class Entry> bool Roster<Entry>::handleSubscriptionRequest(/*{{{*/
    const gloox::JID &jid,
    const std::string &msg)
  {
    LOG2(
      "Received subscription request: (jid: \"" + jid.bare() +
      "\", message: \"" + msg + "\").");

    typename contactList<Entry>::Type::iterator contact = _getContact(jid.bare());
    if (_contacts.end() == contact)
      return true;

    _account->print(
      "Subscription request received: \"" + jid.bare() + "\"");

    return true;
  }/*}}}*/
  template <class Entry> bool Roster<Entry>::handleUnsubscriptionRequest(/*{{{*/
    const gloox::JID &jid,
    const std::string &msg)
  {
    LOG2(
      "Received unsubscription request: (jid: \"" + jid.bare() +
      "\", message: \"" + msg + "\").");

    typename contactList<Entry>::Type::iterator contact = _getContact(jid.bare());
    if (_contacts.end() == contact)
      return true;

    _account->print(
      "Unsubscription request received: \"" + jid.bare() + "\"");

    return true;
  }/*}}}*/
  template <class Entry> void Roster<Entry>::handleNonrosterPresence(const gloox::Presence &presence)/*{{{*/
  {
    std::ostringstream ss;
    ss << "Nonroster-Status changed: (type: \"" << presence.subtype()
       << "\", message: \"" << presence.status() << "\").";
    LOG2(ss.str());
  }/*}}}*/
  template <class Entry> void Roster<Entry>::handleRosterError(const gloox::IQ &iq)/*{{{*/
  {
    const gloox::Error *error = iq.error();
    if (error)
      LOG2(
        "Roster error received: " +
        libsxc::genStanzaErrorString(error->error()));

    // FIXME: Use handleError
    if (error)
      _account->print(
        "Roster error received: " +
        libsxc::genStanzaErrorString(error->error()));
  }/*}}}*/

  template <class Entry> void Roster<Entry>::_checkClient() const/*{{{*/
  {
    if (!gloox::StateConnected == _client->state())
      throw libsxc::Exception::GlooxException(
        libsxc::Exception::InvalidUsage,
        "Connection ist not established.");
  }/*}}}*/
  template <class Entry> void Roster<Entry>::_addContactRemote(const gloox::JID &jid) const/*{{{*/
  {
    LOG2(
      "Add contact to the remote roster: \"" + jid.bare() + "\".");

    _checkClient();

    const gloox::StringList groups;
    _client->rosterManager()->add(jid, jid.bare(), groups);
    _client->rosterManager()->synchronize();
  }/*}}}*/
  template <class Entry> void Roster<Entry>::_addContactLocal(const gloox::JID &jid)/*{{{*/
  {
    LOG2(
      "Add contact to the local roster: \"" + jid.bare() + "\".");

    if (_contacts.end() != _getContact(jid.bare())) {
      LOG2("Contact already in local roster, not adding.");
      return;
    }

    _contacts.insert(std::make_pair(
      jid.bare(),
      new Entry(*this, jid)));
  }/*}}}*/
  template <class Entry> typename contactList<Entry>::Type::iterator Roster<Entry>::_getContact(const std::string &jid)/*{{{*/
  {
    typename contactList<Entry>::Type::iterator contact = _contacts.find(jid);

    if (_contacts.end() == contact) {
      LOG2("Item not found in local roster");
    }

    return contact;
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

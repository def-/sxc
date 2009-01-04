#line 2 "sxc:Account/Roster.cxx"
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
#include <gloox/messagehandler.h>
#include <gloox/error.h>

#include <libsxc/generateString.hxx>
#include <libsxc/Exception/GlooxException.hxx>

#include <Account/Roster.hxx>
#include <Contact/Contact.hxx>
#include <Contact/File/Output.hxx>
#include <File/AbcOutput.hxx>

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <libsxc/Debug/Logger.hxx>

/*}}}*/

namespace Account
{
  Roster::Roster(gloox::Client &client, ::File::AbcOutput &out)/*{{{*/
  : RosterListener()
  , _client(client)
  , _out(out)
  , _contacts()
  {
    // Asynchronous subscription request handling.
    _client.rosterManager()->registerRosterListener(this, false);
  }/*}}}*/
  Roster::~Roster()/*{{{*/
  {
    _client.rosterManager()->removeRosterListener();

    for(
    contactList::iterator entry = _contacts.begin();
    entry != _contacts.end();
    ++entry) {
      delete entry->second;
    }
  }/*}}}*/

  void Roster::sendMessage(const gloox::JID &jid, const std::string &message)/*{{{*/
  {
    // FIXME
  }/*}}}*/

  void Roster::addContact(/*{{{*/
    const gloox::JID &jid,
    bool isPermanent)
  {
    _addContactLocal(jid);
    if (isPermanent)
      _addContactRemote(jid);
  }/*}}}*/
  void Roster::removeContact(const gloox::JID &jid) const/*{{{*/
  {
    _checkClient();

    LOG2("Remove contact from the roster: \"" + jid.bare() + "\".");

    _client.rosterManager()->remove(jid);
    _client.rosterManager()->synchronize();
  }/*}}}*/

  void Roster::subscribe(/*{{{*/
    const gloox::JID &jid,
    const std::string &message) const
  {
    _checkClient();

    LOG2(
      "Sending subscription request: (jid: \"" + jid.bare() +
      "\", message: \"" + message + "\").");

    const gloox::StringList groups;
    _client.rosterManager()->subscribe(jid, jid.bare(), groups, message);
    _client.rosterManager()->synchronize();
  }/*}}}*/
  void Roster::unsubscribe(/*{{{*/
    const gloox::JID &jid,
    const std::string &message) const
  {
    _checkClient();

    LOG2(
      "Sending unsubscription request: (jid: \"" + jid.bare() +
      "\", message: \"" + message + "\").");

    _client.rosterManager()->unsubscribe(jid, message);
    _client.rosterManager()->synchronize();
  }/*}}}*/

  void Roster::acknowledgeSubscription(const gloox::JID &jid) const/*{{{*/
  {
    LOG2(
      "Acknowledge subscription request: \"" + jid.bare() + "\".");

    _client.rosterManager()->ackSubscriptionRequest(jid, true);
  }/*}}}*/
  void Roster::declineSubscription(const gloox::JID &jid) const/*{{{*/
  {
    LOG2(
      "Decline subscription request: \"" + jid.bare() + "\".");

    _client.rosterManager()->ackSubscriptionRequest(jid, false);
  }/*}}}*/

  void Roster::handleMessage(/*{{{*/
    const gloox::Message &msg,
    gloox::MessageSession *session)
  {
    addContact(msg.from(), false); // Local only.

    contactList::iterator contact = _getContact(msg.from().bare());
    if (_contacts.end() == contact)
      return;

    contact->second->handleMessage(msg, session);
  }/*}}}*/

  gloox::MessageSession *Roster::createMessageSession(/*{{{*/
    gloox::MessageHandler *handler,
    const gloox::JID &jid)
  {
    gloox::MessageSession *session = new gloox::MessageSession(&_client, jid);
    session->registerMessageHandler(handler);
    return session;
  }/*}}}*/
  void Roster::disposeMessageSession(gloox::MessageSession *session)/*{{{*/
  {
    _client.disposeMessageSession(session);
  }/*}}}*/

  const gloox::JID &Roster::getJid()/*{{{*/
  {
    return _client.jid();
  }/*}}}*/

  void Roster::handleItemAdded(const gloox::JID &jid)/*{{{*/
  {
    LOG2("Item added to the roster: \"" + jid.bare() + "\".");

    _addContactLocal(jid);
  }/*}}}*/
  void Roster::handleItemSubscribed(const gloox::JID &jid)/*{{{*/
  {
    LOG2("Item subscribed: \"" + jid.bare() + "\".");
  }/*}}}*/
  void Roster::handleItemRemoved(const gloox::JID &jid)/*{{{*/
  {
    LOG2("Item removed from the roster: \"" + jid.bare() + "\".");

    contactList::iterator contact = _getContact(jid.bare());
    if (_contacts.end() == contact)
      return;
    delete contact->second;
    _contacts.erase(contact);

    // _account->print("Contact removed: \"" + jid.bare() + "\".");
  }/*}}}*/
  void Roster::handleItemUpdated(const gloox::JID &jid)/*{{{*/
  {
    LOG2("Item updated: \"" + jid.bare() + "\".");
  }/*}}}*/
  void Roster::handleItemUnsubscribed(const gloox::JID &jid)/*{{{*/
  {
    LOG2(
      "Item unsubscribed: \"" + jid.bare() + "\".");
  }/*}}}*/
  void Roster::handleRoster(const gloox::Roster &roster)/*{{{*/
  {
    LOG2("Initial roster received from the server.");

    for(
    gloox::Roster::const_iterator entry = roster.begin();
    entry != roster.end();
    ++entry) {
      _addContactLocal(entry->first);
    }
  }/*}}}*/
  void Roster::handleRosterPresence(/*{{{*/
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

    contactList::iterator contact = _getContact(item.jid());
    if (_contacts.end() == contact)
      return;
    contact->second->printPresenceUpdate(resource, presence, msg);
  }/*}}}*/
  void Roster::handleSelfPresence(/*{{{*/
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
  bool Roster::handleSubscriptionRequest(/*{{{*/
    const gloox::JID &jid,
    const std::string &msg)
  {
    LOG2(
      "Received subscription request: (jid: \"" + jid.bare() +
      "\", message: \"" + msg + "\").");

    contactList::iterator contact = _getContact(jid.bare());
    if (_contacts.end() == contact)
      return true;

    //_account->print(
    //  "Subscription request received: \"" + jid.bare() + "\"");

    return true;
  }/*}}}*/
  bool Roster::handleUnsubscriptionRequest(/*{{{*/
    const gloox::JID &jid,
    const std::string &msg)
  {
    LOG2(
      "Received unsubscription request: (jid: \"" + jid.bare() +
      "\", message: \"" + msg + "\").");

    contactList::iterator contact = _getContact(jid.bare());
    if (_contacts.end() == contact)
      return true;

    //_account->print(
    //  "Unsubscription request received: \"" + jid.bare() + "\"");

    return true;
  }/*}}}*/
  void Roster::handleNonrosterPresence(const gloox::Presence &presence)/*{{{*/
  {
    std::ostringstream ss;
    ss << "Nonroster-Status changed: (type: \"" << presence.subtype()
       << "\", message: \"" << presence.status() << "\").";
    LOG2(ss.str());
  }/*}}}*/
  void Roster::handleRosterError(const gloox::IQ &iq)/*{{{*/
  {
    const gloox::Error *error = iq.error();
    if (error)
      LOG2(
        "Roster error received: " +
        libsxc::genStanzaErrorString(error->error()));

    // FIXME: Use handleError
    //if (error)
    //  _account->print(
    //    "Roster error received: " +
    //    libsxc::genStanzaErrorString(error->error()));
  }/*}}}*/

  void Roster::_checkClient() const/*{{{*/
  {
    if (!gloox::StateConnected == _client.state())
      throw libsxc::Exception::GlooxException(
        libsxc::Exception::InvalidUsage,
        "Connection ist not established.");
  }/*}}}*/
  void Roster::_addContactRemote(const gloox::JID &jid) const/*{{{*/
  {
    LOG2(
      "Add contact to the remote roster: \"" + jid.bare() + "\".");

    _checkClient();

    const gloox::StringList groups;
    _client.rosterManager()->add(jid, jid.bare(), groups);
    _client.rosterManager()->synchronize();
  }/*}}}*/
  void Roster::_addContactLocal(const gloox::JID &jid)/*{{{*/
  {
    LOG2(
      "Add contact to the local roster: \"" + jid.bare() + "\".");

    if (_contacts.end() != _getContact(jid.bare())) {
      LOG2("Contact already in local roster, not adding.");
      return;
    }

    //Contact::File::Output out(_client.jid().bare(), jid.bare());
    _contacts.insert(std::make_pair(
      jid.bare(),
      new Contact::Contact(
        *this,
        jid,
        *(new Contact::File::Output(_client.jid().bare(), jid.bare())))));
  }/*}}}*/
  contactList::iterator Roster::_getContact(const std::string &jid)/*{{{*/
  {
    contactList::iterator contact = _contacts.find(jid);

    if (_contacts.end() == contact) {
      LOG2("Item not found in local roster");
    }

    return contact;
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

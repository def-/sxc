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

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <string>
#include <map>
#include <sstream>
#include <exception>

#include <pthread.h>

#include <gloox/clientbase.h>
#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/iq.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/error.h>

#include <libsxc/generateString.hxx>
#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Debug/Logger.hxx>
#include <libsxc/Error/Handler.hxx>

#include <Account/Roster.hxx>
#include <Account/RosterType.hxx>
#include <Account/Exception/AddContactFailed.hxx>
#include <Contact/Contact.hxx>
#include <File/AbcOutput.hxx>
#include <File/createDir.hxx>
#include <Exit/Code.hxx>

/*}}}*/

#include <iostream>
namespace Account
{
  Roster::Roster(/*{{{*/
    gloox::Client &client,
    ::File::AbcOutput &out,
    libsxc::Error::Handler &eh)
  : RosterListener()
  , _client(client)
  , _out(out)
  , _contacts()
  , _eh(eh)
  {
    pthread_mutex_init(&_resetMutex, NULL);

    // Asynchronous subscription request handling.
    _client.rosterManager()->registerRosterListener(this, false);
    _client.registerMessageHandler(this);
  }/*}}}*/
  Roster::~Roster()/*{{{*/
  {
    _client.rosterManager()->removeRosterListener();
    _client.removeMessageHandler(this);

    reset();

    // Has to be called after reset.
    pthread_mutex_destroy(&_resetMutex);
  }/*}}}*/

  void Roster::addContactLocal(const gloox::JID &jid)/*{{{*/
  {
    _out.write("Add contact locally: " + jid.bare());
    _addContactLocal(jid);
  }/*}}}*/
  void Roster::addContact(const gloox::JID &jid)/*{{{*/
  {
    _addContactLocal(jid);
    _addContactRemote(jid);
  }/*}}}*/
  void Roster::removeContact(const gloox::JID &jid)/*{{{*/
  {
    _checkClient();

    _out.write("Delete contact: " + jid.bare());

    contactList::iterator contact = _getContact(jid.bare());
    if (_contacts.end() != contact) {
      contact->second->remove();
      delete contact->second;
      _contacts.erase(contact);
    }

    // Still remove the contact from the server, even if it is not available
    // locally.
    _client.rosterManager()->remove(jid);
    _client.rosterManager()->synchronize();
  }/*}}}*/

  void Roster::subscribe(/*{{{*/
    const gloox::JID &jid,
    const std::string &message) const
  {
    _checkClient();

    _out.write("Request subscription: " + jid.bare() + "\nMessage: " + message);
    const gloox::StringList groups;
    _client.rosterManager()->subscribe(jid, jid.bare(), groups, message);
    _client.rosterManager()->synchronize();
  }/*}}}*/
  void Roster::unsubscribe(/*{{{*/
    const gloox::JID &jid,
    const std::string &message) const
  {
    _checkClient();

    _out.write("Unsubscribe: " + jid.bare() +
      "\nMessage: " + message);
    _client.rosterManager()->unsubscribe(jid, message);
    _client.rosterManager()->synchronize();
  }/*}}}*/

  void Roster::cancel(/*{{{*/
    const gloox::JID &jid,
    const std::string &message) const
  {
    _checkClient();

    _out.write("Cancel contact's subscription: " + jid.bare() +
      "\nMessage: " + message);
    _client.rosterManager()->cancel(jid, message);
    _client.rosterManager()->synchronize();
  }/*}}}*/

  void Roster::acknowledgeSubscription(const gloox::JID &jid) const/*{{{*/
  {
    _out.write("Acknowledge subscription request: " + jid.bare());
    _client.rosterManager()->ackSubscriptionRequest(jid, true);
  }/*}}}*/
  void Roster::declineSubscription(const gloox::JID &jid) const/*{{{*/
  {
    _out.write("Decline subscription request: " + jid.bare());
    _client.rosterManager()->ackSubscriptionRequest(jid, false);
  }/*}}}*/

  void Roster::handleMessage(/*{{{*/
    const gloox::Message &msg,
    gloox::MessageSession *session)
  {
    _addContactLocal(msg.from()); // Local only.

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
    // This deletes the session. Else the destructor of gloox::ClientBase would
    // handle this.
    _client.disposeMessageSession(session);
  }/*}}}*/

  void Roster::reset()/*{{{*/
  {
    // Must be unlocked!
    pthread_mutex_lock(&_resetMutex);

    try {
      for(
      contactList::iterator entry = _contacts.begin();
      entry != _contacts.end();
      ++entry) {
        delete entry->second;
      }

      _contacts.clear();
    } catch (std::exception &e) {
      pthread_mutex_unlock(&_resetMutex);
      throw e;
    } catch (...) {
      // Weird exception, rather ignore, so we can unlock the mutex.
    }

    pthread_mutex_unlock(&_resetMutex);
  }/*}}}*/
  const gloox::JID &Roster::getJid()/*{{{*/
  {
    return _client.jid();
  }/*}}}*/

  void Roster::handleItemAdded(const gloox::JID &jid)/*{{{*/
  {
    _out.write("Add contact: " + jid.bare());
    _addContactLocal(jid);

    contactList::iterator contact = _getContact(jid.bare());
    if (_contacts.end() == contact)
      return;
    contact->second->updateRoster(Remote);
    gloox::SubscriptionType newSub =
      _client.rosterManager()->getRosterItem(jid)->subscription();
    contact->second->updateSub(newSub);
  }/*}}}*/
  void Roster::handleItemSubscribed(const gloox::JID &jid)/*{{{*/
  {
    _out.write("Subscribed to contact: " + jid.bare());
  }/*}}}*/
  void Roster::handleItemRemoved(const gloox::JID &jid)/*{{{*/
  {
    LOG("Contact removed: \"" + jid.bare() + "\".");
  }/*}}}*/
  void Roster::handleItemUpdated(const gloox::JID &jid)/*{{{*/
  {
    LOG("Item updated: \"" + jid.bare() + "\".");

    contactList::iterator contact = _getContact(jid.bare());
    if (_contacts.end() == contact)
      return;

    gloox::SubscriptionType newSub =
      _client.rosterManager()->getRosterItem(jid)->subscription();
    contact->second->updateSub(newSub);
  }/*}}}*/
  void Roster::handleItemUnsubscribed(const gloox::JID &jid)/*{{{*/
  {
    _out.write("Unsubscribed to contact: " + jid.bare());
  }/*}}}*/
  void Roster::handleRoster(const gloox::Roster &roster)/*{{{*/
  {
    LOG("Initial roster received from the server.");

    for(
    gloox::Roster::const_iterator entry = roster.begin();
    entry != roster.end();
    ++entry) {
      _addContactLocal(entry->first);

      contactList::iterator contact = _getContact(entry->first);
      if (_contacts.end() == contact)
        continue;

      contact->second->updateRoster(Remote);
      gloox::SubscriptionType newSub = entry->second->subscription();
      contact->second->updateSub(newSub);
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
    LOG(ss.str());

    contactList::iterator contact = _getContact(item.jid());
    if (_contacts.end() == contact)
      return;
    contact->second->updatePresence(resource, presence, msg);
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
    LOG(ss.str());
  }/*}}}*/
  bool Roster::handleSubscriptionRequest(/*{{{*/
    const gloox::JID &jid,
    const std::string &msg)
  {
    _out.write("Contact requests subscription: " + jid.bare() +
      "\nMessage: " + msg);
    return false; // Will be ignored anyway.
  }/*}}}*/
  bool Roster::handleUnsubscriptionRequest(/*{{{*/
    const gloox::JID &jid,
    const std::string &msg)
  {
    contactList::iterator contact = _getContact(jid.bare());
    if (_contacts.end() == contact)
      return false;

    _out.write("Contact unsubscribed: " + jid.bare() + "\nMessage: " + msg);

    return false; // Will be ignored anyway.
  }/*}}}*/
  void Roster::handleNonrosterPresence(const gloox::Presence &presence)/*{{{*/
  {
    std::ostringstream ss;
    ss << "Nonroster-Status changed: (type: \"" << presence.subtype()
       << "\", message: \"" << presence.status() << "\").";
    LOG(ss.str());
  }/*}}}*/
  void Roster::handleRosterError(const gloox::IQ &iq)/*{{{*/
  {
    const gloox::Error *error = iq.error();
    if (error) {
      _eh.print(
        "Roster error received: " +
        libsxc::genStanzaErrorString(error->error()));
    }

  }/*}}}*/

  void Roster::_checkClient() const/*{{{*/
  {
    // FIXME: Better exception or none at all
    if (!gloox::StateConnected == _client.state())
      throw libsxc::Exception::Exception(
        "Connection ist not established.",
        Exit::InvalidUsage);
  }/*}}}*/
  void Roster::_addContactRemote(const gloox::JID &jid)/*{{{*/
  {
    LOG(
      "Add contact to the remote roster: \"" + jid.bare() + "\".");

    _checkClient();

    const gloox::StringList groups;
    _client.rosterManager()->add(jid, jid.bare(), groups);
    _client.rosterManager()->synchronize();

    contactList::iterator contact = _getContact(jid.bare());
    if (_contacts.end() == contact)
      return;

    contact->second->updateRoster(Remote);
  }/*}}}*/
  void Roster::_addContactLocal(const gloox::JID &jid)/*{{{*/
  {
    if (_contacts.end() != _getContact(jid.bare())) {
      LOG("Contact already in local roster, not adding: \"" +
        jid.bare() + "\"");
      return;
    }

    Contact::Contact *contact;

    try {
      ::File::createDir(_client.jid().bare() + "/" + jid.bare());

      contact = new Contact::Contact(
        *this, _out, _client.jid(), jid);
      contact->updateRoster(Local);
    } catch (libsxc::Exception::Exception &e) {
      _out.write(std::string("Adding contact failed: ") + e.what());
      const char* name = jid.bare().c_str();
      throw Exception::AddContactFailed(name, e);
    }

    _contacts.insert(std::make_pair(jid.bare(), contact));
  }/*}}}*/
  contactList::iterator Roster::_getContact(const std::string &jid)/*{{{*/
  {
    contactList::iterator contact = _contacts.find(jid);

    if (_contacts.end() == contact) {
      LOG("Item not found in local roster");
    }

    return contact;
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

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

#include <gloox/clientbase.h>
#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/iq.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>

#include <libsxc/generateString.hxx>
#include <libsxc/Exception/GlooxException.hxx>

#include <Control/Roster.hxx>
#include <Control/Control.hxx>
#include <Contact/Contact.hxx>
#include <print.hxx>

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#endif

#ifdef DEBUG
#   include <sstream>
#endif

/*}}}*/

#include <iostream>

namespace Control
{
    Roster::Roster(Control *control, gloox::Client *client)/*{{{*/
    : RosterListener(),
      _control(control),
      _client(client),
      _contacts()
    {
        // Asynchronous subscription request handling.
        _client->rosterManager()->registerRosterListener(this, false);
    }/*}}}*/
    Roster::~Roster()/*{{{*/
    {
        _client->rosterManager()->removeRosterListener();

        for(
        contactList::iterator entry = _contacts.begin();
        entry != _contacts.end();
        ++entry) {
            delete entry->second;
        }
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

#       ifdef DEBUG
            printLog("Remove contact from the roster: \"" + jid.bare() + "\".");
#       endif

        _client->rosterManager()->remove(jid);
        _client->rosterManager()->synchronize();
    }/*}}}*/

    void Roster::subscribe(/*{{{*/
        const gloox::JID &jid,
        const std::string &message) const
    {
        _checkClient();

#       ifdef DEBUG
            printLog(
                "Sending subscription request: (jid: \"" + jid.bare() +
                "\", message: \"" + message + "\").");
#       endif

        const gloox::StringList groups;
        _client->rosterManager()->subscribe(jid, jid.bare(), groups, message);
        _client->rosterManager()->synchronize();
    }/*}}}*/
    void Roster::unsubscribe(/*{{{*/
        const gloox::JID &jid,
        const std::string &message) const
    {
        _checkClient();

#       ifdef DEBUG
            printLog(
                "Sending unsubscription request: (jid: \"" + jid.bare() +
                "\", message: \"" + message + "\").");
#       endif

        _client->rosterManager()->unsubscribe(jid, message);
        _client->rosterManager()->synchronize();
    }/*}}}*/

    void Roster::acknowledgeSubscription(const gloox::JID &jid) const/*{{{*/
    {
#       ifdef DEBUG
            printLog(
                "Acknowledge subscription request: \"" + jid.bare() + "\".");
#       endif

        _client->rosterManager()->ackSubscriptionRequest(jid, true);
    }/*}}}*/
    void Roster::declineSubscription(const gloox::JID &jid) const/*{{{*/
    {
#       ifdef DEBUG
            printLog(
                "Decline subscription request: \"" + jid.bare() + "\".");
#       endif

        _client->rosterManager()->ackSubscriptionRequest(jid, false);
    }/*}}}*/

    void Roster::handleMessage(/*{{{*/
        const gloox::Message &msg,
        gloox::MessageSession *session)
    {
        addContact(msg.from(), false); // Local only.

        contactList::iterator contact = _getClient(msg.from().bare());
        if (_contacts.end() == contact)
            return;

        contact->second->handleMessage(msg, session);
    }/*}}}*/

    void Roster::handleItemAdded(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog("Item added to the roster: \"" + jid.bare() + "\".");
#       endif

        _addContactLocal(jid);
    }/*}}}*/
    void Roster::handleItemSubscribed(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog("Item subscribed: \"" + jid.bare() + "\".");
#       endif
    }/*}}}*/
    void Roster::handleItemRemoved(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog("Item removed from the roster: \"" + jid.bare() + "\".");
#       endif

        contactList::iterator contact = _getClient(jid.bare());
        if (_contacts.end() == contact)
            return;
        delete contact->second;
        _contacts.erase(contact);

        _control->print("Contact removed: \"" + jid.bare() + "\".");
    }/*}}}*/
    void Roster::handleItemUpdated(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog("Item updated: \"" + jid.bare() + "\".");
#       endif
    }/*}}}*/
    void Roster::handleItemUnsubscribed(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog(
                "Item unsubscribed: \"" + jid.bare() + "\".");
#       endif
    }/*}}}*/
    void Roster::handleRoster(const gloox::Roster &roster)/*{{{*/
    {
#       ifdef DEBUG
            printLog("Initial roster received from the server.");
#       endif
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
#       ifdef DEBUG
            std::ostringstream ss;
            ss << "Status changed: (jid: \"" << item.jid()
               << "/" << resource << "\", presence: \""
               << libsxc::genPresenceString(presence) << "\" (" << presence
               << "), message: \"" << msg << "\").";
            printLog(ss.str());
#       endif

        contactList::iterator contact = _getClient(item.jid());
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
#       ifdef DEBUG
            std::ostringstream ss;
            ss << "Self-status changed: (jid: \"" << item.name()
               << "\", resource: \"" << resource << "\", presence: "
               << presence << ", message: \"" << msg << "\").";
            printLog(ss.str());
#       endif
    }/*}}}*/
    bool Roster::handleSubscriptionRequest(/*{{{*/
        const gloox::JID &jid,
        const std::string &msg)
    {
#       ifdef DEBUG
            printLog(
                "Received subscription request: (jid: \"" + jid.bare() +
                "\", message: \"" + msg + "\").");
#       endif

        contactList::iterator contact = _getClient(jid.bare());
        if (_contacts.end() == contact)
            return true;

        _control->print(
            "Subscription request received: \"" + jid.bare() + "\"");

        return true;
    }/*}}}*/
    bool Roster::handleUnsubscriptionRequest(/*{{{*/
        const gloox::JID &jid,
        const std::string &msg)
    {
#       ifdef DEBUG
            printLog(
                "Received unsubscription request: (jid: \"" + jid.bare() +
                "\", message: \"" + msg + "\").");
#       endif

        contactList::iterator contact = _getClient(jid.bare());
        if (_contacts.end() == contact)
            return true;

        _control->print(
            "Unsubscription request received: \"" + jid.bare() + "\"");

        return true;
    }/*}}}*/
    void Roster::handleNonrosterPresence(const gloox::Presence &presence)/*{{{*/
    {
#       ifdef DEBUG
            std::ostringstream ss;
            ss << "Nonroster-Status changed: (type: \"" << presence.subtype()
               << "\", message: \"" << presence.status() << "\").";
            printLog(ss.str());
#       endif
    }/*}}}*/
    void Roster::handleRosterError(const gloox::IQ &iq)/*{{{*/
    {
        const gloox::Error *error = iq.error();
#       ifdef DEBUG
            if (error)
                printLog(
                    "Roster error received: " +
                    libsxc::genStanzaErrorString(error->error()));
#       endif

        // FIXME: Use handleError
        if (error)
            _control->print(
                "Roster error received: " +
                libsxc::genStanzaErrorString(error->error()));
    }/*}}}*/

    void Roster::_checkClient() const/*{{{*/
    {
        if (!gloox::StateConnected == _client->state())
            throw libsxc::Exception::GlooxException(
                libsxc::Exception::InvalidUsage,
                "Connection ist not established.");
    }/*}}}*/
    void Roster::_addContactRemote(const gloox::JID &jid) const/*{{{*/
    {
#       ifdef DEBUG
            printLog(
                "Add contact to the remote roster: \"" + jid.bare() + "\".");
#       endif

        _checkClient();

        const gloox::StringList groups;
        _client->rosterManager()->add(jid, jid.bare(), groups);
        _client->rosterManager()->synchronize();
    }/*}}}*/
    void Roster::_addContactLocal(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog(
                "Add contact to the local roster: \"" + jid.bare() + "\".");
#       endif

        _contacts.insert(std::make_pair(
            jid.bare(),
            new Contact::Contact(_client, jid)));
    }/*}}}*/
    contactList::iterator Roster::_getClient(const std::string &jid)/*{{{*/
    {
        contactList::iterator contact = _contacts.find(jid);

        if (_contacts.end() == contact) {
#           ifdef DEBUG
                printLog("Item not found in local roster");
#           endif
        }

        return contact;
    }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

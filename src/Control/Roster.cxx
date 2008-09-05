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
#include <map>
#include <gloox/clientbase.h>
#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/iq.h>

#include <libsxc/Exception/GlooxException.hxx>

#include <Control/Roster.hxx>
#include <Control/Control.hxx>
#include <Contact/Contact.hxx>
#include <print.hxx>
#include <generateString.hxx>

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#endif

#ifdef DEBUG
#   include <sstream>
#endif

/*}}}*/


namespace Control
{
    Roster::Roster(gloox::Client &client)/*{{{*/
    : RosterListener(),
      _client(client),
      _contacts()
    {
        // Asynchronous subscription request handling.
        _client.rosterManager()->registerRosterListener(this, false);
    }/*}}}*/

    void Roster::addContact(const gloox::JID &jid) const/*{{{*/
    {
        _checkClient();

#       ifdef DEBUG
            printLog("Add contact to the roster: \"" + jid.bare() + "\".");
#       endif

        const gloox::StringList groups;
        _client.rosterManager()->add(jid, jid.bare(), groups);
    }/*}}}*/
    void Roster::removeContact(const gloox::JID &jid) const/*{{{*/
    {
        _checkClient();

#       ifdef DEBUG
            printLog("Remove contact from the roster: \"" + jid.bare() + "\".");
#       endif

        _client.rosterManager()->remove(jid);
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
        _client.rosterManager()->subscribe(jid, jid.bare(), groups, message);
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

        _client.rosterManager()->unsubscribe(jid, message);
    }/*}}}*/

    void Roster::acknowledgeSubscription(const gloox::JID &jid) const/*{{{*/
    {
#       ifdef DEBUG
            printLog(
                "Acknowledge subscription request: \"" + jid.bare() + "\".");
#       endif

        _client.rosterManager()->ackSubscriptionRequest(jid, true);
    }/*}}}*/
    void Roster::declineSubscription(const gloox::JID &jid) const/*{{{*/
    {
#       ifdef DEBUG
            printLog(
                "Decline subscription request: \"" + jid.bare() + "\".");
#       endif

        _client.rosterManager()->ackSubscriptionRequest(jid, false);
    }/*}}}*/

    void Roster::handleItemAdded(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog("Item added to the roster: \"" + jid.bare() + "\".");
#       endif
        // FIXME
    }/*}}}*/
    void Roster::handleItemSubscribed(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog("Item subscribed to the roster: \"" + jid.bare() + "\".");
#       endif
        // FIXME
    }/*}}}*/
    void Roster::handleItemRemoved(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog("Item removed from the roster: \"" + jid.bare() + "\".");
#       endif
        // FIXME
    }/*}}}*/
    void Roster::handleItemUpdated(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog("Item updated: \"" + jid.bare() + "\".");
#       endif
        // FIXME
    }/*}}}*/
    void Roster::handleItemUnsubscribed(const gloox::JID &jid)/*{{{*/
    {
#       ifdef DEBUG
            printLog("Item unsubscribed: \"" + jid.bare() + "\".");
#       endif
        // FIXME
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
#           ifdef DEBUG
                printLog("Add contact " + entry->first + " to the roster");
#           endif
            _contacts.insert(make_pair(
                entry->first,
                new Contact::Contact(&_client, gloox::JID(entry->first))));
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
               << "\", resource: \"" << resource << "\", presence: \""
               << genPresenceString(presence) << "\" (" << presence
               << "), message: \"" << msg << "\").";
            printLog(ss.str());
#       endif
        // FIXME
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
        // FIXME
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
        // FIXME
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
        // FIXME
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
        //FIXME
    }/*}}}*/
    void Roster::handleRosterError(const gloox::IQ &iq)/*{{{*/
    {
#       ifdef DEBUG
            // FIXME: getStanzaErrorDescription()
            printLog("Roster error received.");
#       endif
        //FIXME
    }/*}}}*/

    void Roster::_checkClient() const/*{{{*/
    {
        if (! gloox::StateConnected == _client.state())
            throw libsxc::Exception::GlooxException(
                libsxc::Exception::InvalidUsage,
                "Connection ist not established.");
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

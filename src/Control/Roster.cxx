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

/*}}}*/


namespace Control
{
    Roster::Roster(gloox::Client &client)/*{{{*/
    : RosterListener(),
      _client(client),
      _contacts()
    {
    }/*}}}*/

    void Roster::addContact(const std::string &rawJid) const/*{{{*/
    {
        _checkClient();
        const gloox::JID &jid = _generateJid(rawJid);

#       ifdef DEBUG
            printLog("Add " + rawJid + " to the roster.");
#       endif

        const gloox::StringList groups;
        _client.rosterManager()->add(jid, jid.bare(), groups);
    }/*}}}*/
    void Roster::removeContact(const std::string &rawJid) const/*{{{*/
    {
        _checkClient();
        const gloox::JID &jid = _generateJid(rawJid);

#       ifdef DEBUG
            printLog("Remove " + rawJid + " from the roster.");
#       endif

        _client.rosterManager()->remove(jid);
    }/*}}}*/

    void Roster::subscribe(/*{{{*/
        const std::string &rawJid,
        const std::string &message) const
    {
        _checkClient();
        const gloox::JID &jid = _generateJid(rawJid);

#       ifdef DEBUG
            printLog("Sending subscription request to " + rawJid);
#       endif

        _client.rosterManager()->remove(jid);
    }/*}}}*/
    void Roster::unsubscribe(/*{{{*/
        const std::string &rawJid,
        const std::string &message) const
    {
    }/*}}}*/

    void Roster::acknowledgeSubscription(const std::string &rawJid) const/*{{{*/
    {
    }/*}}}*/
    void Roster::declineSubscription(const std::string &rawJid) const/*{{{*/
    {
    }/*}}}*/

    void Roster::handleItemAdded(const gloox::JID &jid)/*{{{*/
    {
    }/*}}}*/
    void Roster::handleItemSubscribed(const gloox::JID &jid)/*{{{*/
    {
    }/*}}}*/
    void Roster::handleItemRemoved(const gloox::JID &jid)/*{{{*/
    {
    }/*}}}*/
    void Roster::handleItemUpdated(const gloox::JID &jid)/*{{{*/
    {
    }/*}}}*/
    void Roster::handleItemUnsubscribed(const gloox::JID &jid)/*{{{*/
    {
    }/*}}}*/
    void Roster::handleRoster(const gloox::Roster &roster)/*{{{*/
    {
#       if DEBUG
            printLog("Initial roster received from the server.");
#       endif
        for(
        gloox::Roster::const_iterator entry = roster.begin();
        entry != roster.end();
            ++entry) {
#           if DEBUG
                printLog("Adding contact " + entry->first + " to the roster");
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
    }/*}}}*/
    void Roster::handleSelfPresence(/*{{{*/
        const gloox::RosterItem &item,
        const std::string &resource,
        gloox::Presence::PresenceType presence,
        const std::string &msg)
    {
    }/*}}}*/
    bool Roster::handleSubscriptionRequest(/*{{{*/
        const gloox::JID &jid,
        const std::string &msg)
    {
        // TODO
        return true;
    }/*}}}*/
    bool Roster::handleUnsubscriptionRequest(/*{{{*/
        const gloox::JID &jid,
        const std::string &msg)
    {
        // TODO
        return true;
    }/*}}}*/
    void Roster::handleNonrosterPresence(const gloox::Presence &presence)/*{{{*/
    {
    }/*}}}*/
    void Roster::handleRosterError(const gloox::IQ &iq)/*{{{*/
    {
    }/*}}}*/

    void Roster::_checkClient() const/*{{{*/
    {
        if (! gloox::StateConnected == _client.state())
            throw libsxc::Exception::GlooxException(
                libsxc::Exception::InvalidUsage,
                "Connection ist not established.");
    }/*}}}*/
    const gloox::JID &Roster::_generateJid(const std::string &raw) const/*{{{*/
    {
        static const gloox::JID jid(raw);
        if (jid.full() == gloox::EmptyString)
            throw libsxc::Exception::GlooxException(
                libsxc::Exception::JidInvalid,
                "Invalid JID: " + raw);
        return jid;
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

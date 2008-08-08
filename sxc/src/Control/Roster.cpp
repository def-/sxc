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

#include <Control/Roster.h>
#include <Contact/Contact.h>

/*}}}*/


namespace Control
{
    Roster::Roster(gloox::ClientBase *client)/*{{{*/
    : RosterManager(client),
      RosterListener(),
      _client(client),
      _contacts()
    {
    }/*}}}*/

    bool Roster::handleIq(const gloox::IQ &iq)/*{{{*/
    {
    }/*}}}*/

    void Roster::handleIqID(const gloox::IQ &iq, int context)/*{{{*/
    {
    }/*}}}*/

    void Roster::handlePresence(const gloox::Presence &presence)/*{{{*/
    {
    }/*}}}*/

    void Roster::handleSubscription(/*{{{*/
        const gloox::Subscription &subscription)
    {
    }/*}}}*/

    void Roster::handlePrivateXML(const gloox::Tag *xml)/*{{{*/
    {
    }/*}}}*/

    void Roster::handlePrivateXMLResult(/*{{{*/
        const std::string &uid,
        gloox::PrivateXMLHandler::PrivateXMLResult pxResult)
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
        for(
        gloox::Roster::const_iterator entry = roster.begin();
        entry != roster.end();
            ++entry) {
            _contacts.insert(make_pair(
                entry->first,
                new Contact::Contact(_client, gloox::JID(entry->first))));
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
    }/*}}}*/

    bool Roster::handleUnsubscriptionRequest(/*{{{*/
        const gloox::JID &jid,
        const std::string &msg)
    {
    }/*}}}*/

    void Roster::handleNonrosterPresence(const gloox::Presence &presence)/*{{{*/
    {
    }/*}}}*/

    void Roster::handleRosterError(const gloox::IQ &iq)/*{{{*/
    {
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

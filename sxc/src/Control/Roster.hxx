// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright(C) 2008 Dennis Felsing, Andreas Waidler

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


#ifndef CONTROL_ROSTER_HXX
#define CONTROL_ROSTER_HXX


// INCLUDE/*{{{*/

#include <string>
#include <map>
#include <gloox/clientbase.h>
#include <gloox/rostermanager.h>
#include <gloox/rosterlistener.h>
#include <gloox/subscription.h>
#include <gloox/privatexmlhandler.h>
#include <gloox/rosteritem.h>
#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/iq.h>

#include <Contact/Contact.hxx>

/*}}}*/

namespace Control
{
    //typedef std::map<const std::string, Contact::Contact *> contactList;/*{{{*/

    /// A map of JIDs and Contact-objects.
    typedef std::map<const std::string, Contact::Contact *> contactList;

/*}}}*/

    /**
     * @author Dennis Felsing
     * @brief A roster containing all the contacts.
     *
     * This class handles all changes to the roster from and to the server.
     */
    // TODO: RosterManager not neccessary?
    class Roster : public gloox::RosterManager, gloox::RosterListener
    {
        public:
            Roster(gloox::ClientBase *client);

            // Reimplemented from gloox::RosterManager.
            virtual bool handleIq(const gloox::IQ &iq);
            virtual void handleIqID(const gloox::IQ &iq, int context);
            virtual void handlePresence(const gloox::Presence &presence);
            virtual void handleSubscription(
                const gloox::Subscription &subscription);
            virtual void handlePrivateXML(const gloox::Tag *xml);
            virtual void handlePrivateXMLResult(
                const std::string &uid,
                gloox::PrivateXMLHandler::PrivateXMLResult pxResult);

            // Reimplemented from gloox::RosterListener
            virtual void handleItemAdded(const gloox::JID &jid);
            virtual void handleItemSubscribed(const gloox::JID &jid);
            virtual void handleItemRemoved(const gloox::JID &jid);
            virtual void handleItemUpdated(const gloox::JID &jid);
            virtual void handleItemUnsubscribed(const gloox::JID &jid);
            //virtual void handleRoster(const gloox::Roster &roster);/*{{{*/

            /**
             * @brief This function gets called on the initial push.
             *
             * When the connection to the server is established, the server
             * pushes the current roster and this function gets called. It
             * creates the client objects for each roster item.
             *
             * @param roster The roster from the server.
             */
            virtual void handleRoster(const gloox::Roster &roster);

/*}}}*/
            virtual void handleRosterPresence(
                const gloox::RosterItem &item,
                const std::string &resource,
                gloox::Presence::PresenceType presence,
                const std::string &msg);
            virtual void handleSelfPresence(
                const gloox::RosterItem &item,
                const std::string &resource,
                gloox::Presence::PresenceType presence,
                const std::string &msg);
            virtual bool handleSubscriptionRequest(
                const gloox::JID &jid,
                const std::string &msg);
            virtual bool handleUnsubscriptionRequest(
                const gloox::JID &jid,
                const std::string &msg);
            virtual void handleNonrosterPresence(
                const gloox::Presence &presence);
            virtual void handleRosterError(const gloox::IQ &iq);

        private:
            gloox::ClientBase *_client;
            contactList _contacts;

    };
}


#endif // CONTROL_ROSTER_HXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

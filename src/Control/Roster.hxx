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
#include <gloox/client.h>
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
    class Roster : public gloox::RosterListener
    {
        public:
            //Roster(gloox::Client &client);/*{{{*/

            /**
             * @brief Initialise the roster and register with the client.
             *
             * @param client The client class to register with.
             */
            Roster(gloox::Client &client);

/*}}}*/

            //void addContact(const std::string &rawJid) const;/*{{{*/

            /**
             * @brief Add contact to the roster.
             *
             * @note This method does not send a subscription request, use @ref
             *       subscribe() if you want to see the contact's status.
             *
             * @param rawJid The JID to add to the roster.
             */
            void addContact(const std::string &rawJid) const;

/*}}}*/
            //void removeContact(const std::string &rawJid) const;/*{{{*/

            /**
             * @brief Remove a contact from the roster.
             *
             * @note This function unsubscribes implicetely.
             *
             * @param rawJid The JID of the contact to remove.
             */
            void removeContact(const std::string &rawJid) const;

/*}}}*/

            //void subscribe(string &rawJid, &message=EmptyString) const;/*{{{*/

            /**
             * @brief Send a subscription request.
             *
             * This method sends a request to the contact asking for permission
             * to be updated on presence changes. Compliant servers add the
             * contact to the roster automatically, so there is no need to call
             * @ref addContact().
             *
             * @param rawJid The JID to subscribe to for presence updates.
             * @param message The message to send along.
             */
            void subscribe(
                const std::string &rawJid,
                const std::string &message=gloox::EmptyString) const;

/*}}}*/
            //void unsubscribe(string &rawJid, &message=Empty) const;/*{{{*/

            /**
             * @brief Unsubscribe from a contact.
             *
             * This method sends an unsubscription request to the contact. So
             * the contact will no longer receive presence updates from you.
             *
             * @param rawJid The JID to unsubscribe from.
             * @param message The message to send along.
             */
            void unsubscribe(
                const std::string &rawJid,
                const std::string &message=gloox::EmptyString) const;

/*}}}*/

            //void acknowledgeSubscription(const string &rawJid) const;/*{{{*/

            /**
             * @brief Acknowlodge a subscription request.
             *
             * This method adds the user to the list of contacts to send
             * presence updates to.
             *
             * @param rawJid The JID.
             */
            void acknowledgeSubscription(const std::string &rawJid) const;

/*}}}*/
            //void declineSubscription(const std::string &rawJid) const;/*{{{*/

            /**
             * @brief Decline a subscription request.
             *
             * @param rawJid The JID.
             */
            void declineSubscription(const std::string &rawJid) const;

/*}}}*/

            // Reimplemented from gloox::RosterListener
            //void handleItemAdded(const gloox::JID &jid);/*{{{*/

            /**
             * @brief Notification about new items on the server-side roster.
             *
             * This function is called regardless who added the item, either
             * this resource or another. However, it will not be called for
             * JIDs for which presence is received without them beuing on the
             * roster.
             *
             * The JID will be added to the local file structure.
             *
             * @param jid The new item's full address.
             */
            void handleItemAdded(const gloox::JID &jid);

/*}}}*/
            //void handleItemSubscribed(const gloox::JID &jid);/*{{{*/

            /**
             * @brief Notification about items which authorised subscription.
             *
             * @param jid The authorising item's full address.
             */
            void handleItemSubscribed(const gloox::JID &jid);

/*}}}*/
            //void handleItemRemoved(const gloox::JID &jid);/*{{{*/

            /**
             * @brief Notification about removals on the server-side roster.
             *
             * This function is called regardless who removed the item, either
             * this resource or another. However, it will not be called for
             * JIDs for which presence is received without them beuing on the
             * roster.
             *
             * The JID will be removed from the local file structure.
             *
             * @param jid The removed item's full address.
             */
            void handleItemRemoved(const gloox::JID &jid);

/*}}}*/
            //void handleItemUpdated(const gloox::JID &jid);/*{{{*/

            /**
             * @brief Notification about modifications on the roster.
             *
             * This function is called regardless who modified the item, either
             * this resource or another. However, it will not be called for
             * JIDs for which presence is received without them beuing on the
             * roster.
             *
             * @param jid The modified item's full address.
             */
            void handleItemUpdated(const gloox::JID &jid);

/*}}}*/
            //void handleItemUnsubscribed(const gloox::JID &jid);/*{{{*/

            /**
             * @brief An item removed subscription authorization.
             *
             * @param jid The item's full address.
             */
            void handleItemUnsubscribed(const gloox::JID &jid);

/*}}}*/
            //void handleRoster(const gloox::Roster &roster);/*{{{*/

            /**
             * @brief This function gets called on the initial push.
             *
             * When the connection to the server is established, the server
             * pushes the current roster and this function gets called. It
             * creates the client objects for each roster item.
             *
             * @param roster The roster from the server.
             */
            void handleRoster(const gloox::Roster &roster);

/*}}}*/
            //void handleRosterPresence(item, resouce, presence, msg);/*{{{*/

            /**
             * @brief Notification about status changes of roster items.
             *
             * @param item The roster item.
             * @param resource The resource that changed presence.
             * @param presence The item's new presence.
             * @param msg The status change message.
             */
            void handleRosterPresence(
                const gloox::RosterItem &item,
                const std::string &resource,
                gloox::Presence::PresenceType presence,
                const std::string &msg);

/*}}}*/
            //void handleSelfPresence(item, resource, presence, msg);/*{{{*/

            /**
             * @brief Notification about the client's own JID.
             *
             * @param item The roster item.
             * @param resource The resource that changed presence.
             * @param presence The item's new presence.
             * @param msg The status change message.
             */
            void handleSelfPresence(
                const gloox::RosterItem &item,
                const std::string &resource,
                gloox::Presence::PresenceType presence,
                const std::string &msg);

/*}}}*/
            //bool handleSubscriptionRequest(JID jid, string msg);/*{{{*/

            /**
             * @brief An entity wishes to subscribe to this entity's presence.
             *
             * @note If the handler is registered as a asynchronous handler for
             *       subscription requests, the return value of this function
             *       is ignored.
             *
             * @param jid The requesting item's address.
             * @param msg A message sent along with the request.
             */
            bool handleSubscriptionRequest(
                const gloox::JID &jid,
                const std::string &msg);

/*}}}*/
            //bool handleUnsubscriptionRequest(JID jid, string msg);/*{{{*/

            /**
             * @brief An entity has unsubscribed to this entity's presence.
             *
             * @note If the handler is registered as a asynchronous handler for
             *       subscription requests, the return value of this function
             *       is ignored.
             *
             * @param jid The requesting item's address.
             * @param msg A message sent along with the request.
             */
            bool handleUnsubscriptionRequest(
                const gloox::JID &jid,
                const std::string &msg);

/*}}}*/
            //void handleNonrosterPresence(const Presence &presence);/*{{{*/

            /**
             * @brief The presence from an entity is received.
             *
             * This function is called whenever the presence from an entity,
             * which is not in the roster, is received.
             *
             * @param presence The full presence stanza.
             */
            void handleNonrosterPresence(
                const gloox::Presence &presence);

/*}}}*/
            //void handleRosterError(const gloox::IQ &iq);/*{{{*/

            /**
             * @brief This function is called if the server returned an error.
             *
             * @param The error stanza.
             */
            void handleRosterError(const gloox::IQ &iq);

/*}}}*/

        private:
            //void _checkClient() const;/*{{{*/
            /// Check if there is a client. Throw an exception if not.
            void _checkClient() const;

/*}}}*/
            //const gloox::JID &_generateJid(const string &raw) const;/*{{{*/
            /// Generate a jid from a raw string. Throw exception on error.
            const gloox::JID &_generateJid(const std::string &raw) const;

/*}}}*/

            //gloox::Client &_client;/*{{{*/
            /// The client object this roster is bound to.
            gloox::Client &_client;

/*}}}*/
            //contactList _contacts;/*{{{*/
            /// All @ref Contact instances of the roster.
            contactList _contacts;

/*}}}*/

    };
}


#endif // CONTROL_ROSTER_HXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

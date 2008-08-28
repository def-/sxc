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
            //Roster(gloox::ClientBase *client);/*{{{*/

            /**
             * @brief Initialise the roster and register with the client.
             *
             * @param client The client class to register with.
             */
            Roster(gloox::ClientBase *client);

/*}}}*/

            // Reimplemented from gloox::RosterManager.
            //bool handleIq(const gloox::IQ &iq);/*{{{*/

            /**
             * @brief Notification about incoming IQs.
             *
             * @param iq The complete IQ stanza.
             */
            bool handleIq(const gloox::IQ &iq);

/*}}}*/
            //void handleIqID(const gloox::IQ &iq, int context);/*{{{*/

            /**
             * @brief Notification about incoming IQs with a specific id.
             *
             * @note Only IQ stanzas of type 'result or 'error' can arrive
             *       here.
             *
             * @param iq The complete IQ stanza.
             * @param context A value to restore context.
             */
            void handleIqID(const gloox::IQ &iq, int context);

/*}}}*/
            //void handlePresence(const gloox::Presence &presence);/*{{{*/

            /**
             * @biref Incoming presence notifications.
             *
             * @presence The complete stanza.
             */
            void handlePresence(const gloox::Presence &presence);

/*}}}*/
            //void handleSubscription(const Subscription subscription);/*{{{*/

            /**
             * @brief Notification about incoming subscriptions and requests.
             *
             * @param subscription The complete stanza.
             */
            void handleSubscription(const gloox::Subscription &subscription);

/*}}}*/
            //void handlePrivateXML(const gloox::Tag *xml);/*{{{*/

            /**
             * @brief Receive private XML that was requested earlier.
             *
             * @param xml The private xml, i.e. the first child of the <query>
             *        tag. May be 0. You should not delete the object.
             */
            void handlePrivateXML(const gloox::Tag *xml);

/*}}}*/
            //void handlePrivateXMLResult(string uid, pxResult);/*{{{*/

            /**
             * @brief Notification about the result of a 'store' or 'request'.
             *
             * @param uid The ID of the query.
             * @param pxResult The result of the operation.
             */
            void handlePrivateXMLResult(
                const std::string &uid,
                gloox::PrivateXMLHandler::PrivateXMLResult pxResult);

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
            //gloox::ClientBase *_client;/*{{{*/
            /// The client object this roster is bound to.
            gloox::ClientBase *_client;

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

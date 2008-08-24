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


#ifndef CONTROL_CONTROL_HXX
#define CONTROL_CONTROL_HXX


// INCLUDE/*{{{*/

#include <string>

#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/error.h>

#include <Singleton.hxx>
#include <Exception/Exception.hxx>
#include <Control/Roster.hxx>

/*}}}*/

/**
 * @brief Contains the controller classes.
 */
namespace Control
{
    /**
     * @author Dennis Felsing
     * @brief The central class connecting and controlling other classes.
     *
     * This class initializes sxc's main input and output files, handles
     * input and errors.
     *
     * @note As this class is a singleton you can use it from anywhere.
     *       @code
     *       Control::Control::get().print("foobar");
     *       @endcode
     */
    class Control : public
        Singleton<Control>,
        gloox::ConnectionListener,
        gloox::MessageHandler
    {
        public:
            //Control();/*{{{*/

            /**
             * @brief The constructor
             *
             * Initializes the values
             */
            Control();

/*}}}*/

            //void initialize(const gloox::JID jid, int port=-1);/*{{{*/

            /**
             * @brief Save the JID and the port and initialize the control
             *        files.
             *
             * Create new instances of @ref File::Input, and @ref File::Output.
             * Also save the parameters to be able to use them when connecting
             * to the server on a call to @ref setPresence().
             *
             * @note Does not connect to the server, see @ref _setPresence()
             *       for that.
             *
             * @warning The parameters won't be checked for validity.
             *
             * @param newJid A valid JID.
             * @param newPort The port on the server to connect to. -1 to use
             *        the default one.
             */
            void initialize(const gloox::JID newJid, int newPort=-1);

/*}}}*/

            //bool setPassword(std::string newPassword);/*{{{*/

            /**
             * @brief Set the password to a given string.
             *
             * If the connection is not established takes a new password and
             * stores it for the later connecting to the server.
             * If you are already connected to the server the new password is
             * transmitted to the server.
             *
             * @param newPassword The new password to be set.
             * @return True when not connected to the server or when the server
             *         accepts the new password, else false.
             */
            bool setPassword(std::string newPassword);

/*}}}*/
            //bool setPresence(presence, priority, status=EmptyString);/*{{{*/

            /**
             * @brief Set the presence.
             *
             * Set the user's presence and immediately send it out. Create the
             * @ref gloox::Client first if not existing, but password provided.
             *
             * @param presence The presence type. @ref
             *        gloox::Presence::PresenceType
             * @param priority The priority ranging from -128 to 127.
             * @param status A message describing the status.
             * @return Whether it was possible to set the presence.
             */
            bool setPresence(
                gloox::Presence::PresenceType presence,
                int priority=0,
                const std::string &status=gloox::EmptyString);

/*}}}*/
            //bool sendMessage(std::string to, std::string body) const;/*{{{*/

            /**
             * @brief Send a text message to a user.
             *
             * This function sends a given message to a recipant, whether he is
             * on the roster or not.
             *
             * @param to A string representing the JID of the recipant.
             * @param body The message to be transmitted.
             * @return Whether it was possible to send the message.
             */
            bool sendMessage(std::string to, std::string body) const;

/*}}}*/
            //bool addContact(string jid, string message=EmptyString)/*{{{*/

            /**
             * @brief Add a contact to the roster
             *
             * This function adds a contact to the roster and optionally sends
             * him a message to ask for the permission to see his presence.
             *
             * @param jid The JID to add to the roster.
             * @param message The message to send to the JID to ask for
             *        permission.
             * @return Whether the JID is valid.
             */
            bool addContact(
                std::string jid,
                std::string message=gloox::EmptyString) const;

/*}}}*/
            //bool ackSubscription(std::string jid, bool ack) const;/*{{{*/

            /**
             * @brief Acknowledge or decline a subscription request.
             *
             * When a user adds you to your roster and wants to see your
             * presence, he has to send you a request. This function
             * acknowledges or declines this request and thereby grants the
             * user to see your presence.
             *
             * @param jid A string representing the JID of the user.
             * @param ack Whether to acknowledge or to decline.
             * @return Whether the JID is valid.
             */
            bool ackSubscription(std::string jid, bool ack) const;

/*}}}*/
            //bool removeContact(std::string jid) const;/*{{{*/

            /**
             * @brief Remove a contact from the roster.
             *
             * This function removes a contact from the roster and disallows
             * him to see your presence.
             *
             * @param jid A string representing the JID of the contact.
             * @return Whether the JID is valid.
             */
            bool removeContact(std::string jid) const;

/*}}}*/

            //void handleError(Exception &e, isCritical=false) const;/*{{{*/

            /**
             * @brief Handle an error that happened inside sxc.
             *
             * @param e The @ref Exception object that contains more
             *        information.
             * @param isCritical Whether sxc cannot run anymore because of this
             *        error and has to be closed.
             */
            void handleError(
                Exception::Exception &e,
                bool isCritical=false) const;

/*}}}*/

            //void handleMessage(Message &msg, session=0);/*{{{*/

            /**
             * @brief Handle an incomming message.
             *
             * This function redirects an incomming message to the general
             * out-file for contacts that are not in the roster.
             *
             * @note Only messages, whose senders don't have a @ref
             *       Contact::Contact registered, get to this function.
             *
             * @param msg The complete message.
             * @param session The message session, if available.
             */
            void handleMessage(
                const gloox::Message &msg,
                gloox::MessageSession *session=0);

/*}}}*/

            //int print(std::string text) const;/*{{{*/

            /**
             * @brief Print a text to the output file.
             *
             * Print a text to the output file by sending it to the instance of
             * @ref File::Output.
             *
             * @param text The raw text to be written to the output file.
             */
            void print(std::string text) const;

/*}}}*/
            //gloox::Client *getClient() const;/*{{{*/

            /**
             * @brief Get the client object.
             */
            gloox::Client *getClient() const;

/*}}}*/

            //void onConnect();/*{{{*/

            /**
             * @brief This function is called after a connect.
             */
            void onConnect();

/*}}}*/
            //void onDisconnect(gloox::ConnectionError e);/*{{{*/

            /**
             * @brief This function is called after a disconnect.
             *
             * Handle the error.
             *
             * @param e The error which caused the disconnect.
             */
            void onDisconnect(gloox::ConnectionError e);

/*}}}*/
            //void onResourceBind(const std::string &resource);/*{{{*/

            /**
             * @brief This function is called on a resource bind.
             *
             * @param resource The resource string.
             */
            void onResourceBind(const std::string &resource);

/*}}}*/
            //void onResourceBindError(const gloox::Error *error);/*{{{*/

            /**
             * @brief An error occured when trying to bind a resouce.
             *
             * @param error A pointer to an Error object that contains more
             *        information. May be 0.
             */
            void onResourceBindError(const gloox::Error *error);

/*}}}*/
            //void onSessionCreateError(const gloox::Error *error);/*{{{*/

            /**
             * @brief Is called on errors in establishing a session.
             *
             * @param error A pointer to an Error object that contains more
             *        information. May be 0.
             */
            void onSessionCreateError(const gloox::Error *error);

/*}}}*/
            //bool onTLSConnect(const gloox::CertInfo &info);/*{{{*/

            /**
             * @brief This function is called when the connection was secured.
             *
             * @note Returning false terminates the connection.
             *
             * @param info Comprehensive information on the certificate.
             * @return Whether credentials are accepted.
             */
            bool onTLSConnect(const gloox::CertInfo &info);

/*}}}*/
            //void onStreamEvent(gloox::StreamEvent event);/*{{{*/

            /**
             * @brief This function is called for certain stream events.
             *
             * Notifications are purely informational. Not all StreamEvents
             * will necessarily be emitted for a given connection.
             *
             * @param event A stream event.
             */
            void onStreamEvent(gloox::StreamEvent event);

/*}}}*/

        private:
            //gloox::JID _jid;/*{{{*/

            /// The JID, stored to initialize the Client with.
            gloox::JID _jid;

/*}}}*/
            //int _port;/*{{{*/

            /// The server's port, stored to initialize the Client with.
            int _port;

/*}}}*/
            //std::string _password;/*{{{*/

            /// The password of the JID.
            std::string _password;

/*}}}*/
            //gloox::Client _client;/*{{{*/

            /// The XMPP client.
            gloox::Client *_client;

/*}}}*/
            //const Roster _roster;/*{{{*/

            /// The roster operation listener.
            const Roster *_roster;

/*}}}*/
            //const Control::File::Input _input;/*{{{*/

            /// The input file.
            //const Control::File::Input _input;

/*}}}*/
            //const Control::File::Output _output;/*{{{*/

            /// The output file.
            //const Control::File::Output _output;

/*}}}*/
    };
}

#include <Control/Control.ixx>

#endif // CONTROL_CONTROL_HXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

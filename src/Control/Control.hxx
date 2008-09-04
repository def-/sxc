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

#include <libsxc/Exception/Exception.hxx>

#include <Control/Roster.hxx>
#include <Control/File/Input.hxx>

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
     */
    class Control : public
        gloox::ConnectionListener,
        gloox::MessageHandler
    {
        public:
            //Control(JID &jid, int port, string &name, string &version);/*{{{*/

            /**
             * @brief The constructor.
             *
             * Create new instances of @ref File::Input, and @ref File::Output.
             * Also save the parameters to be able to use them when connecting
             * to the server on a call to @ref setPresence(). Create a client,
             * but don't connect to the server.
             *
             * @warning The parameters won't be checked for validity.
             *
             * @param jid A valid JID.
             * @param port The port on the server to connect to. -1 to use
             *        the default one.
             * @param name The name to announce.
             * @param version The version to announce.
             */
            Control(
                const gloox::JID &jid,
                int port,
                const std::string &name,
                const std::string &version);

/*}}}*/
            //~Control();/*{{{*/

            /**
             * @brief The destructor.
             */
            ~Control();

/*}}}*/

            //void setPassphrase(const std::string &pass);/*{{{*/

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
            void setPassphrase(const std::string &pass);

/*}}}*/
            //bool setPresence(presence, priority, status=Empty);/*{{{*/

            /**
             * @brief Set the presence.
             *
             * Set the user's presence and immediately send it out.
             *
             * @param presence The presence type
             * @param priority The priority ranging from -128 to 127.
             * @param status A message describing the status.
             */
            void setPresence(
                gloox::Presence::PresenceType presence,
                int priority,
                const std::string &status=gloox::EmptyString);

/*}}}*/
            //bool setPresence(presence, string status=EmptyString);/*{{{*/

            /**
             * @brief Set the presence.
             *
             * This method does not alter the priority.
             *
             * @param presence The presence type.
             * @param status A message describing the status.
             */
            void setPresence(
                gloox::Presence::PresenceType presence,
                const std::string &status=gloox::EmptyString);

/*}}}*/
            //void sendMessage(const gloox::JID &to, const string &body);/*{{{*/

            /**
             * @brief Send a text message to a user.
             *
             * This function sends a given message to a recipant, whether he is
             * on the roster or not.
             *
             * @note This message sends a "normal", not a "chat" message. Use
             *       @ref Contact::Contact for "chat" messages.
             *
             * @param to The JID of the recipant.
             * @param body The message to be transmitted.
             * @return Whether it was possible to send the message.
             */
            void sendMessage(const gloox::JID &to, const std::string &body);

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
                libsxc::Exception::Exception &e,
                bool isCritical=false) const;

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

            //Roster &getRoster();/*{{{*/

            /**
             * @brief Get a reference to the roster manager.
             */
            Roster &getRoster();

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
            //static void *_run(void *rawThat);/*{{{*/

            /**
             * @brief Receive socket updates.
             *
             * This function receives data from the socket. It runs until the
             * connection is closed.
             *
             * @param rawThat Pointer to this. Isn't pthread great?
             */
            static void *_run(void *rawThat);

/*}}}*/

            pthread_t _thread;

            //gloox::Client _client;/*{{{*/

            /// The XMPP client.
            gloox::Client _client;

/*}}}*/
            //Roster _roster;/*{{{*/

            /// The roster operation listener.
            Roster _roster;

/*}}}*/

            //const File::Input _input;/*{{{*/

            /// The input file.
            const File::Input _input;

/*}}}*/
            //const File::Output _output;/*{{{*/

            /// The output file.
            //const File::Output _output;

/*}}}*/
    };
}

#include <Control/Control.ixx>

#endif // CONTROL_CONTROL_HXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

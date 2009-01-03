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



#ifndef ACCOUNT_ACCOUNT_HXX
#define ACCOUNT_ACCOUNT_HXX


// INCLUDE/*{{{*/

#include <string>

#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/error.h>
#include <gloox/presence.h>

#include <libsxc/Exception/Exception.hxx>

#include <Account/File/Input.hxx>
#include <LogHandler.hxx>
#include <File/AbcOutput.hxx>

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif
/*}}}*/

/**
 * @brief Contains the accountler classes.
 */
namespace Account
{
  class Roster;

  /**
   * @brief The account of the local user.
   */
  class Account : public gloox::ConnectionListener
  {
    public:
      //Account(&client, &roster, &out);/*{{{*/

      /**
       * @brief The constructor.
       */
      Account(gloox::Client &client, Roster &roster, ::File::AbcOutput &out);

/*}}}*/
      //~Account();/*{{{*/

      /**
       * @brief The destructor.
       */
      ~Account();

/*}}}*/

      void run();
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
      //void setPriority(int priority);/*{{{*/

      /**
       * @brief Set the priority.
       *
       * This function sets the priority without altering the other
       * presence data.
       *
       * @param priority The new priority to set to.
       */
      void setPriority(int priority);

/*}}}*/
      //void disconnect();/*{{{*/

      /**
       * @brief Close the connection to the server.
       */
      void disconnect();

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
      //void addContact(const gloox::JID &jid) const;/*{{{*/

      /**
       */
      void addContact(const gloox::JID &jid);

/*}}}*/
      //void removeContact(const gloox::JID &jid) const;/*{{{*/

      /**
       */
      void removeContact(const gloox::JID &jid) const;

/*}}}*/
      //void subscribe(const JID &jid, &message=EmptyString) const;/*{{{*/

      /**
       */
      void subscribe(
        const gloox::JID &jid,
        const std::string &message=gloox::EmptyString) const;

/*}}}*/
      //void unsubscribe(const JID &jid, &message=Empty) const;/*{{{*/

      /**
       */
      void unsubscribe(
        const gloox::JID &jid,
        const std::string &message=gloox::EmptyString) const;

/*}}}*/
      //void acknowledgeSubscription(const gloox::JID &jid) const;/*{{{*/

      /**
       */
      void acknowledgeSubscription(const gloox::JID &jid) const;

/*}}}*/
      //void declineSubscription(const gloox::JID &jid) const;/*{{{*/

      /**
       */
      void declineSubscription(const gloox::JID &jid) const;

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

      // FIXME: Remove this! Use Output object directly instead.
      //void print(std::string text) const;/*{{{*/

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

      // FIXME: Remove this! Use wrapper methods instead.
      //Roster &getRoster();/*{{{*/

      /**
       * @brief Get a reference to the roster manager.
       */
      Roster &getRoster();

/*}}}*/
      //const gloox::JID &getJid();/*{{{*/

      /**
       * @brief Get the JID.
       *
       * @return A reference to the JID.
       */
      const gloox::JID &getJid();

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

      //pthread_t _thread;/*{{{*/

      /// The connection thread.
      pthread_t _thread;

/*}}}*/

      //gloox::Client &_client;/*{{{*/

      /// The XMPP client.
      gloox::Client &_client;

/*}}}*/
      //Roster &_roster;/*{{{*/

      /// The roster operation listener.
      Roster &_roster;

/*}}}*/
#     if DEBUG
        LogHandler _logHandler;
#     endif

      gloox::Presence::PresenceType _presence;
      int _priority;
      std::string _status;

      //File::Input _input;/*{{{*/

      /// The input file.
      File::Input _input;

/*}}}*/
      //::File::AbcOutput _out;/*{{{*/

      /// The output file.
      ::File::AbcOutput &_out;

/*}}}*/
  };
}

#include <Account/Account.ixx>

#endif // ACCOUNT_ACCOUNT_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

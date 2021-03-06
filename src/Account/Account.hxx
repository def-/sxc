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
#include <libsxc/Error/Handler.hxx>

#include <Account/File/Input.hxx>
#include <Account/File/Info.hxx>
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
      //Account(Client &, Roster &, AbcOutput &, Info &, Error::Handler &);/*{{{*/

      /**
       * @brief The constructor.
       */
      Account(
        gloox::Client &client,
        Roster &roster,
        ::File::AbcOutput &out,
        File::Info &nfo,
        libsxc::Error::Handler &eh);

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
        const std::string &status="");

/*}}}*/
      //bool setPresence(presence, string status="");/*{{{*/

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
        const std::string &status="");

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

      //void addContactLocal(const gloox::JID &jid);/*{{{*/

      /**
       * Wrapper method.
       */
      void addContactLocal(const gloox::JID &jid);

/*}}}*/
      //void addContact(const gloox::JID &jid);/*{{{*/

      /**
       * Wrapper method.
       */
      void addContact(const gloox::JID &jid);

/*}}}*/
      //void removeContact(const gloox::JID &jid) const;/*{{{*/

      /**
       * Wrapper method.
       */
      void removeContact(const gloox::JID &jid) const;

/*}}}*/
      //void subscribe(const JID &jid, &message="") const;/*{{{*/

      /**
       * Wrapper method.
       */
      void subscribe(
        const gloox::JID &jid,
        const std::string &message="") const;

/*}}}*/
      //void unsubscribe(const JID &jid, &message=Empty) const;/*{{{*/

      /**
       * Wrapper method.
       */
      void unsubscribe(
        const gloox::JID &jid,
        const std::string &message="") const;

/*}}}*/
      //void cancel(const JID &jid, &message=Empty) const;/*{{{*/

      /**
       * Wrapper method.
       */
      void cancel(
        const gloox::JID &jid,
        const std::string &message="") const;

/*}}}*/
      //void acknowledgeSubscription(const gloox::JID &jid) const;/*{{{*/

      /**
       * Wrapper method.
       */
      void acknowledgeSubscription(const gloox::JID &jid) const;

/*}}}*/
      //void declineSubscription(const gloox::JID &jid) const;/*{{{*/

      /**
       * Wrapper method.
       */
      void declineSubscription(const gloox::JID &jid) const;

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
      void _updateInfo();

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

      //File::Input _in;/*{{{*/

      /// The input file.
      File::Input _in;

/*}}}*/
      //::File::AbcOutput &_out;/*{{{*/

      /// The output file.
      ::File::AbcOutput &_out;

/*}}}*/
      //File::Info &_nfo;/*{{{*/

      /// The nfo-directory.
      File::Info &_nfo;

/*}}}*/
      libsxc::Error::Handler &_eh;
  };
}

#include <Account/Account.ixx>

#endif // ACCOUNT_ACCOUNT_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

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



#ifndef CONTACT_CONTACT_HXX
#define CONTACT_CONTACT_HXX


// INCLUDE/*{{{*/

#include <string>

#include <gloox/clientbase.h>
#include <gloox/messagesession.h>
#include <gloox/messagehandler.h>
#include <gloox/presence.h>
#include <gloox/gloox.h>

#include <File/AbcOutput.hxx>
#include <Contact/File/Input.hxx>
#include <Contact/File/Output.hxx>
#include <Contact/File/Info.hxx>
#include <Account/RosterType.hxx>

/*}}}*/

namespace Account
{
  class Roster;
}

/**
 * @brief Contains the classes for contacts.
 */
namespace Contact
{
  /**
   * @brief A representation of a contact.
   *
   * Objects of this class get called when a message for the represented
   * contact gets in. This class does not register itself as the message
   * handler.
   */
  class Contact : public gloox::MessageHandler
  {
    public:
      //Contact(&roster, &accountOut, &accountJid, &contactJid, sub);/*{{{*/

      /**
       * @brief Initialise the contact.
       *
       * @param roster The roster this contact belongs to.
       */
      Contact(
        Account::Roster &roster,
        ::File::AbcOutput &accountOut,
        const gloox::JID &accountJid,
        const gloox::JID &contactJid);

/*}}}*/
      //~Contact();/*{{{*/

      /**
       * @brief Destroy the contact.
       *
       * This method also lets the client dispose of the MessageSession.
       */
      ~Contact();

/*}}}*/

      //void updatePresence(presence, &message)/*{{{*/

      /**
       * @brief Update the presence.
       */
      void updatePresence(
        gloox::Presence::PresenceType presence,
        const std::string &message);

/*}}}*/
       //void updateRoster(Account::RosterType type);/*{{{*/

      /**
       * Update the roster type.
       */
      void updateRoster(Account::RosterType type);

/*}}}*/
      //SubscriptionType updateSub(SubscriptionType type);/*{{{*/

      /**
       * Update the subscription type.
       * @return The old subscription type.
       */
      gloox::SubscriptionType updateSub(gloox::SubscriptionType type);

/*}}}*/
      //void handleMessage(Message msg, MessageSession session);/*{{{*/

      /**
       */
      void handleMessage(
        const gloox::Message &msg,
        gloox::MessageSession *session);

/*}}}*/

      //void sendMessage(const std::string &message);/*{{{*/

      /**
       * @brief Send a chat message to the contact.
       *
       * @param message The raw message to send.
       */
      void sendMessage(const std::string &message);

/*}}}*/
      //void remove();/*{{{*/

      /**
       * Remove the info directory of the contact.
       */
      void remove();

/*}}}*/
      //bool isNew();/*{{{*/

      /**
       * Whether this contact has not been there before creating this object.
       */
      bool isNew();

/*}}}*/

    private:
      Account::Roster &_roster;
      gloox::MessageSession *_session;
      ::File::AbcOutput &_accountOut;
      //::File::AbcInput &_in;
      File::Input _in;
      //::File::AbcOutput &_out;
      File::Output _out;
      //::File::AbcInfo &_nfo;
      File::Info _nfo;

      //const gloox::JID &_getJid();/*{{{*/

      /**
       * @brief Get the JID.
       *
       * @return The JID of the contact.
       */
      const gloox::JID &_getJid();

/*}}}*/
      gloox::SubscriptionType _sub;
      bool _subSet;
  };
}


#endif // CONTACT_CONTACT_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

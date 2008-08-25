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


#ifndef CONTACT_CONTACT_HXX
#define CONTACT_CONTACT_HXX


// INCLUDE/*{{{*/

#include <gloox/clientbase.h>
#include <gloox/messagesession.h>
#include <gloox/messagehandler.h>

//#include <Contact/File/Input.hxx>

/*}}}*/

/**
 * @brief Contains the classes for contacts.
 */
namespace Contact
{
    /**
     * @author Dennis Felsing
     * @brief A representation of a contact.
     *
     * Objects of this class get called when a message for the represented
     * contact gets in.
     */
    class Contact : public gloox::MessageHandler
    {
        public:
            //Contact(gloox::ClientBase *client, const gloox::JID jid);/*{{{*/

            /**
             * @brief Initialise the contact.
             */
            Contact(gloox::ClientBase *client, const gloox::JID jid);

/*}}}*/
            //~Contact();/*{{{*/

            /**
             * @brief Destroy the contact.
             */
            ~Contact();

/*}}}*/

            //void handleMessage(Message msg, MessageSession session);/*{{{*/

            /**
             */
            void handleMessage(
                const gloox::Message &msg,
                gloox::MessageSession *session);

/*}}}*/
        private:
            //File::Input *_input;
            //File::Output *_output;
            gloox::MessageSession *_session;

    };
}

#endif // CONTACT_CONTACT_HXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

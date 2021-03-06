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

#ifndef CONTACT_FILE_INPUT_HXX
#define CONTACT_FILE_INPUT_HXX

// INCLUDES/*{{{*/

#include <string>

#include <File/AbcInput.hxx>

/*}}}*/

namespace Contact
{
  class Contact;

  namespace File
  {
    /**
     * @brief Input file for communication with contacts.
     *
     * Creates the file <JID>/<Contact>/in which handles communication with
     * a contact and the corresponding commands.
     *
     */
    class Input : public ::File::AbcInput
    {
      public:
        // Input(Contact &, string &accountJid, string &contactJid);/*{{{*/

        /**
         * @brief Default constructor, initalizes object.
         *
         * Calls @ref initialize() so that the object is ready to use.
         *
         * @param contact Contact object. Stored as a reference
         *                internally.
         */
        Input(
          Contact &contact,
          const std::string &accountJid,
          const std::string &contactJid);

/*}}}*/

      protected:

      private:
        // std::string _createPath() const;/*{{{*/

        /**
         * @brief Returns the path and file name of the FIFO.
         *
         * @see File::AbcInput::_createPath()
         *
         * @return "$accountName/in"
         */
        std::string _createPath() const;

/*}}}*/
        //Contact &_contact;/*{{{*/
        /// The contact object.
        Contact &_contact;

/*}}}*/
        const std::string _accountJid;
        const std::string _contactJid;

        // void _handleInput(const std::string &input);/*{{{*/

        /**
         * @brief Handles input that has been written into the FIFO.
         *
         * All input is interpreted as a message to the contact. A trailing
         * newline already has to be removed.
         *
         * @param input Something that has been written into the FIFO.
         */
        void _handleInput(const std::string &input);

/*}}}*/
    };
  }
}

#endif // CONTACT_FILE_INPUT_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

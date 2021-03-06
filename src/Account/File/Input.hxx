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

#ifndef ACCOUNT_FILE_INPUT_HXX
#define ACCOUNT_FILE_INPUT_HXX

// INCLUDES/*{{{*/

#include <string>

#include <File/AbcInput.hxx>
#include <File/AbcOutput.hxx>
#include <Account/Account.hxx>

/*}}}*/

namespace Account
{
  class Account;

  namespace File
  {
    /**
     * @brief Main input class for sxc.
     *
     * Creates the file <JID>/in which handles commands for sxc and
     * communication with the server.
     *
     */
    class Input : public ::File::AbcInput
    {
      public:
        // Input(Account &account, &out, const std::string &jid);/*{{{*/

        /**
         * @brief Initializes the object.
         *
         * @param account The Account object.
         */
        Input(
          Account &account,
          ::File::AbcOutput &out,
          const std::string &jid);

/*}}}*/

      private:
        //Account &_account;/*{{{*/
        /// The account object.
        Account &_account;

/*}}}*/
        //const std::string _jid;/*{{{*/
        /// The account's (local) jid.
        const std::string _jid;

/*}}}*/
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
        // void _handleInput(const std::string &input);/*{{{*/

        /**
         * @brief Handles input that has been written into the FIFO.
         *
         * For a list of valid commands see @ref
         * Account::Command. The main work will be done by an
         * instance of that class, this method provides just the
         * exception handling and creates that object.
         *
         * @param input Something that has been written into the FIFO.
         */
        void _handleInput(const std::string &input);

/*}}}*/

        ::File::AbcOutput &_out;
    };
  }
}

#endif // ACCOUNT_FILE_INPUT_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

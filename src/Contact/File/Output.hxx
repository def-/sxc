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

#ifndef CONTACT_FILE_OUTPUT_HXX
#define CONTACT_FILE_OUTPUT_HXX

// INCLUDES/*{{{*/

#include <string>

#include <File/AbcOutput.hxx>

/*}}}*/

namespace Contact
{
  namespace File
  {
    /**
     * @brief Output class for contacts.
     *
     * Creates the file $JID/$CONTACT/out which contains messages from and
     * to that contact.
     *
     */
    class Output : public ::File::AbcOutput
    {
      public:
        // Output(const string &accountJid, const string &contactJid);/*{{{*/

        /**
         * @brief Initializes the object.
         *
         * @param accountJid Our local jid.
         * @param contactJid The remote contact's jid.
         */
        Output(const std::string &accountJid, const std::string &contactJid);

/*}}}*/

      private:
        const std::string _accountJid;
        const std::string _contactJid;
        // std::string _createPath() const;/*{{{*/

        /**
         * @brief Creates a string containing the path of this file.
         *
         * @see File::AbcOutput::_createPath()
         *
         * @return $accountName/out
         */
        std::string _createPath() const;

/*}}}*/
        // std::string _format(const std::string &output) const;/*{{{*/

        /**
         * @brief Formats the output.
         *
         * @param output String to be formatted.
         * @return A formatted string.
         */
        std::string _format(const std::string &output) const;

/*}}}*/
    };
  }
}

#endif // CONTACT_FILE_OUTPUT_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
